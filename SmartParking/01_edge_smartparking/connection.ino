void setupBLE() 
  {
    BLEDevice::init("");
    BLEScan *pScan = BLEDevice::getScan();
    pScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pScan->setActiveScan(true);
    pScan->start(5, false);
  }

void notifyCallback(BLERemoteCharacteristic* pRemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) 
  {
    // Proses data yang diterima dari Node Fog
    Serial.print("Received data: ");
    for (int i = 0; i < length; i++) 
      {
        Serial.print(pData[i], HEX);
        Serial.print(" ");
      }
    Serial.println();
  }


void sendDataToNodeFog(String data) 
  {
    if (pRemoteCharacteristic != nullptr) 
      {
        pRemoteCharacteristic->writeValue(data.c_str());
      }
  }