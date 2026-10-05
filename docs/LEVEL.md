# Level / poziomica

The smartwatch now has a `Level` screen based on an MPU6050 accelerometer.

## Hardware

- MPU6050 at I2C address `0x68`
- SDA: GPIO 1 (provisional)
- SCL: GPIO 2 (provisional)
- 3.3 V and GND

The GPIO assignment must be verified against the final ESP32-S3 board/PCB before wiring.

## Firmware

At startup the firmware probes the MPU6050. If it is found, the Level page shows a live bubble and roll/pitch values. A small low-pass filter reduces jitter.

Menu -> **Level** opens the screen. The Android/BLE command `SCREEN:LEVEL` opens it remotely, while `LEVEL:READ` returns the current roll and pitch.

The level is considered centered when both roll and pitch are within approximately +/-2 degrees.
