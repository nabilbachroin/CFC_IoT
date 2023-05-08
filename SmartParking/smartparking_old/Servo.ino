void openGate() {
  parkingServo.write(0); // Set servo angle to 0 degrees (opened)
  delay(1000); // Wait for the servo to reach the position
}

void closeGate() {
  parkingServo.write(90); // Set servo angle to 90 degrees (closed)
  delay(1000); // Wait for the servo to reach the position
}