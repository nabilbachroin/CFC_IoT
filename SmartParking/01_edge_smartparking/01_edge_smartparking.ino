#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>
#include <ESP32Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SS_PIN 5
#define RST_PIN 15
#define servoPin 25
const int SDA_PIN = 21;
const int SCL_PIN = 22;
const int ledBluePin = 33;
const int ledRedPin = 32;
const int buttonGreen = 34;
const int buttonRed = 35;
 
MFRC522 rfid(SS_PIN, RST_PIN);
Adafruit_SSD1306 display(128, 64, &Wire, -1);
Servo gateServo;
MFRC522::MIFARE_Key key; 
byte nuidPICC[4];
String cardUID;

void setupDisplay();
void setup_LedButton();

void setup() { 
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  gateServo.setPeriodHertz(50); 
  gateServo.attach(servoPin, 500, 2400); // minim and maks (ms)
  gateServo.write(180);
  setupDisplay();
  setup_LedButton();

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
          openGate();
        }
      else digitalWrite(ledRedPin, 1);
      delay(1000);
      cardUID="";
      digitalWrite(ledRedPin, LOW);
      digitalWrite(ledBluePin, LOW);
    }
  if(digitalRead(buttonGreen)==0) {Serial.println("Button Green Pressed"); delay(333);}
  if(digitalRead(buttonRed)==0) {Serial.println("Button Red Pressed"); delay(333);}
}