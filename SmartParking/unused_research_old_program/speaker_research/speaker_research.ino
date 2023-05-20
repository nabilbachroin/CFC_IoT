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
speaker.play(1);
//playSpeaker("system_starting.mp3");
Serial.println("lagi muter");
delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void playSpeaker(String music)
  {
    speaker.volume(30);  // 0-30
    if (music=="system_starting.mp3") speaker.play(1);
    else if (music=="Welcome-pleaseenter.mp3") speaker.play(2);
    else if (music=="Sorry-parklot_full.mp3") speaker.play(3);
    else if (music=="Thankyou-becareful_otr.mp3") speaker.play(4);
    
    //while (speaker.isPlaying()) delay(10);
  }