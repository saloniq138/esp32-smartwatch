# TODO

## V1 prototype
- [x] ESP32-S3 PlatformIO project
- [x] ST7789V 1.69" 240x280 display baseline
- [x] 8-button input
- [x] BLE GATT baseline
- [x] Android BLE companion baseline
- [x] MediaSession metadata bridge
- [x] Play/Pause
- [x] Previous/Next
- [x] volume commands
- [x] Wi-Fi provisioning commands
- [x] NTP clock baseline
- [x] theme selection
- [x] wallpaper selection
- [x] settings persistence on watch
- [x] IR receive foundation
- [x] TV remote command UI/protocol
- [ ] Build firmware on target
- [ ] Build/install Android app
- [ ] Wire and test display/buttons
- [ ] Pair phone and verify Spotify

## Configuration
- [x] Create/update firmware/include/config.h
- [ ] Verify every GPIO against the exact ESP32-S3 module
- [ ] Verify ST7789V display pinout and backlight circuit
- [ ] Verify 8-button GPIO assignments
- [ ] Verify IR TX/RX GPIOs
- [ ] Verify MPU6050 I2C pins/address
- [ ] Verify vibration GPIO and transistor/MOSFET driver
- [ ] Verify battery ADC pin and voltage-divider values

## V2
- [ ] Android Wi-Fi provisioning/settings UI
- [ ] Android theme/wallpaper configuration UI
- [ ] Album-art transfer and caching
- [ ] Android notifications
- [ ] vibration alerts
- [ ] real battery measurement
- [ ] robust Europe/Warsaw timezone handling

## V3
- [ ] IR learning with raw timing storage
- [ ] named IR remote profiles
- [ ] IR replay
- [ ] richer media UI
- [ ] TV protocol/profile database
- [ ] configurable button mapping
- [ ] level / inclinometer mode using MPU6050

## Power / USB-C
- [ ] USB-C receptacle on final PCB
- [ ] USB-C CC1/CC2 sink resistors
- [ ] USB D+/D- native ESP32-S3 connection
- [ ] USB ESD protection
- [ ] Li-Po charger with power-path
- [ ] battery protection and safe charge-current selection
- [ ] 3.3V regulator sized for ESP32-S3 + TFT + peripherals
- [ ] charging/status indicator
- [ ] battery voltage/fuel-gauge measurement

## PCB / Manufacturing
- [ ] Select exact ESP32-S3 module and footprint
- [ ] Select exact USB-C receptacle footprint
- [ ] Select charger/power-path IC
- [ ] Select 3.3V regulator
- [ ] Select battery connector and protection
- [ ] Create KiCad schematic
- [ ] Assign verified footprints
- [ ] Create PCB layout
- [ ] Run ERC
- [ ] Run DRC
- [ ] Add test points: VBUS, VBAT, 3V3, GND
- [ ] Generate Gerber files
- [ ] Generate Excellon drill files
- [ ] Generate BOM
- [ ] Generate CPL/PnP file if assembly is ordered
- [ ] Production review before sending to JLCPCB/PCBWay

## Final hardware
- [ ] exact ESP32-S3 module selection
- [ ] battery + charger + protection
- [ ] USB-C
- [ ] custom PCB
- [ ] 3D printed enclosure
- [ ] power optimization
- [ ] final tests
