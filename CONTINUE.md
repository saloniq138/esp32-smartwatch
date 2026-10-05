# CONTINUE — continuation state

## Project
Saloniq ESP32 Smartwatch — private repository saloniq138/esp32-smartwatch.

## Goal
A wrist smartwatch based on ESP32-S3 with a color display, physical buttons, BLE phone connection, Android media control/metadata, notifications and an IR remote.

## Current state
A working-code baseline has now been added:
- firmware/ — PlatformIO ESP32-S3 firmware
- android/ — Android companion app
- existing design/protocol documentation remains in the repository

## Hardware baseline
- ESP32-S3 DevKit-class board
- 240x240 ST7789 SPI display
- four buttons
- IR receiver + IR transmitter
- future Li-Po, charger and vibration motor

Pin assignments are prototypes only and live in firmware/include/config.h.

## Architecture
ESP32-S3 is the BLE peripheral. Android is the BLE central and also bridges Android MediaSession data to the watch. The watch sends media/IR commands back over BLE.

## Current next action
Build both projects and test the first physical prototype. After that, implement album art, notifications, IR learning/storage, battery and final PCB.

## Rule
Only mark hardware/features as completed after they are actually tested. Update this file, PROJECT_STATUS.md, TODO.md and CHANGELOG.md after each major verified step.
