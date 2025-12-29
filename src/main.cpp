#include <Arduino.h>
#include <NimBLEDevice.h>

// ВАЖНО: Статический random-адрес (первый байт от 0xC0 до 0xFF)
uint8_t spoofedMac[6] = {0xC1, 0x23, 0x45, 0x67, 0x89, 0xAB};
const char* deviceName = "FakeDevice"; // Замените на имя вашего устройства

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting BLE spoof...");

  // Инициализируем BLE с именем устройства
  NimBLEDevice::init(deviceName);

  // Устанавливаем MAC-адрес (работает в версии 1.4.3)
  if (esp_ble_gap_set_rand_addr(spoofedMac) != ESP_OK) {
    Serial.println("FAILED to set MAC address!");
  } else {
    Serial.println("MAC address spoofed successfully.");
  }

  // Запускаем рекламу
  NimBLEDevice::getAdvertising()->start();
  Serial.println("Advertising as FakeDevice");
}

void loop() {
  delay(5000);
}
