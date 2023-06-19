void checkConnection()
{
  if(WiFi.status() == WL_CONNECTED)
    {
      if(after_disconnect==true)
        {
          get_update_from_temporary_register_table();
          writeDatabase(SD, "/registered.txt", "/status_and_balance.txt", "/availableSlots.txt");
          sendDataToServer();
        }
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
          get_update_from_temporary_register_table();
          writeDatabase(SD, "/registered.txt", "/status_and_balance.txt", "/availableSlots.txt");
        }
      after_disconnect=false;
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
              after_disconnect=true;
              //Serial.println("WiFi not connected");
            }
          else 
            {
              get_update_from_temporary_register_table();
              writeDatabase(SD, "/registered.txt", "/status_and_balance.txt", "/availableSlots.txt");
              sendDataToServer();
              break;
            }
        }
    }
}

void get_update_from_temporary_register_table()
  {
    HTTPClient http;
    http.begin("http://44.197.96.78/dashboard/updateDATAEsp.php");
    int httpCode = http.GET();
    if (httpCode > 0) 
      {
        String payload = http.getString();
        Serial.println("payload: " + payload);
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, payload);
        if (error)
          {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
          }
        cardCount = doc.size();
        for (int i = 0; i < cardCount; i++) 
          {
            cardDatabase[i].UID = doc[i]["UID"].as<String>();
            cardDatabase[i].name = doc[i]["name"].as<String>();
            cardDatabase[i].status = doc[i]["status"].as<String>();
            cardDatabase[i].balance = doc[i]["balance"].as<int>();
          }
      }
    else 
      {
        Serial.println("Error on HTTP request");
      }
    http.end();
  }


void sendUID() {
  Serial.println("Starting sendUID...");
  if(WiFi.status() == WL_CONNECTED) 
  {
    Serial.println("WiFi is connected...");
    HTTPClient http;

    String UIDresultSend, postData;
    UIDresultSend = cardUID;

    postData = "UIDresult=" + UIDresultSend;

    Serial.println("Attempting to connect to server...");
    http.begin("http://44.197.96.78/dashboard/getUID.php/");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    Serial.println("Attempting to send data...");
    Serial.println(postData);
    int httpCode = http.POST(postData);   //Send the request
    String payload = http.getString();    //Get the response payload

    Serial.println("httpCode= " + String(httpCode));    // Print HTTP return code
    Serial.print("payload= ");
    Serial.println(payload);                    //Print request response payload
    Serial.println("Finished sendDataToServer.");
    http.end();
  } 
  else 
  {
    Serial.println("WiFi not connected");
  }
}

void sendDataToServer() {
  Serial.println("Starting sendDataToServer...");
  if(WiFi.status() == WL_CONNECTED) 
    {
      Serial.println("WiFi is connected...");
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

      Serial.println("Attempting to connect to server...");
      http.begin("http://44.197.96.78/dashboard/postdata.php/");
      http.addHeader("Content-Type", "application/json");

      Serial.println("Attempting to send data...");
      Serial.println(postData);
      int httpCode = http.POST(postData);   //Send the request
      String payload = http.getString();    //Get the response payload

      Serial.println("httpCode= " + String(httpCode));    // Print HTTP return code
      Serial.print("payload= ");
      Serial.println(payload);                    //Print request response payload
      Serial.println("Finished sendDataToServer.");
      http.end();
    } 
  else 
    {
      Serial.println("WiFi not connected");
    }
}

