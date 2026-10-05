# BLE Protocol

UUID-y są TBD.

## Phone → Watch
- media metadata
- album art chunks
- notifications
- settings/configuration

## Watch → Phone
- play/pause
- previous
- next
- volume
- notification actions
- settings

Album art: Android skaluje i kompresuje obraz, dzieli go na fragmenty BLE, ESP32 składa i wyświetla.