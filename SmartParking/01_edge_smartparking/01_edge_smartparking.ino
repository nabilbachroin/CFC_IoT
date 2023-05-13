#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

#define SS_PIN 5
#define RST_PIN 22
#define servoPin 25
const int ledBluePin = 33;
const int ledRedPin = 32;
 
MFRC522 rfid(SS_PIN, RST_PIN);
Servo gateServo;
MFRC522::MIFARE_Key key; 
byte nuidPICC[4];
String cardUID;

void setup() { 
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  gateServo.setPeriodHertz(50); 
  gateServo.attach(servoPin, 500, 2400); // minim and maks (ms)
  pinMode(ledBluePin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
  digitalWrite(ledRedPin, LOW);
  digitalWrite(ledBluePin, LOW);

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  gateServo.write(180);
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
          openGate();
        }
      else digitalWrite(ledRedPin, 1);
      delay(1000);
      cardUID="";
      digitalWrite(ledRedPin, LOW);
      digitalWrite(ledBluePin, LOW);
    }
}