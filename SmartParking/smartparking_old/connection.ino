void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectToAWS() {
  Serial.print("Connecting to AWS IoT...");

  net.setCACert(AWS_ROOT_CA);
  net.setCertificate(AWS_CERTIFICATE);
  net.setPrivateKey(AWS_PRIVATE_KEY);

  client.begin(AWS_IOT_ENDPOINT, 8883, net);
  
  while (!client.connect("ESP32Client")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("Connected to AWS IoT!");

  // Subscribe to topics
  client.subscribe("smartparking/openGate");
  client.subscribe("smartparking/closeGate");
}

void messageHandler(String &topic, String &payload) {
  Serial.println("Received [" + topic + "]: " + payload);

  if (topic == "smartparking/openGate") {
    openGate();
  } else if (topic == "smartparking/closeGate") {
    closeGate();
  }
}