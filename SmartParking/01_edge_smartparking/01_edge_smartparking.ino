#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>
#include <ESP32Servo.h>

//  Input
#define BUTTON_GREEN 17
#define BUTTON_RED 18
#define RFID_SS 5
#define RFID_RST 22
#define PROXIMITY_PIN 34

//  Output
#define LED_RED 32
#define LED_BLUE 33
#define SERVO_PIN 23

// Inisialisasi
Servo gateServo;

// Variabel global
String cardUID;
String cardOwnerName;
String cardStatus;
MFRC522 mfrc522(RFID_SS, RFID_RST);
String readRFID() {
  cardUID = "";
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardUID += String(mfrc522.uid.uidByte[i], HEX);
    }
  }
  return cardUID;
}

void setup()
  {
    Serial.begin(115200);
    // PB
    pinMode(BUTTON_GREEN, INPUT_PULLUP);
    pinMode(BUTTON_RED, INPUT_PULLUP);
    // RFID
    SPI.begin();
    mfrc522.PCD_Init();
    // Servo
    setupServo();
    // Proximity
    pinMode(PROXIMITY_PIN, INPUT);
  }

void loop()
  {
    cardUID = readRFID();
    //testServo();
  }