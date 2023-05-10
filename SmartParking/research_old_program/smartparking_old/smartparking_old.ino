#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <MFRC522.h>

#include <MQTTClient.h>

const char* ssid = "Bachroin";
const char* password = "masnabilganteng";

// AWS IoT Endpoint, Certificate, and Private Key
const char* AWS_IOT_ENDPOINT = "your-aws-iot-endpoint.amazonaws.com";

static const char AWS_ROOT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
... (sertifikat CA root Amazon) ...
-----END CERTIFICATE-----
)EOF";

static const char AWS_CERTIFICATE[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
... (sertifikat perangkat AWS IoT) ...
-----END CERTIFICATE-----
)EOF";

static const char AWS_PRIVATE_KEY[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
... (kunci privat perangkat AWS IoT) ...
-----END RSA PRIVATE KEY-----
)EOF";

// Pins
const int servoPin = 5;
const int rfidSDA = 21;
const int rfidSCK = 22;
const int rfidMOSI = 23;
const int rfidMISO = 19;
const int rfidRST = 4;

// Servo
Servo parkingServo;

// Display
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_RST 16
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RST);

// RFID
MFRC522 rfid(rfidSDA, rfidRST);

// MQTT
WiFiClientSecure net;
MQTTClient client;

// Function prototypes
void connectToWiFi();
void connectToAWS();
void messageHandler(String &topic, String &payload);
void displayMessage(const char* message);
void openGate();
void closeGate();

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  connectToAWS();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  parkingServo.attach(servoPin);

  SPI.begin(rfidSCK, rfidMISO, rfidMOSI, rfidSDA);
  rfid.PCD_Init();

  // Set MQTT message handler
  client.onMessage(messageHandler);
}

void loop() {
  client.loop();
  delay(10);  // <- it is important to add delay in loop to avoid watchdog reset

  // Check RFID card
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String rfidUid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      rfidUid += String(rfid.uid.uidByte[i], HEX);
    }
    rfidUid.toUpperCase();

    Serial.println("RFID UID: " + rfidUid);

    // Publish RFID UID to AWS IoT
    client.publish("smartparking/rfid", rfidUid);
  }
}

