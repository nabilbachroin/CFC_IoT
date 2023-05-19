// name of mp3 file:
// system_starting.mp3
// Welcome-pleaseenter.mp3
// Sorry-parklot_full.mp3
// Thankyou-becareful_otr.mp3
// 

void playSpeaker(String music)
  {
    speaker.volume(10);  // 0-30
    if (music=="system_starting.mp3") speaker.play(1);
    else if (music=="Welcome-pleaseenter.mp3") speaker.play(2);
    else if (music=="Sorry-parklot_full.mp3") speaker.play(3);
    else if (music=="Thankyou-becareful_otr.mp3") speaker.play(4);
    
    while (speaker.isPlaying()) delay(10);
  }

void openGate()
  {
    for (int pos = 180; pos >= 90; pos -= 1) 
      {
        gateServo.write(pos);
        delay(15);
      }
    delay(2000);
    // read proximity
    back_to_counter:
    for (int i = 0; i < 100; i++) // for 10 seconds
      {
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
        if(digitalRead(proximitySensor) == LOW) 
          {
            gateServo.write(90);
            delay(777);
            goto back_to_counter;
          }
      }
  }

  void setup_LedButton()
    {
      pinMode(ledBluePin, OUTPUT);
      pinMode(ledRedPin, OUTPUT);
      digitalWrite(ledRedPin, LOW);
      digitalWrite(ledBluePin, LOW);
      pinMode(buttonGreen, INPUT_PULLUP);
      pinMode(buttonRed, INPUT_PULLUP);
    }