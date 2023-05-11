void processRFID(String rfidData)
  {
    cardUID = rfidData.trim();
    //bluetoothSerial.print("lookup:" + cardUID);
  }

bool isCarDetected() {
  return digitalRead(PROXIMITY_PIN) == HIGH;
}