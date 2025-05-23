# Kamera konfigurēšanas testa koda README

## Projekta apraksts
Šis ir vienkāršs C++ kods, kas izmanto **Vimba C SDK**, lai:
- Inicializētu Allied Vision Alvium G5 kameru
- Iestatītu kameras parametrus (trigger, ekspozīcija, gain, white balance)
- Ņemtu kadrus ar programmatūras trigeri (software trigger)
- Aktivizētu GPIO izvadi ekspozīcijas laika sinhronizācijai (Line2)

## Izmantošanas vide
- **OS:** Windows 10/11
- **IDE:** Visual Studio 2019 / 2022
- **SDK:** Vimba C SDK
- **Kamera:** Allied Vision Alvium G5-508C

## Kompilēšana (Visual Studio)
1. Izveido jaunu **Console App** projektu (C++)
2. Pievieno Vimba C SDK include un lib ceļus:
   - Include path: `C:\Program Files\Allied Vision\Vimba X\VmbC\Include`
   - Library path: `...\VmbC\Lib\x64`
3. Pievieno linkerim biblioteku: `VmbC.lib`
4. Iekopē kodu `confcam.cpp`
5. Build un palaid

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

