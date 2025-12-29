#include <Arduino.h>
#include <NimBLEDevice.h>
#include <NimBLEAdvertising.h>

uint8_t spoofedMac[6] = {0xC1, 0x23, 0x45, 0x67, 0x89, 0xAB}; // Статический рандом-адрес
const char* deviceName = "FakeDevice";

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting BLE spoof...");

  // Устанавливаем MAC ДО init()
  NimBLEAddress addr(spoofedMac, BLE_ADDR_RANDOM);
  NimBLEDevice::setCustomGapAddress(addr);

  NimBLEDevice::init(deviceName);
  NimBLEDevice::getAdvertising()->start();
  Serial.println("Advertising as FakeDevice");
}

void loop() {
  delay(5000);
}
