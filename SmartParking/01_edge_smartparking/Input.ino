void processRFID(String rfidData)
  {
    rfidData.trim();
    cardUID = rfidData;
    //bluetoothSerial.print("lookup:" + cardUID);
  }

bool isCarDetected() {
  return digitalRead(PROXIMITY_PIN) == HIGH;
}