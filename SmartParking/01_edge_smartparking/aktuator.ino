void openGate()
  {
    for (int pos = 180; pos >= 90; pos -= 1) 
      {
        gateServo.write(pos);
        delay(15);
      }
    delay(2000);
    // Disini baca proximity
    for (int pos = 90; pos <= 180; pos += 1) 
      {
        gateServo.write(pos);
        delay(33);
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