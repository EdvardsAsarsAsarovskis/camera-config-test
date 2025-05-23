# Kamera konfigurēšanas testa koda README

## Projekta apraksts
Šis ir vienkāršs C++ kods, kas izmanto **Vimba C SDK**, lai:
- Inicializētu Allied Vision Alvium G5 kameru
- Iestatītu kameras parametrus (trigger, ekspozīcija, gain, white balance)
- Ņemtu kadrus ar programmatūras trigeri (software trigger)
- Aktivizētu GPIO izvadi ekspozīcijas laika sinhronizācijai (Line2)

## Izmantošanas vide
- **OS:** Windows 10
- **IDE:** Visual Studio 2022
- **SDK:** Vimba C SDK
- **Kamera:** Allied Vision Alvium G5-508C

## Kompilēšana (Visual Studio)
1. Izveidot jaunu projektu:
   - **Console App (C++)**

2. Pievienot include ceļus (`C/C++ → General → Additional Include Directories`):
C:\Program Files\Allied Vision\Vimba X\api\include
C:\Program Files\Allied Vision\Vimba X\api\include\VmbImageTransform
C:\Users\Edvards\Documents\confcam\opencv\build\include

3. Pievienot bibliotēku ceļus (`Linker → General → Additional Library Directories`):
C:\Program Files\Allied Vision\Vimba X\api\lib
C:\Users\Edvards\Documents\confcam\opencv\build\x64\vc16\lib

4. Norādit nepieciešamās bibliotēkas (`Linker → Input → Additional Dependencies`):
VmbC.lib
VmbImageTransform.lib
opencv_world4100.lib
opencv_world4100d.lib

5. Pievienot `confcam.cpp` failu projektā (vai aizvietot `main.cpp`).
6. Build un palaid programmu.


## Galvenie iestatījumi kodā
- `ExposureTime = 900000.0` (900 ms)
- `Gain = 10.0`
- `BalanceRatio Red = 2.9`
- `BalanceRatio Blue = 2.4`
- `TriggerSource = Software`, `TriggerSelector = FrameStart`
- `Line2` tiek konfigurēts ar `ExposureActive`

## Ko kods dara
1. Inicializē Vimba SDK
2. Atrod pirmo pieejamo kameru
3. Atver kameru un uzstāda parametrus
4. Iestata trigger un LED sinhronizāciju (Line2 GPIO)
5. Ar programmatūras trigeri uzņem kadrus ar 15 sek. intervālu
6. Beidz uzņemšanu un aizver kameru

![Blokshēma](Ekrānuzņēmums%202025-05-23%20061521.png)

