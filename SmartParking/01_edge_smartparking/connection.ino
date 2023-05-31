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
    for(int cn=0; cn<2000; cn++)
      {
        if(WiFi.status() != WL_CONNECTED) 
          {
            digitalWrite(led_online, LOW);
            digitalWrite(led_offline, HIGH);
            //Serial.println("WiFi not connected");
          }
        else break;
      }
    }
}
