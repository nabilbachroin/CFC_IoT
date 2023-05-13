#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
  while (!Serial); // Waiting for Serial Monitor
  Serial.println("\nI2C Scanner");
}

void loop() {
  byte error, address;
  int devices_found = 0;

  Serial.println("Scanning...");

  for (address = 1; address < 127; address++ ) {
    // Menggunakan Wire.beginTransmission() untuk memulai transmisi ke perangkat
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    // Jika tidak ada error, berarti perangkat ditemukan
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      devices_found++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }    
  }

  if (devices_found == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("done\n");
  }

  // Tunggu 5 detik untuk scan selanjutnya
  delay(5000);
}
