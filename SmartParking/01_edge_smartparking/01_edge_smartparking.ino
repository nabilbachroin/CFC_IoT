#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 22
 
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key; 
byte nuidPICC[4];
String cardUID;

void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}
 
void loop() {
  readRFID();
  if (cardUID != "") 
    {
      Serial.println(cardUID); 
      if (cardUID == "90a44c26") Serial.println("Oke,lanjut");
      cardUID="";
    }
}

void readRFID()
  {
    if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }
  cardUID = "";
  for (byte i = 0; i < 4; i++) {
    cardUID += (nuidPICC[i] < 0x10 ? "0" : "") + String(nuidPICC[i], HEX);
  }
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  }
