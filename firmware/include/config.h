#pragma once

// Saloniq Smartwatch - ESP32-S3 hardware configuration
// Target: ESP32-S3 + 1.69" 240x280 ST7789V SPI display
//
// IMPORTANT:
// - GPIO map is for the custom-watch design.
// - Exact ESP32-S3 module, display FPC and PCB routing must be verified
//   before production.
// - GPIO19/20 are reserved for native USB D-/D+.
// - Battery ADC uses GPIO8 (ADC1).
// - GPIO34 is NOT used for battery measurement.

#define TFT_CS       10
#define TFT_DC        9
#define TFT_RST      38
#define TFT_SCLK     12
#define TFT_MOSI     11
#define TFT_BL        7

#define TFT_WIDTH    240
#define TFT_HEIGHT   280

// Eight physical buttons, active LOW with INPUT_PULLUP.
#define BTN_UP        4
#define BTN_DOWN      5
#define BTN_LEFT      6
#define BTN_RIGHT     3
#define BTN_SELECT   13
#define BTN_BACK     14
#define BTN_MENU     15
#define BTN_ACTION   16

#define BUTTON_COUNT 8

// IR remote
#define IR_SEND_PIN  17
#define IR_RECV_PIN  18
#define IR_CARRIER_FREQUENCY 38000

// MPU6050 I2C
// External 4.7k pull-ups to 3V3 are required on the final PCB.
// AD0 should be tied to GND for address 0x68.
#define IMU_SDA      1
#define IMU_SCL      2
#define IMU_ADDR     0x68

// Vibration motor driver control.
// Final PCB should use a transistor/MOSFET driver and flyback diode.
#define VIBRATION_PIN 21

// Battery voltage measurement.
// ADC1 is used so Wi-Fi operation does not conflict with ADC2.
// Final PCB: 100k/100k voltage divider from VBAT to GPIO8.
#define BATTERY_ADC_PIN 8
#define BATTERY_R1 100000.0f
#define BATTERY_R2 100000.0f

#define BATTERY_MIN_VOLTAGE 3.20f
#define BATTERY_MAX_VOLTAGE 4.20f

// Native ESP32-S3 USB
// GPIO19 = USB D-
// GPIO20 = USB D+
#define USB_ENABLED true
#define USB_D_MINUS_PIN 19
#define USB_D_PLUS_PIN 20

// BLE
#define BLE_DEVICE_NAME "Saloniq Watch"
#define BLE_SERVICE_UUID "6e400001-b5a3-f393-e0a9-e50e24dcca9e"
#define BLE_RX_UUID "6e400002-b5a3-f393-e0a9-e50e24dcca9e"
#define BLE_TX_UUID "6e400003-b5a3-f393-e0a9-e50e24dcca9e"

// Wi-Fi
#define WIFI_HOSTNAME "saloniq-watch"
#define WIFI_CONNECT_TIMEOUT_MS 15000

// Display defaults
#define WATCH_DEFAULT_BRIGHTNESS 80
#define WATCH_DEFAULT_SCREEN_TIMEOUT 30000
#define WATCH_DEFAULT_VIBRATION true

// Feature flags
#define FEATURE_WIFI true
#define FEATURE_BLE true
#define FEATURE_IR true
#define FEATURE_IMU true
#define FEATURE_VIBRATION true
#define FEATURE_USB true
#define FEATURE_BATTERY true

// Debug
#define DEBUG_ENABLED true

#if DEBUG_ENABLED
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif
