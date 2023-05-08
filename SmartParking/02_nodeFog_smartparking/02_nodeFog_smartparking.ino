#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <SD.h>
#include <MFRC522.h>
#include <Ping.h>

// Wi-Fi credentials
char* ssid = "Bachroin";
const char* password = "masnabilganteng";

// AWS IoT endpoint and credentials
// const char* awsEndpoint = "your-aws-iot-endpoint";
// const char* awsCert = "your-aws-certificate";
// const char* awsPrivateKey = "your-aws-private-key";

// SD card pins
// const int sdCSPin = 5;

// RFID pins and object
// #define RST_PIN 22
// #define SS_PIN 21
// MFRC522 rfid(SS_PIN, RST_PIN);

// Servo pins
// const int servoPin = 18;

WiFiServer server(80);
WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup() {
  Serial.begin(115200);

  // Initialize SPI for SD card and RFID
  // SPI.begin();

  // Initialize SD card
  // if (!SD.begin(sdCSPin)) {
  //   Serial.println("SD card initialization failed");
  //   return;
  // }
  // Serial.println("SD card initialized");

  // Initialize RFID
  // rfid.PCD_Init();
  // Serial.println("RFID initialized");

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


