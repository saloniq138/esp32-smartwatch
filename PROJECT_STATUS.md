# Project Status

## 2026-10-05 — implementation baseline
The repository now contains a real V1 firmware baseline and Android companion app skeleton.

### Implemented
- ESP32-S3 PlatformIO project
- ST7789 240x240 display driver baseline
- four physical buttons
- BLE GATT service with phone-to-watch and watch-to-phone characteristics
- Android BLE scanner/connection
- Android NotificationListenerService + MediaSession bridge
- media metadata transfer: title, artist, state, position, duration
- Play/Pause, Previous and Next commands
- volume UI/commands
- IR receiver/transmitter foundation
- documented configurable pin map

### Not yet validated on physical hardware
- exact board/display pinout
- actual TFT module
- BLE behavior on target phone
- Spotify-specific behavior
- album-art transfer
- Android notification mirroring
- IR learning storage/replay
- battery gauge, charger and vibration motor
- final PCB and enclosure

## Next
1. Build the firmware in PlatformIO.
2. Build/install Android app.
3. Wire the prototype using HARDWARE.md.
4. Pair and test MediaSession with Spotify.
5. Add album art and notifications.
6. Add IR learning/storage.
