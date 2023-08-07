#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
const int SDA_PIN = 21;
const int SCL_PIN = 22;
Adafruit_SSD1306 display(128, 64, &Wire, -1);
void setupDisplay();


void setup() { 
  Serial.begin(9600);
  Hello();
}

void loop(){
}
void Hello() 
  {
    Wire.begin(SDA_PIN, SCL_PIN);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(16, 12);
    display.println("HELLO...");
    display.setTextSize(1);
    display.setCursor(16, 38);
    display.println("Team 4, CFC IoT");
    display.display();
  }


