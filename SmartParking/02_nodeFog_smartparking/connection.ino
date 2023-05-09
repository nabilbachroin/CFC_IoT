


// KODE DIBAWAH INI KODE SEBELUM GANTI ESP32
// TINGGAL BLOK SAMPAI BAWAH KEMUDIAN BARENGKAN UNCOMENNT NYA

// void connectToWiFiAndAWS() {
//   // Connect to Wi-Fi
//   Serial.println();
//   Serial.println();
//   Serial.print("Connecting to ");
//   Serial.println(ssid);
//   if (WiFi.status() != WL_CONNECTED) {
//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED) {
//       delay(500);
//       Serial.println("Connecting to Wi-Fi...");
//     }
//     Serial.println("Connected to Wi-Fi");
//     Serial.println("IP address: ");
//     Serial.println(WiFi.localIP());
//   }

//   // Configure MQTT settings
//   // mqttClient.setServer(awsEndpoint, 8883);
//   // mqttClient.setCallback(mqttCallback);

//   // Connect to MQTT
//   // if (!mqttClient.connected()) {
//   //   while (!mqttClient.connected()) {
//   //     Serial.println("Connecting to AWS IoT...");
//   //     if (mqttClient.connect("ESP32FogNode", awsCert, awsPrivateKey)) {
//   //       Serial.println("Connected to AWS IoT");
//   //       mqttClient.subscribe("parking/space/1");
//   //       mqttClient.subscribe("parking/space/2");
//   //     } else {
//   //       Serial.print("Failed to connect to AWS IoT, state: ");
//   //       Serial.println(mqttClient.state());
//   //       delay(5000);
//   //     }
//   //   }
//   // }
// }

// // void mqttCallback(char* topic, byte* payload, unsigned int length) {
// //   // Handle incoming MQTT messages from AWS IoT
// //   String message;
// //   for (unsigned int i = 0; i < length; i++) {
// //     message += (char)payload[i];
// //   }
// //   Serial.print("Received message: ");
// //    Serial.println(message);

// //   // Handle messages based on the topic
// //   if (String(topic) == "parking/space/1") {
// //     // Perform actions for parking space 1
// //   } else if (String(topic) == "parking/space/2") {
// //     // Perform actions for parking space 2
// //   }
// // }

// // void handleClient(WiFiClient client) {
// //   // Read incoming data from edge devices
// //   if (client.available()) {
// //     String cardId = client.readStringUntil('\n');
// //     cardId.trim();

// //     Serial.print("Received card ID: ");
// //     Serial.println(cardId);

// //     // Check if card ID is registered in the SD card
// //     if (isCardRegistered(cardId)) {
// //       // If the card is registered, send a command to open the servo
// //       client.println("OPEN_SERVO");
// //     } else {
// //       // If the card is not registered, send a command to display a message on the OLED
// //       client.println("CARD_NOT_REGISTERED");
// //     }
// //   }
// // }
