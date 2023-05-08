#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <SD.h>
#include <MFRC522.h>
#include <Ping.h>

// Wi-Fi credentials
const char* ssid = "Your_WiFi_SSID";
const char* password = "Your_WiFi_Password";

// AWS IoT endpoint and credentials
const char* awsEndpoint = "your-aws-iot-endpoint";
const char* awsCert = "your-aws-certificate";
const char* awsPrivateKey = "your-aws-private-key";

// SD card pins
const int sdCSPin = 5;

// RFID pins and object
#define RST_PIN 22
#define SS_PIN 21
MFRC522 rfid(SS_PIN, RST_PIN);

// Servo pins
const int servoPin = 18;

WiFiServer server(80);
WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup() {
  Serial.begin(115200);

  // Initialize SPI for SD card and RFID
  SPI.begin();

  // Initialize SD card
  if (!SD.begin(sdCSPin)) {
    Serial.println("SD card initialization failed");
    return;
  }
  Serial.println("SD card initialized");

  // Initialize RFID
  rfid.PCD_Init();
  Serial.println("RFID initialized");

  // Initialize Wi-Fi and MQTT
  connectToWiFiAndAWS();

  // Start the server
  server.begin();
}

void loop() {
  // Check Wi-Fi and MQTT connection
  if (WiFi.status() != WL_CONNECTED || !mqttClient.connected()) {
    connectToWiFiAndAWS();
  }

  // Handle incoming MQTT messages
  mqttClient.loop();

  // Handle incoming client connections (from edge devices)
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connected");
    handleClient(client);
    client.stop();
  }
}

void connectToWiFiAndAWS() {
  // Connect to Wi-Fi
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to Wi-Fi...");
    }
    Serial.println("Connected to Wi-Fi");
  }

  // Configure MQTT settings
  mqttClient.setServer(awsEndpoint, 8883);
  mqttClient.setCallback(mqttCallback);

  // Connect to MQTT
  if (!mqttClient.connected()) {
    while (!mqttClient.connected()) {
      Serial.println("Connecting to AWS IoT...");
      if (mqttClient.connect("ESP32FogNode", awsCert, awsPrivateKey)) {
        Serial.println("Connected to AWS IoT");
        mqttClient.subscribe("parking/space/1");
        mqttClient.subscribe("parking/space/2");
      } else {
        Serial.print("Failed to connect to AWS IoT, state: ");
        Serial.println(mqttClient.state());
        delay(5000);
      }
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming MQTT messages from AWS IoT
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Received message: ");
   Serial.println(message);

  // Handle messages based on the topic
  if (String(topic) == "parking/space/1") {
    // Perform actions for parking space 1
  } else if (String(topic) == "parking/space/2") {
    // Perform actions for parking space 2
  }
}

void handleClient(WiFiClient client) {
  // Read incoming data from edge devices
  if (client.available()) {
    String cardId = client.readStringUntil('\n');
    cardId.trim();

    Serial.print("Received card ID: ");
    Serial.println(cardId);

    // Check if card ID is registered in the SD card
    if (isCardRegistered(cardId)) {
      // If the card is registered, send a command to open the servo
      client.println("OPEN_SERVO");
    } else {
      // If the card is not registered, send a command to display a message on the OLED
      client.println("CARD_NOT_REGISTERED");
    }
  }
}

bool isCardRegistered(const String& cardId) {
  // Check if the card ID is in the SD card
  File file = SD.open("registered_cards.txt", FILE_READ);
  while (file.available()) {
    String line = file.readStringUntil('\n');
    line.trim();
    if (line == cardId) {
      file.close();
      return true;
    }
  }
  file.close();
  return false;
}

