#include <Arduino.h>
#include <NimBLEDevice.h>
// Добавляем заголовки ESP-IDF для низкоуровневых функций
#include "esp_bt.h"
#include "esp_gap_ble_api.h"

// Статический random-адрес: первый байт от 0xC0 до 0xFF
uint8_t spoofedMac[6] = {0xC1, 0x23, 0x45, 0x67, 0x89, 0xAB};
const char* deviceName = "FakeDevice";

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting BLE spoof...");

  // 1. Выключаем Bluetooth стек, если он уже включен
  if (esp_bluedroid_get_status() == ESP_BLUEDROID_STATUS_ENABLED) {
    esp_bluedroid_disable();
    esp_bluedroid_deinit();
  }

  // 2. Инициализируем BLE стек
  esp_err_t err = esp_bluedroid_init();
  if (err != ESP_OK) {
    Serial.printf("esp_bluedroid_init() failed: %d\n", err);
    return;
  }

  err = esp_bluedroid_enable();
  if (err != ESP_OK) {
    Serial.printf("esp_bluedroid_enable() failed: %d\n", err);
    return;
  }

  // 3. Устанавливаем MAC-адрес
  err = esp_ble_gap_set_rand_addr(spoofedMac);
  if (err != ESP_OK) {
    Serial.printf("Failed to set random addr, error: %d\n", err);
  } else {
    Serial.println("MAC address spoofed successfully.");
  }

  // 4. Инициализируем NimBLE
  NimBLEDevice::init(deviceName);
  
  // 5. Запускаем рекламу
  NimBLEDevice::getAdvertising()->start();
  Serial.println("Advertising as FakeDevice");
}

void loop() {
  delay(5000);
}
