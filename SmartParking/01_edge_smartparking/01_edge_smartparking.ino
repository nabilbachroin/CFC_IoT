#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>
#include <ESP32Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <DFPlayerMini_Fast.h>

#define SD_CS 13
#define SS_PIN 5
#define RST_PIN 15
#define servoPin 25
#define proximitySensor 26
#define MAX_CARDS 50
const int SDA_PIN = 21;
const int SCL_PIN = 22;
const int ledBluePin = 33;
const int ledRedPin = 32;
const int buttonGreen = 34;
const int buttonRed = 35;
const int relay = 27;
const int led_online = 14;
const int led_offline = 12;
const int parkingFee = 10;
 
MFRC522 rfid(SS_PIN, RST_PIN);
Adafruit_SSD1306 display(128, 64, &Wire, -1);
DFPlayerMini_Fast speaker;
Servo gateServo;
MFRC522::MIFARE_Key key; 
byte nuidPICC[4];
String cardUID;

struct CardData {
  String UID;
  String name;
  String status;
  int balance;
};
CardData cardDatabase[MAX_CARDS];
int cardCount = 0;

CardData* findCard(String UID) 
  {
    for (int i = 0; i < cardCount; i++) {
      if (cardDatabase[i].UID == UID) {
        return &cardDatabase[i]; // back to card
      }
    }

    return NULL; // if card not finding
  }

void setupDisplay();
void setup_LedButton();

void setup() { 
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  gateServo.setPeriodHertz(50); 
  gateServo.attach(servoPin, 500, 2400); // minim and maks (ms)
  Serial2.begin(9600, SERIAL_8N1, 4, 2); // RX, TX
  if (!speaker.begin(Serial2)) 
    {
      Serial.println(F("Unable to begin:"));
      Serial.println(F("1.Please recheck the connection!"));
      Serial.println(F("2.Please insert the SD card!"));
      while(true);
    } 
  if (!SD.begin(SD_CS)) 
    {
      Serial.println("Card Mount Failed");
      return;
    }
  delay(1000);
  gateServo.write(180);
  setupDisplay();
  setup_LedButton();
  pinMode(proximitySensor, INPUT);
  for (byte i = 0; i < 6; i++) 
    {
      key.keyByte[i] = 0xFF;
    }
  playSpeaker("system_starting.mp3");
  // readFile(SD, "/status_and_balance.txt");
  // readFile(SD, "/registered.txt");
  readDatabase(SD, "/registered.txt", "/status_and_balance.txt");
}
 
void loop() {
  // //TEST RFID
  readRFID();
  if (cardUID != "") 
    {
      Serial.println(cardUID); 
      CardData* card = findCard(cardUID);
      if (card != NULL) 
      {
        Serial.println("Oke, lanjut");
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Welcome, " + card->name);
        display.display();
        digitalWrite(ledBluePin, 1);
        playSpeaker("Welcome-pleaseenter.mp3");
        openGate();
        card->balance -= parkingFee;
      }
      else digitalWrite(ledRedPin, 1);
      delay(1000);
      cardUID="";
      digitalWrite(ledRedPin, LOW);
      digitalWrite(ledBluePin, LOW);
      writeDatabase(SD, "/registered.txt", "/status_and_balance.txt");
    }

  // //TEST PROXIMITY SENSOR
  // //Serial.println(digitalRead(proximitySensor));
}