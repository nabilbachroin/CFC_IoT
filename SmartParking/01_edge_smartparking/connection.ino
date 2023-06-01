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


void sendDataToServer() {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Make json objeck
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

    http.begin("http://192.168.0.0/NodeMCU_RC522_Mysql/postData.php");
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST(postData);   //Send the request
    String payload = http.getString();    //Get the response payload

    Serial.println("httpCode= " + httpCode);    //Print HTTP return code
    Serial.println(payload);                    //Print request response payload

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

