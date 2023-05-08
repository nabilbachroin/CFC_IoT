#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <MFRC522.h>
#include <Servo.h>

// Wi-Fi credentials
const char* ssid = "Your_WiFi_SSID";
const char* password = "Your_WiFi_Password";

// Fog node IP address
const IPAddress fogNodeIP(192, 168, 1, 100);

// OLED display pins
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RESET -1

// RFID pins and object
#define RST_PIN 22
#define SS_PIN 21
MFRC522 rfid(SS_PIN, RST_PIN);

// Servo pin and object
const int servoPin = 18;
Servo myservo;

// Create an OLED display object
Adafruit_SSD1306 display(OLED_RESET);

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// Add from pcinu
int space=0;
const int led_wifi_con=;
const int led_wifi_dis=;
const int pb1=;
const int pb2=;
// database register = name, rfid num
// database transaction = rfid num, balance

void setup() {
  Serial.begin(115200);

  // Initialize OLED display
  Wire.begin(OLED_SDA, OLED_SCL);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Smart Parking");
  display.display();

  // Initialize RFID
  SPI.begin();
  rfid.PCD_Init();

  // Initialize servo
  myservo.attach(servoPin);

  // Connect to Wi-Fi
  connectToWiFi();
}

void loop() {
  // Check Wi-Fi connection
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  // Check for RFID card
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String cardId = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      cardId += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
      cardId += String(rfid.uid.uidByte[i], HEX);
    }
    cardId.toUpperCase();
    Serial.print("Card ID: ");
    Serial.println(cardId);

    // Send card ID to the fog node
    WiFiClient client;
    if (client.connect(fogNodeIP, 80)) {
      client.println(cardId);
      client.flush();

      // Wait for a response from the fog node
      String response = client.readStringUntil('\n');
      response.trim();

      if (response == "OPEN_SERVO") {
        openServo();
      } else if (response == "CARD_NOT_REGISTERED") {
        displayMessage("Card not registered");
      }
    }
  }
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");
}

void openServo() {
  myservo.write(0);
  delay(5000);
  myservo.write(90);
}

void displayMessage(const char* message) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(message);
  display.display();
  delay(3000);
}