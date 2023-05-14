// fc:f5:c4:19:a8:be  Master

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    Serial.print("Data received: ");
    Serial.println(value.c_str());
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  BLEDevice::init("Slave_SmartParking_1");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(BLEUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b"));
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    BLEUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8"),
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY
  );

  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(pService->getUUID());
  pAdvertising->start();
  Serial.println("Advertising started...");
}

void loop() {
  delay(1000);
}

