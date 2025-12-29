#include <Arduino.h>
#include <NimBLEDevice.h>
#include <NimBLEAdvertising.h>

// Статический random-адрес: первый байт от 0xC0 до 0xFF
uint8_t spoofedMac[6] = {0xC1, 0x23, 0x45, 0x67, 0x89, 0xAB};
const char* deviceName = "FakeDevice";

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting BLE spoof...");

  // 1. Инициализируем с именем
  NimBLEDevice::init(deviceName);

  // 2. Устанавливаем MAC-адрес
  NimBLEDevice::setAddress(NimBLEAddress(spoofedMac, BLE_ADDR_RANDOM));

  // 3. Запускаем рекламу
  NimBLEDevice::getAdvertising()->start();

  Serial.println("Advertising as FakeDevice");
}

void loop() {
  delay(5000);
}
