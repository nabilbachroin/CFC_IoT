#include <Arduino.h>
#include <DFPlayerMini_Fast.h>

DFPlayerMini_Fast speaker;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
Serial2.begin(9600, SERIAL_8N1, 4, 2); // RX, TX

if (!speaker.begin(Serial2)) {  // Use the Serial2
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  } 
delay(1000);
playSpeaker("system_starting.mp3");
Serial.println("lagi muter");
playSpeaker("Welcome-pleaseenter.mp3");
playSpeaker("Sorry-parklot_full.mp3");
playSpeaker("Thankyou-becareful_otr.mp3");
}

void loop() {
  // put your main code here, to run repeatedly:

}

void playSpeaker(const char* music)
{
  if (strcmp(music, "system_starting.mp3") == 0) {speaker.play(1); delay(4000);}
  else if (strcmp(music, "Welcome-pleaseenter.mp3") == 0) {speaker.play(2); delay(1700);}
  else if (strcmp(music, "Sorry-parklot_full.mp3") == 0) {speaker.play(3); delay(3000);}
  else if (strcmp(music, "Thankyou-becareful_otr.mp3") == 0) {speaker.play(4); delay(3000);}
}
