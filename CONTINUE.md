# CONTINUE — continuation state

## Project
Saloniq ESP32 Smartwatch — private repository saloniq138/esp32-smartwatch.

## Goal
A wrist smartwatch based on ESP32-S3 with a 1.69" 240x280 color display, 8 physical buttons, Wi-Fi, BLE phone connection, Android media control/metadata, settings/themes/wallpapers and an IR remote for TVs and other devices.

## Current state
Code baseline is in the repository:
- firmware/ — PlatformIO ESP32-S3 firmware
- android/ — Android companion app
- existing design/protocol/hardware documentation remains in the repository

### Hardware baseline
- ESP32-S3 DevKit-class board
- 1.69" ST7789V 240x280 SPI display
- 8 buttons
- IR receiver + IR transmitter
- future Li-Po, charger and vibration motor

Pin assignments are prototypes only and live in firmware/include/config.h.

## Architecture
ESP32-S3 is the BLE peripheral. Android is the BLE central and bridges Android MediaSession data to the watch. Wi-Fi is handled by the ESP32 for network/time functions. The watch sends media/IR commands to the phone over BLE.

## Current firmware UI
- HOME — clock, date, Wi-Fi/BLE status
- MEDIA — media metadata and playback controls
- MENU — navigation
- SETTINGS — theme/wallpaper controls
- WIFI — saved Wi-Fi/provisioning commands
- IR — IR receiver foundation
- TV REMOTE — abstract TV commands over BLE

## Important limitation
TV remote buttons currently send abstract IR command messages; full IR learning, raw timing storage, profiles and replay are not finished. Do not describe this as a fully working universal TV remote yet.

## Current next action
Build both projects and test the first physical prototype. Then implement Android settings/provisioning UI, IR learning/storage/replay, notifications, album art, battery and final PCB. The final PCB must include USB-C charging/programming with a proper Li-Po power-path.

## Rule
Only mark hardware/features as completed after they are actually tested. Update this file, PROJECT_STATUS.md, TODO.md and CHANGELOG.md after each major verified step.
