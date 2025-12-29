#include <Arduino.h>
#include <NimBLEDevice.h>
#include <NimBLEAdvertising.h>

// Статический рандом-адрес: первый байт от 0xC0 до 0xFF
uint8_t spoofedMac[6] = {0xC1, 0x23, 0x45, 0x67, 0x89, 0xAB};
const char* deviceName = "FakeDevice";

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting BLE spoof...");

  // Передаём MAC-адрес прямо в init()
  NimBLEDevice::init(NimBLEAddress(spoofedMac, BLE_ADDR_RANDOM), deviceName);

  NimBLEAdvertising* pAdv = NimBLEDevice::getAdvertising();
  pAdv->start();

  Serial.println("Advertising as FakeDevice");
}

void loop() {
  delay(5000);
}
