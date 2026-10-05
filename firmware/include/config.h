#pragma once

// Prototype pin map for ESP32-S3 + 1.69" 240x280 ST7789V SPI display.
// Verify these GPIOs against the exact ESP32-S3 board before wiring.
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8
#define TFT_SCLK 12
#define TFT_MOSI 11
#define TFT_BL 7

// Eight physical buttons, active LOW with INPUT_PULLUP.
#define BTN_UP 4
#define BTN_DOWN 5
#define BTN_LEFT 6
#define BTN_RIGHT 3
#define BTN_SELECT 13
#define BTN_BACK 14
#define BTN_MENU 15
#define BTN_ACTION 16

#define IR_SEND_PIN 17
#define IR_RECV_PIN 18

// MPU6050 I2C. These are provisional and must be verified on the final PCB.
#define IMU_SDA 1
#define IMU_SCL 2
#define IMU_ADDR 0x68

#define BLE_DEVICE_NAME "Saloniq Watch"
#define BLE_SERVICE_UUID "6e400001-b5a3-f393-e0a9-e50e24dcca9e"
#define BLE_RX_UUID "6e400002-b5a3-f393-e0a9-e50e24dcca9e"
#define BLE_TX_UUID "6e400003-b5a3-f393-e0a9-e50e24dcca9e"

#define WIFI_HOSTNAME "saloniq-watch"
