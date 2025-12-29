#include <Arduino.h>
#include <NimBLEDevice.h>
#include <NimBLEAdvertising.h>

// ВАЖНО: первый байт должен быть от 0xC0 до 0xFF (статический рандом-адрес)
uint8_t spoofedMac[6] = {0xC1, 0x23, 0x45, 0x67, 0x89, 0xAB};
const char* deviceName = "FakeDevice";

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting BLE spoof...");

  // Установка кастомного MAC через NimBLE API
  NimBLEAddress addr(spoofedMac, BLE_ADDR_TYPE_RANDOM);
  if (!NimBLEDevice::setCustomGapAddress(addr)) {
    Serial.println("FAILED to set MAC address!");
  } else {
    Serial.println("MAC address spoofed successfully.");
  }

  NimBLEDevice::init(deviceName);
  NimBLEDevice::getAdvertising()->start();
  Serial.println("Advertising as FakeDevice");
}

void loop() {
  delay(5000);
}
