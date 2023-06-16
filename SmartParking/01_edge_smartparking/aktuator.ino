// name of mp3 file:
// system_starting.mp3
// Welcome-pleaseenter.mp3
// Sorry-parklot_full.mp3
// Thankyou-becareful_otr.mp3
// balance_not_enough.mp3
// not_registered_wouldulike2register.mp3
// registration_fail.mp3
// thankyou_for_register.mp3
// 

void checkRelay()
  {
    if(slotData.electricChargingSlots>0) digitalWrite(relay, HIGH);
    else digitalWrite(relay, LOW);
  }

void playSpeaker(const char* music)
{
  if (strcmp(music, "system_starting.mp3") == 0) {speaker.play(1); delay(4000);}                          // playSpeaker("system_starting.mp3");
  else if (strcmp(music, "Welcome-pleaseenter.mp3") == 0) {speaker.play(2); delay(1700);}                 // playSpeaker("Welcome-pleaseenter.mp3");
  else if (strcmp(music, "Sorry-parklot_full.mp3") == 0) {speaker.play(3); delay(3000);}                  // playSpeaker("Sorry-parklot_full.mp3");
  else if (strcmp(music, "Thankyou-becareful_otr.mp3") == 0) {speaker.play(4); delay(3000);}              // playSpeaker("Thankyou-becareful_otr.mp3");
  else if (strcmp(music, "balance_not_enough.mp3") == 0) {speaker.play(5); delay(3100);}                  // playSpeaker("balance_not_enough.mp3");
  else if (strcmp(music, "not_registered_wouldulike2register.mp3") == 0) {speaker.play(6); delay(3100);}  // playSpeaker("not_registered_wouldulike2register.mp3");
  else if (strcmp(music, "registration_fail.mp3") == 0) {speaker.play(7); delay(3000);}                   // playSpeaker("registration_fail.mp3");
  else if (strcmp(music, "thankyou_for_register.mp3") == 0) {speaker.play(8); delay(2500);}               // playSpeaker("thankyou_for_register.mp3");
}

void openGate()
  {
    for (int pos = 180; pos >= 90; pos -= 1) 
      {
        gateServo.write(pos);
        delay(15);
      }
    delay(1500);
    // read proximity
    back_to_counter:
    for (int i = 0; i < 100; i++) // for 10 seconds
      {
        gateServo.write(90);
        delay(197);
        if(digitalRead(proximitySensor) == LOW) 
          {
            delay(2500); // to make sure that the car is already go away
            break;
          }
        delay(100);
      }
    for (int pos = 90; pos <= 180; pos += 1) 
      {
        gateServo.write(pos);
        delay(33);
        if(digitalRead(proximitySensor) == LOW) goto back_to_counter;
      }
  }

void setup_LedButton()
  {
    pinMode(relay,OUTPUT);
    pinMode(ledBluePin, OUTPUT);
    pinMode(ledRedPin, OUTPUT);
    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledBluePin, LOW);
    pinMode(led_online, OUTPUT);
    pinMode(led_offline, OUTPUT);
    digitalWrite(led_online, LOW);
    digitalWrite(led_offline, LOW);
    pinMode(buttonGreen, INPUT_PULLUP);
    pinMode(buttonRed, INPUT_PULLUP);
  }