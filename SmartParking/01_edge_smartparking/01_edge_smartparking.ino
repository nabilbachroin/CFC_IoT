#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 22
const int ledBluePin = 32;
const int ledRedPin = 33;
 
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key; 
byte nuidPICC[4];
String cardUID;

void setup() { 
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(ledBluePin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
  digitalWrite(ledRedPin, LOW);
  digitalWrite(ledBluePin, LOW);

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}
 
void loop() {
  //TEST RFID
  readRFID();
  if (cardUID != "") 
    {
      Serial.println(cardUID); 
      if (cardUID == "90a44c26") 
        {
          Serial.println("Oke,lanjut");
          digitalWrite(ledBluePin, 1);
        }
      else digitalWrite(ledRedPin, 1);
      delay(1000);
      cardUID="";
      digitalWrite(ledRedPin, LOW);
      digitalWrite(ledBluePin, LOW);
    }
}