void checkConnection()
{
  if(WiFi.status() == WL_CONNECTED)
    {
      WiFiClient client;
      int httpPort = 80;
      if (!client.connect(host, httpPort)) 
        {
          digitalWrite(led_online, LOW);
          digitalWrite(led_offline, HIGH);
          //Serial.println("Ping failed");
          client.stop();
        }
      else 
        {
          digitalWrite(led_online, HIGH);
          digitalWrite(led_offline, LOW);
          //Serial.println("Ping successful");
          client.stop();
        }
    }
  else 
    {
      WiFi.begin(ssid, password);
      for(int cn=0; cn<1500; cn++)
        {
          if(WiFi.status() != WL_CONNECTED) 
            {
              digitalWrite(led_online, LOW);
              digitalWrite(led_offline, HIGH);
              //Serial.println("WiFi not connected");
            }
          else 
            {
              sendDataToServer();
              break;
            }
        }
    }
}

void sendUID() {
  Serial.println("Starting sendUID...");  // Add this line
  if(WiFi.status() == WL_CONNECTED) 
  {
    Serial.println("WiFi is connected...");  // Add this line
    HTTPClient http;

    String UIDresultSend, postData;
    UIDresultSend = cardUID;

    postData = "UIDresult=" + UIDresultSend;

    Serial.println("Attempting to connect to server...");  // Add this line
    http.begin("http://44.197.96.78/dashboard/getUID.php/");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    Serial.println("Attempting to send data...");  // Add this line
    Serial.println(postData);
    int httpCode = http.POST(postData);   //Send the request
    String payload = http.getString();    //Get the response payload

    Serial.println("httpCode= " + String(httpCode));    // Print HTTP return code
    Serial.print("payload= ");
    Serial.println(payload);                    //Print request response payload
    Serial.println("Finished sendDataToServer.");  // Add this line
    http.end();
  } 
  else 
  {
    Serial.println("WiFi not connected");
  }
}

void sendDataToServer() {
  Serial.println("Starting sendDataToServer...");  // Add this line
  if(WiFi.status() == WL_CONNECTED) 
    {
      Serial.println("WiFi is connected...");  // Add this line
      HTTPClient http;

      // Make json object
      DynamicJsonDocument doc(1024);

      // Fill the json object 
      for (int i = 0; i < cardCount; i++) {
        doc["CardData"][i]["UID"] = cardDatabase[i].UID;
        doc["CardData"][i]["name"] = cardDatabase[i].name;
        doc["CardData"][i]["status"] = cardDatabase[i].status;
        doc["CardData"][i]["balance"] = cardDatabase[i].balance;
      }
      doc["SlotData"]["parkingSlots"] = slotData.parkingSlots;
      doc["SlotData"]["electricChargingSlots"] = slotData.electricChargingSlots;

      // convert from json to string
      String postData;
      serializeJson(doc, postData);

      Serial.println("Attempting to connect to server...");  // Add this line
      http.begin("http://44.197.96.78/dashboard/postdata.php/");
      http.addHeader("Content-Type", "application/json");

      Serial.println("Attempting to send data...");  // Add this line
      Serial.println(postData);
      int httpCode = http.POST(postData);   //Send the request
      String payload = http.getString();    //Get the response payload

      Serial.println("httpCode= " + String(httpCode));    // Print HTTP return code
      Serial.print("payload= ");
      Serial.println(payload);                    //Print request response payload
      Serial.println("Finished sendDataToServer.");  // Add this line
      http.end();
    } 
  else 
    {
      Serial.println("WiFi not connected");
    }
}

