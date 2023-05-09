#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;
bool deviceConnected = false;

class MyServerCallbacks: public BLEServerCallbacks 
  {
    void onConnect(BLEServer* pServer) 
      {
        deviceConnected = true;
        Serial.println("Client connected");
      }
    void onDisconnect(BLEServer* pServer) 
      {
        deviceConnected = false;
        Serial.println("Client disconnected");
      }
  };

// test ble 09 may 2023
String receivedData = "";
class MyCharacteristicCallbacks : public BLECharacteristicCallbacks 
{
  void onWrite(BLECharacteristic *pCharacteristic) 
  {
    std::string value = pCharacteristic->getValue();
    receivedData = String(value.c_str());
    Serial.print("Received data: ");
    Serial.println(receivedData);
  }
};

void setup()
  {
    Serial.begin(115200);
    setupBLE();
  }

void loop()
  {
    if (deviceConnected) 
      {
        Serial.print("Received data: ");
        Serial.println(receivedData);
        receivedData = "";
      }
    delay(1000);
  }



// KODE DIBAWAH INI KODE SEBELUM GANTI ESP32
// TINGGAL BLOK SAMPAI BAWAH KEMUDIAN BARENGKAN UNCOMENNT NYA

// #include <ESP8266WiFi.h>
// // #include <WiFi.h>
// // #include <PubSubClient.h>
// // #include <SPI.h>
// // #include <SD.h>
// // #include <MFRC522.h>
// #include <ESP8266Ping.h>

// // Indicator for Internet connection
// const int led1 = 4; //D2
// const int led2 = 16; //D0
// bool isConnectedToInternet = false;

// // Wi-Fi credentials
// const char* ssid = "NabilBachroin";
// const char* password = "nabilganteng";

// // AWS IoT endpoint and credentials
// // const char* awsEndpoint = "your-aws-iot-endpoint";
// // const char* awsCert = "your-aws-certificate";
// // const char* awsPrivateKey = "your-aws-private-key";

// // SD card pins
// // const int sdCSPin = 5;

// // RFID pins and object
// // #define RST_PIN 22
// // #define SS_PIN 21
// // MFRC522 rfid(SS_PIN, RST_PIN);

// // Servo pins
// // const int servoPin = 18;

// // WiFiServer server(80);
// // WiFiClient espClient;
// // PubSubClient mqttClient(espClient);

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Test Serial");

//   pinMode(led1, OUTPUT);
//   pinMode(led2, OUTPUT);
//   digitalWrite(led1, LOW);
//   digitalWrite(led2, LOW);

//   // Initialize SPI for SD card and RFID
//   // SPI.begin();

//   // Initialize SD card
//   // if (!SD.begin(sdCSPin)) {
//   //   Serial.println("SD card initialization failed");
//   //   return;
//   // }
//   // Serial.println("SD card initialized");

//   // Initialize RFID
//   // rfid.PCD_Init();
//   // Serial.println("RFID initialized");

//   // Initialize Wi-Fi and MQTT
//   connectToWiFiAndAWS();

//   // Start the server
//   // server.begin();
// }

// void loop() {
//   if (WiFi.status() != WL_CONNECTED) {
//     WiFi.begin(ssid, password);
//   }
  
//   isConnectedToInternet = Ping.ping("www.google.com");
//   if (isConnectedToInternet) {
//     digitalWrite(led1, HIGH);
//     digitalWrite(led2, LOW);
//   } else {
//     digitalWrite(led1, LOW);
//     digitalWrite(led2, HIGH);
//   }

//   // Check Wi-Fi and MQTT connection
//   // if (WiFi.status() != WL_CONNECTED || !mqttClient.connected()) {
//   //   connectToWiFiAndAWS();
//   // }

//   // Handle incoming MQTT messages
//   // mqttClient.loop();

//   // Handle incoming client connections (from edge devices)
//   // WiFiClient client = server.available();
//   // if (client) {
//   //   Serial.println("Client connected");
//   //   handleClient(client);
//   //   client.stop();
//   // }
// }


