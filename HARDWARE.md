# Hardware

## Założenia
- ESP32-S3
- kolorowy wyświetlacz
- fizyczne przyciski
- IR TX i IR RX
- silnik wibracyjny
- Li-Po
- USB-C

## TBD
Dokładne modele elementów zostaną wybrane przed PCB.

Nie projektować finalnej PCB przed ustaleniem pinów, ekranu, baterii, ładowania, IR i wibracji.

## USB-C + charging — added 2026-10-05

The final PCB must include a USB-C receptacle used for:
- Li-Po charging
- ESP32-S3 USB data/programming

### Power architecture

USB-C VBUS (5 V)
→ input protection
→ Li-Po charger / power-path IC
→ 1S Li-Po battery
→ 3.3 V regulator
→ ESP32-S3 + display + peripherals

The design should support running the watch while the battery is charging and seamless USB/battery source switching. A power-path charger is preferred over a simple charger-only circuit for this reason. USB-C CC1 and CC2 require separate 5.1 kΩ pull-down resistors when the device is a USB power sink. USB 2.0 D+/D− can be connected to the ESP32-S3 native USB interface.

### Planned USB-C features

- USB-C receptacle on the PCB edge
- 5 V VBUS input
- CC1/CC2 configuration resistors
- ESD protection for USB data
- USB D+ / D− to ESP32-S3
- Li-Po charging
- charge-status indication
- protected battery connection
- 3.3 V regulated system rail
- test pads for VBUS, VBAT, 3V3 and GND

### Charging safety

The exact charger, charge current, battery capacity and protection circuit must be selected together before the final PCB is routed. Do not connect an unprotected Li-Po to a prototype PCB without a verified protection strategy.

Reference architecture research: USB-C + Li-Po + power-path designs commonly use a dedicated charger/power-path IC so the system can operate while charging. citeturn0search10turn0search11
