/* Need to test:
1. When the available parking slot is only for electric charging slot, if still want to enter, so the fee is like using electric charging slot
2. electric on even the system is starting
3. balance
4. register
5. if is there object when servo is working
6. internet connection
7. registrasion demo 
  a. say that the data from local database esp, will be save on temporary table
  b. before writing, we always clear the old data
  c. after that, we check the new UID with 'no-name' from ESP32
  d. compare with mySQL database
  e. and then we change the name in temporary table with new name from user mySQL database
  f. after that, send the data to the ESP32 to update local database
8. Already register on website, but the internet connection on system still broke
   So the local database still not update yet, and the system can give the announcement that the 
   current position there is internet connection inference

- [Me] Not finished yet:
- AWS

- [My Friends]:
- setting display
- Buy for Bright Green Led

- make mp3 file:
- Sorry balance not enough
- your card is not registered, do you want to register?
- thank you for register your card
- you are not register your card
- etc

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
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

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
const int relay = 27;  // 0 on, 1 off
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
bool after_disconnect=false;

struct CardData 
  {
    String UID;
    String name;
    String status;
    int balance;
  };
CardData cardDatabase[MAX_CARDS];
int cardCount = 0;
struct SlotData 
  {
    int parkingSlots;
    int electricChargingSlots;
  };
SlotData slotData;

void setupDisplay();
void setup_LedButton();

const char* ssid = "NabilBachroin";
const char* password = "nabilganteng";
const char* host = "google.com";
unsigned long lastCheck = 0;

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

  WiFi.begin(ssid, password);
  delay(4000);
  readDatabase(SD, "/registered.txt", "/status_and_balance.txt", "/availableSlots.txt");
  if(WiFi.status() == WL_CONNECTED)
    {
      Serial.println("");
      Serial.println("WiFi connected");  
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      Serial.println("================");
    }
  Serial.println("Out from void setup");
}
 
void loop() {
  if (millis() - lastCheck >= 3000) 
    {
      checkConnection();
      lastCheck = millis();
    }
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Smart Parking System");
  display.println("CFC-IoT Class");
  display.println();
  display.print("Parking Slots = ");
  display.println(slotData.parkingSlots);
  display.print("Elctrc Slots = ");
  display.println(slotData.electricChargingSlots);
  display.display();
  readRFID();
  if (cardUID != "") 
    {
      Serial.println(cardUID); 
      CardData* card = findCard(cardUID);
      if (card != NULL) 
        {
          bool useElectricChargingSlot = false;
          if(card->name == "no-name" && card->balance <=0 && card->status == "outside")
            {
              Serial.println("He need to finish the registration");
              digitalWrite(ledRedPin, 1);
              display.clearDisplay();
              display.setCursor(0, 0);
              display.println("Hello, You need to finish the registration proccess fisrt.");
              display.println("Have you finish the registration in the website?");
              display.println("-push the button-");
              display.display();
              //playSpeaker("Sorry-parklot_full.mp3");
              while(1)
                {
                  if(digitalRead(buttonGreen)==0) 
                    {
                      digitalWrite(led_online, LOW);
                      digitalWrite(led_offline, HIGH);
                      after_disconnect=true;

                      get_update_from_temporary_register_table();
                      writeDatabase(SD, "/registered.txt", "/status_and_balance.txt", "/availableSlots.txt");
                      Serial.println("He already finish the registration in website,");
                      Serial.println("But we still disconnect with internet,");
                      Serial.println("So my local database still not update yet.");
                      display.clearDisplay();
                      display.setCursor(0, 0);
                      display.println("Sorry, we still disconnect with internet,");
                      display.println("My database still not update,");
                      display.println("Please wait until my Online_led indicator is turn on.");
                      display.display();
                      delay(5500);

                      checkConnection();
                      goto skipthisstep;
                    }
                  else if(digitalRead(buttonRed)==0) 
                    {
                      backhere:
                      show_qrcode();
                      for(int r=0; r<=33; r++) sendUID();

                      display.setCursor(0, 0);
                      display.println("Have you finished fill in the form on the website?");
                      display.println("-push the button-");
                      display.display();
                      while(1)
                        {
                          if(digitalRead(buttonGreen)==0) break;
                          else if(digitalRead(buttonGreen)==0) goto backhere;
                        }
                      get_update_from_temporary_register_table();
                      writeDatabase(SD, "/registered.txt", "/status_and_balance.txt", "/availableSlots.txt");
                      display.clearDisplay();
                      display.setCursor(0, 0);
                      display.println("Thank you, my database is up to date.");
                      display.display();
                    }
                }
            }
          else if(card->balance <=0)
            {
              Serial.println(card->name + " Can not Enter, balance not enough");
              display.clearDisplay();
              display.setCursor(0, 0);
              display.println("Hello, " + card->name);
              display.println("Sorry, your balance is empty");
              display.display();
              digitalWrite(ledRedPin, 1);
              //playSpeaker("Sorry-parklot_full.mp3");
              delay(5000); // nanti delay hapus aja kalau udah ada suaranya
              goto skipthisstep;
            }
          else if(card->status == "outside" && slotData.parkingSlots <= 0 && slotData.electricChargingSlots <= 0)
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
          else if(card->status == "outside" && (slotData.parkingSlots>0 || slotData.electricChargingSlots>0)) 
            {
              if(slotData.electricChargingSlots>0) 
                {
                  display.clearDisplay();
                  display.setCursor(0, 0);
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
                  display.clearDisplay();
                  display.setCursor(0, 0);
                  display.println("Welcome, " + card->name);
                  display.println(card->name + " using electric charging slot");
                  display.println("Balance: " + String(card->balance) + " - " + electricParkingFee);
                  slotData.electricChargingSlots--;
                  card->status = "inside";
                  card->balance -= electricParkingFee;
                }
              else if(useElectricChargingSlot==false && slotData.parkingSlots>0)
                {
                  Serial.println(card->name + " didn't using electric charging slot");
                  display.clearDisplay();
                  display.setCursor(0, 0);
                  display.println("Welcome, " + card->name);
                  display.println(card->name + " didn't using electric charging slot");
                  display.println("Balance: " + String(card->balance) + " - " + parkingFee);
                  slotData.parkingSlots--;
                  card->status = "inside";
                  card->balance -= parkingFee;
                }
              else if(useElectricChargingSlot==false && slotData.parkingSlots<=0)
                {
                  Serial.println(card->name + " The avlble parking slot only for electric park");
                  Serial.println("asl " + card->name + " to using the slot");
                  display.clearDisplay();
                  display.setCursor(0, 0);
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
              Serial.println("Ask to " + card->name +  " for Go Away?");
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
              if(slotData.electricChargingSlots<=0) slotData.electricChargingSlots++;
              else slotData.parkingSlots++;
              card->status = "outside";
            }
          writeDatabase(SD, "/registered.txt", "/status_and_balance.txt", "/availableSlots.txt");
        }
      else 
        {
          digitalWrite(ledRedPin, 1);
          delay(500);
          Serial.println("The card is not registered");
          display.clearDisplay();
          display.setCursor(0, 0);
          display.println("Your card is not registered");
          display.println("Do you want to register?");
          display.println("-push the button-");
          display.display();
          while(1)
            {
              if(digitalRead(buttonGreen)==0)
                {
                  String nm="no-name";
                  int blnc=0;
                  addCard(cardUID, nm, "outside", blnc);
                  writeDatabase(SD, "/registered.txt", "/status_and_balance.txt", "/availableSlots.txt");

                  show_registration_again:
                  show_qrcode();
                  for(int r=0; r<=33; r++) sendUID();
                  Serial.println("Thank you for register the card");
                  display.clearDisplay();
                  display.setCursor(0, 0);
                  display.println("Thank you for register your card");
                  display.println("Your card balance=" + blnc);
                  display.display();
                  delay(5000);
                  display.setCursor(0, 0);
                  display.println("Have you finished fill in the form on the website?");
                  display.println("-push the button-");
                  display.display();
                  while(1)
                    {
                      if(digitalRead(buttonGreen)==0) break;
                      else if(digitalRead(buttonRed)==0) goto show_registration_again;
                    }
                  get_update_from_temporary_register_table();
                  writeDatabase(SD, "/registered.txt", "/status_and_balance.txt", "/availableSlots.txt");
                  display.clearDisplay();
                  display.setCursor(0, 0);
                  display.println("Thank you, my database is up to date.");
                  display.display();
                  break;
                }
              else if(digitalRead(buttonRed)==0) 
                {
                  Serial.println("He/She didn't register the card");
                  display.clearDisplay();
                  display.setCursor(0, 0);
                  display.println("Okay, You didn't register your card");
                  display.println("Thank you");
                  display.display();
                  delay(2000);
                  break;
                }
            }
        }

      skipthisstep:
      cardUID="";
      digitalWrite(ledRedPin, LOW);
      digitalWrite(ledBluePin, LOW);
    }
}