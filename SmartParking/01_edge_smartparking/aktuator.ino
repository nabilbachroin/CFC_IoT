// void setupServo()
//   {
//     gateServo.setPeriodHertz(50);             // standard 50 hz servo
//     gateServo.attach(SERVO_PIN, 500, 2400);   // attaches the servo on pin 2 to the servo object
//                                             // and set min and max pulse widths
//   }

// void testServo()
//   {
//     gateServo.write(90);  // tell servo to go to position '90'
//     delay(1000);        // wait 1s
//     gateServo.write(0);   // tell servo to go to position '0'
//     delay(1000);        // wait 1s
//   }

void openGate()
  {
    for (int pos = 180; pos >= 90; pos -= 1) {
    gateServo.write(pos);
    delay(15);}
    delay(2000);
    // Disini baca proximity
    for (int pos = 90; pos <= 180; pos += 1) {
    gateServo.write(pos);
    delay(33);
  }
  }