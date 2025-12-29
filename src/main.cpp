#include <Arduino.h>
#include <NimBLEDevice.h>
#include "esp_gap_ble_api.h"  // Для esp_ble_gap_set_rand_addr

// Статический random-адрес: первый байт от 0xC0 до 0xFF
uint8_t spoofedMac[6] = {0xC1, 0x23, 0x45, 0x67, 0x89, 0xAB};
const char* deviceName = "FakeDevice";

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting BLE spoof...");

  // 1. Инициализируем NimBLE
  NimBLEDevice::init(deviceName);
  
  // 2. Устанавливаем MAC-адрес
  esp_ble_gap_set_rand_addr(spoofedMac);
  
  // 3. Запускаем рекламу
  NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->start();
  
  Serial.println("Advertising with spoofed MAC");
}

void loop() {
  delay(5000);
}
