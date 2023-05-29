/* Need to test:
- When the available parking slot is only for electric charging slot,
- if still want to enter, so the fee is like using electric charging slot
*/

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
const int electricParkingFee = 30;
 
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

const int totalParkingSlots = 5;
int availableParkingSlots = totalParkingSlots;
const int electricChargingSlots = 1;
int availableElectricChargingSlots = electricChargingSlots;

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
  readDatabase(SD, "/registered.txt", "/status_and_balance.txt");
}
 
void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Smart Parking System");
  display.println("CFC-IoT Class");
  display.println();
  display.println("Avlble Parking Slots=");
  display.println(availableParkingSlots);
  display.println("Elctrc Chrging Slots=");
  display.println(availableElectricChargingSlots);
  display.display();
  readRFID();
  if (cardUID != "") 
    {
      Serial.println(cardUID); 
      CardData* card = findCard(cardUID);
      if (card != NULL) 
        {
          bool useElectricChargingSlot = false;
          if(card->status == "outside" && availableParkingSlots <= 0 && availableElectricChargingSlots <= 0)
            {
              Serial.println(card->name + " Can not Enter, because parking slot is full");
              display.clearDisplay();
              display.setCursor(0, 0);
              display.println("Hello, " + card->name);
              display.println("Sorry, the parking slot is full");
              display.display();
              digitalWrite(ledRedPin, 1);
              playSpeaker("Sorry-parklot_full.mp3");
              goto skipthisstep;
            }
          if(card->status == "outside" && (availableParkingSlots>0 || availableElectricChargingSlots>0)) 
            {
              display.clearDisplay();
              display.setCursor(0, 0);
              if(availableElectricChargingSlots>0) 
                {
                  display.println("Do you want to use electric charging slot?");
                  display.println("-push the button-");
                  display.display();
                  while(1)
                    {
                      if(digitalRead(buttonGreen)==0) {useElectricChargingSlot=true; break; }
                      else if(digitalRead(buttonRed)==0) break;
                    }
                }
              if(useElectricChargingSlot)
                {
                  usingelectricslot:
                  Serial.println(card->name + " using electric charging slot");
                  display.println("Welcome, " + card->name);
                  display.println(card->name + " using electric charging slot");
                  display.println("Balance: " + String(card->balance) + " - " + electricParkingFee);
                  availableElectricChargingSlots--;
                  card->status = "inside";
                  card->balance -= electricParkingFee;
                }
              else if(useElectricChargingSlot==false && availableParkingSlots>0)
                {
                  Serial.println(card->name + " didn't using electric charging slot");
                  display.println("Welcome, " + card->name);
                  display.println(card->name + " didn't using electric charging slot");
                  display.println("Balance: " + String(card->balance) + " - " + parkingFee);
                  availableParkingSlots--;
                  card->status = "inside";
                  card->balance -= parkingFee;
                }
              else if(useElectricChargingSlot==false && availableParkingSlots<=0)
                {
                  Serial.println(card->name + " The avlble parking slot only for electric park");
                  Serial.println("asl " + card->name + " to using the slot");
                  display.println("Hello " + card->name + ", The avlble parking slot only for electric park");
                  display.println("Do you want to use electric charging slot? The Fee is " + electricParkingFee);
                  display.println("-push the button-");
                  display.display();
                  while(1)
                    {
                      if(digitalRead(buttonGreen)==0) {useElectricChargingSlot=true; break; }
                      else if(digitalRead(buttonRed)==0) break;
                    }
                  if(useElectricChargingSlot) goto usingelectricslot;
                  else 
                    {
                      display.clearDisplay();
                      display.setCursor(0, 0);
                      display.println("Okay, Thank you");
                      display.display();
                      goto skipthisstep;
                    }
                }
              display.display();
              digitalWrite(ledBluePin, 1);
              playSpeaker("Welcome-pleaseenter.mp3");
              openGate();
            }
          else if(card->status == "inside") 
            {
              Serial.println(card->name + "Ask for Go Away?");
              display.clearDisplay();
              display.setCursor(0, 0);
              display.println("Your car is currently inside, " + card->name);
              display.println("Do you want to checkout?");
              display.println("-push the button-");
              display.display();
              while(1)
                {
                  if(digitalRead(buttonGreen)==0) break;
                  else if(digitalRead(buttonRed)==0) 
                    {
                      Serial.println(card->name + " still inside");
                      display.clearDisplay();
                      display.setCursor(0, 0);
                      display.println("Okay, Thank you");
                      display.display();
                      delay(1000);
                      goto skipthisstep;
                    }
                }
              Serial.println(card->name + " Go out");
              display.clearDisplay();
              display.setCursor(0, 0);
              display.println("See you, " + card->name);
              display.println("Balance: " + String(card->balance));
              display.display();
              digitalWrite(ledBluePin, 1);
              playSpeaker("Thankyou-becareful_otr.mp3");
              openGate();
              if(availableElectricChargingSlots<=0) availableElectricChargingSlots++;
              else availableParkingSlots++;
              card->status = "outside";
            }
          writeDatabase(SD, "/registered.txt", "/status_and_balance.txt");
          updateParkingSlotsToAWS(availableParkingSlots);
        }
      else digitalWrite(ledRedPin, 1);
      delay(1000);

      skipthisstep:
      cardUID="";
      digitalWrite(ledRedPin, LOW);
      digitalWrite(ledBluePin, LOW);
    }
}