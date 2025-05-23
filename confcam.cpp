#include <VmbC/VmbC.h> 
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    // 1) Start Vimba
    VmbError_t err = VmbStartup(nullptr);
    if (err != VmbErrorSuccess) {
        std::cerr << "Failed to start Vimba: " << err << std::endl;
        return 1;
    }

    // 2) Find cameras
    constexpr VmbUint32_t MAX_CAMERAS = 10;
    VmbCameraInfo_t cameras[MAX_CAMERAS];
    VmbUint32_t cameraCount = MAX_CAMERAS;

    err = VmbCamerasList(cameras, MAX_CAMERAS, &cameraCount, sizeof(VmbCameraInfo_t));
    if (err != VmbErrorSuccess || cameraCount == 0) {
        std::cerr << "No cameras found.\n";
        VmbShutdown();
        return 1;
    }

    // 3) Open the first camera
    VmbHandle_t cameraHandle = nullptr;
    err = VmbCameraOpen(cameras[0].cameraIdString, VmbAccessModeFull, &cameraHandle);
    if (err != VmbErrorSuccess) {
        std::cerr << "Failed to open camera.\n";
        VmbShutdown();
        return 1;
    }



    // Trigger + Acquisition settings
    VmbFeatureEnumSet(cameraHandle, "TriggerSelector", "FrameStart");
    VmbFeatureEnumSet(cameraHandle, "TriggerMode", "On");
    VmbFeatureEnumSet(cameraHandle, "TriggerSource", "Software");
    VmbFeatureEnumSet(cameraHandle, "TriggerActivation", "RisingEdge");

   
    VmbFeatureEnumSet(cameraHandle, "Acquisition Mode", "SingleFrame");


    // ————————————————
    // Line2 → ExposureActive (for external LED, etc.)
    // ————————————————
    VmbFeatureEnumSet(cameraHandle, "LineSelector", "Line2");
    VmbFeatureEnumSet(cameraHandle, "LineMode", "Output");
    VmbFeatureEnumSet(cameraHandle, "LineSource", "ExposureActive");

    // ————————————————
    // Basic camera parameters
    // ————————————————
    VmbFeatureFloatSet(cameraHandle, "ExposureTime", 900000.0);
    VmbFeatureFloatSet(cameraHandle, "Gain", 10.0);
    VmbFeatureEnumSet(cameraHandle, "BalanceWhiteAuto", "Off");
    VmbFeatureEnumSet(cameraHandle, "BalanceRatioSelector", "Red");
    VmbFeatureFloatSet(cameraHandle, "BalanceRatio", 2.9);
    VmbFeatureEnumSet(cameraHandle, "BalanceRatioSelector", "Blue");
    VmbFeatureFloatSet(cameraHandle, "BalanceRatio", 2.4);

    // 4) Start acquisition
    err = VmbFeatureCommandRun(cameraHandle, "AcquisitionStart");
    if (err != VmbErrorSuccess) {
        std::cerr << "Failed to start acquisition.\n";
    }

    // ————————————————
    // Trigger loop: 5 frames
    // ————————————————
    for (int i = 0; i < 2; ++i) { 
        std::cout << "Triggering frame #" << (i + 1) << std::endl;
        err = VmbFeatureCommandRun(cameraHandle, "TriggerSoftware");
        if (err != VmbErrorSuccess) {
            std::cerr << "Software trigger failed.\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(15));
    }

    // 5) Stop acquisition
    VmbFeatureCommandRun(cameraHandle, "AcquisitionStop");

    // 6) Close & shutdown
    VmbCameraClose(cameraHandle);
    VmbShutdown();

    std::cout << "Done, exiting.\n";
    return 0;
}