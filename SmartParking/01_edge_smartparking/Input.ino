void readRFID()
  {
    if ( ! rfid.PICC_IsNewCardPresent()) return;
    if ( ! rfid.PICC_ReadCardSerial()) return;
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) 
      {
        Serial.println(F("Your tag is not of type MIFARE Classic."));
        return;
      }
    for (byte i = 0; i < 4; i++) nuidPICC[i] = rfid.uid.uidByte[i];
    cardUID = "";
    for (byte i = 0; i < 4; i++) cardUID += (nuidPICC[i] < 0x10 ? "0" : "") + String(nuidPICC[i], HEX);
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }