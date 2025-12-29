#include <Arduino.h>
#include <NimBLEDevice.h>
#include <NimBLEAdvertising.h>
#include <NimBLEUtils.h>  // ⚠️ ВАЖНО: добавьте этот заголовок

// Статический random-адрес: первый байт от 0xC0 до 0xFF
uint8_t spoofedMac[6] = {0xC1, 0x23, 0x45, 0x67, 0x89, 0xAB};
const char* deviceName = "FakeDevice";

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting BLE spoof...");

  // Создаем объект адреса
  NimBLEAddress addr(spoofedMac, BLE_ADDR_RANDOM);
  
  // Устанавливаем MAC-адрес через NimBLEUtils
  if (!NimBLEUtils::setCustomAddress(addr)) {
    Serial.println("FAILED to set MAC address!");
  } else {
    Serial.println("MAC address spoofed successfully.");
  }

  // Инициализируем BLE
  NimBLEDevice::init(deviceName);
  
  // Запускаем рекламу
  NimBLEDevice::getAdvertising()->start();
  Serial.println("Advertising as FakeDevice");
}

void loop() {
  delay(5000);
}
