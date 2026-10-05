# Album Art

Pipeline:
MediaSession → Android App → artwork → resize/compress → BLE → ESP32 → display.

Przykładowy rozmiar: 160×160 px dla ekranu 240×240.

Optymalizacja: JPEG, ograniczenie rozmiaru, fragmentacja BLE, cache i wysyłanie tylko po zmianie utworu.