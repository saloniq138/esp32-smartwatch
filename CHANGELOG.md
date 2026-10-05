# Changelog

## 2026-10-05 — 240x280 + 8-button smartwatch baseline
- Switched the firmware display target from the earlier 240x240 assumption to the selected 1.69" ST7789V 240x280 SPI display.
- Expanded the prototype from four buttons to eight buttons.
- Added Home, Media, Menu, Settings, Wi-Fi, IR and TV Remote pages.
- Added Wi-Fi credential commands and saved Wi-Fi settings on the ESP32.
- Added NTP-based clock display when Wi-Fi is available.
- Added persistent theme and wallpaper selection.
- Added IR receive forwarding foundation.
- Added abstract TV remote commands sent over BLE to the Android companion.
- Documented that IR learning/storage/replay and full universal-TV support are still unfinished.
- Updated continuation, project status and TODO documentation.

Earlier baseline:
- ESP32-S3 PlatformIO firmware baseline.
- Android BLE companion with MediaSession/NotificationListener bridge.
- Media metadata and Play/Pause/Previous/Next commands.
- IR receiver/transmitter foundation.
