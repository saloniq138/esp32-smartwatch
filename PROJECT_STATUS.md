# Project Status

## 2026-10-05 — ESP32-S3 smartwatch prototype
The repository now targets the selected 1.69" 240x280 ST7789V SPI display and an 8-button prototype.

### Implemented in code
- ESP32-S3 PlatformIO firmware baseline
- ST7789V 1.69" 240x280 SPI display initialization
- 8 physical-button UI
- BLE GATT service for phone ↔ watch communication
- Android BLE scanner/connection
- Android MediaSession/NotificationListener bridge
- media metadata transfer and Play/Pause/Previous/Next commands
- Wi-Fi provisioning commands and saved Wi-Fi settings on the watch
- NTP time display when Wi-Fi is connected
- theme and wallpaper selection with persistent preferences
- menu pages for Home, Media, Settings, Wi-Fi, IR and TV Remote
- IR receive foundation and TV-remote command protocol

### Not yet fully implemented or hardware-validated
- exact ESP32-S3 board GPIO compatibility
- physical TFT wiring and display orientation
- Android Wi-Fi provisioning/settings UI
- actual Spotify behavior on the target phone
- album-art transfer
- Android notification mirroring
- IR learning, raw timing storage and reliable replay
- real TV protocol/profile database
- battery gauge, charger and vibration motor
- final PCB, enclosure and power optimization

### Next
1. Build firmware in PlatformIO and validate the exact pinout.
2. Build/install Android companion.
3. Wire and test the 240x280 display and all 8 buttons.
4. Pair the phone and test media control/metadata.
5. Add Android Wi-Fi/theme/wallpaper configuration UI.
6. Implement IR learning, storage, profiles and replay.
7. Add notifications, album art, battery and final hardware.

Only mark hardware/features as completed after physical testing.
