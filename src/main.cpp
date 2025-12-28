#include <Arduino.h>
#include <NimBLEDevice.h>
#include <NimBLEAdvertising.h>

// MAC-адрес должен начинаться с 0xC0–0xFF (например: C1, D2, E3, F4)
// Пример: {0xC1, 0x23, 0x45, 0x67, 0x89, 0xAB}
uint8_t spoofedMac[6] = {0xC1, 0x23, 0x45, 0x67, 0x89, 0xAB};
const char* deviceName = "FakeDevice"; // ← Замените на имя настоящего устройства!

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting BLE spoof...");

  NimBLEDevice::init(deviceName);
  
  if (esp_ble_gap_set_rand_addr(spoofedMac) != ESP_OK) {
    Serial.println("FAILED to set MAC address!");
  } else {
    Serial.println("MAC address spoofed successfully.");
  }

  NimBLEAdvertising* pAdv = NimBLEDevice::getAdvertising();
  pAdv->start();
  Serial.println("Advertising as FakeDevice");
}

void loop() {
  delay(5000);
}
