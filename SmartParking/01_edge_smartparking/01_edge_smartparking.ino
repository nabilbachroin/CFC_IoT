#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEUUID.h>

BLEUUID SERVICE_UUID        ("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
BLEUUID CHARACTERISTIC_UUID ("beb5483e-36e1-4688-b7f5-ea07361b26a8");

BLEClient *pClient;
BLEAddress *serverAddress;
BLERemoteService *pRemoteService;
BLERemoteCharacteristic *pRemoteCharacteristic;

class MyClientCallback : public BLEClientCallbacks 
  {
    void onConnect(BLEClient *pClient) {Serial.println("Connected to server");}
    void onDisconnect(BLEClient *pClient) {Serial.println("Disconnected from server");}
  };

bool connectToServer() 
  {
    pClient = BLEDevice::createClient();
    pClient->setClientCallbacks(new MyClientCallback());
    pClient->connect(*serverAddress);

    pRemoteService = pClient->getService(SERVICE_UUID);
    if (pRemoteService == nullptr) 
      {
        pClient->disconnect();
        return false;
      }
    pRemoteCharacteristic = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID);
    if (pRemoteCharacteristic == nullptr) 
      {
        pClient->disconnect();
        return false;
      }
    if (pRemoteCharacteristic->canNotify()) 
      {
        pRemoteCharacteristic->registerForNotify(notifyCallback);
        Serial.println("Registered for notifications");
      }
    return true;
  }

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks 
  {
    void onResult(BLEAdvertisedDevice advertisedDevice) 
      {
        if (advertisedDevice.haveServiceUUID() && advertisedDevice.getServiceUUID().equals(SERVICE_UUID)) 
          {
            BLEDevice::getScan()->stop();
            serverAddress = new BLEAddress(advertisedDevice.getAddress());
            connectToServer();
          }
      }
  };

void setup()
  {
    Serial.begin(115200);
    setupBLE();
  }

void loop()
  {
    //test ble
    String data = "test 09 may"; // Isi dengan data yang ingin dikirim
    sendDataToNodeFog(data);
    delay(1000);
  }
