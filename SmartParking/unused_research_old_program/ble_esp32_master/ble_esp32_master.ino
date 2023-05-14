// // fc:f5:c4:19:70:9e  Slave 1
// // FC:F5:C4:19:72:6C  Slave 2

#include <BLESerial.h>

BLESerial bleSerial1;
BLESerial bleSerial2;

const char* slaveAddress1 = "fc:f5:c4:19:70:9e"; // Alamat MAC Bluetooth dari perangkat slave 1
const char* slaveAddress2 = "FC:F5:C4:19:72:6C"; // Alamat MAC Bluetooth dari perangkat slave 2

void setup() {
  Serial.begin(115200);
  bleSerial1.begin("MasterESP32_1");
  bleSerial2.begin("MasterESP32_2");

  Serial.println("Waiting for connections...");
  bleSerial1.connect(slaveAddress1);
  bleSerial2.connect(slaveAddress2);
  Serial.println("Connected to both slaves");
}

void loop() {
  bleSerial1.println("Hello from Master ESP32 to Slave 1!");
  bleSerial2.println("Hello from Master ESP32 to Slave 2!");
  delay(1000);
}










// #include <BluetoothSerial.h>

// BluetoothSerial SerialBT;

// // Alamat MAC Bluetooth dari perangkat slave
// const char* slaveAddresses[] = {"fc:f5:c4:19:70:9e", "FC:F5:C4:19:72:6C"}; // Ganti xx:xx:xx:xx:xx:xx dengan alamat MAC ESP32 slave kedua
// const int numSlaves = sizeof(slaveAddresses) / sizeof(slaveAddresses[0]);

// void setup() {
//   Serial.begin(115200);
//   SerialBT.begin("MasterESP32"); // Nama Bluetooth yang digunakan pada perangkat master
//   Serial.println("Waiting for connections...");

//   for (int i = 0; i < numSlaves; ++i) {
//     bool connected = false;
//     while (!connected) {
//       connected = SerialBT.connect(slaveAddresses[i]);
//       if (connected) {
//         Serial.printf("Connected to %s\n", slaveAddresses[i]);
//       } else {
//         Serial.printf("Failed to connect to %s. Retrying...\n", slaveAddresses[i]);
//         delay(2000);
//       }
//     }
//   }
// }

// void loop() {
//   for (int i = 0; i < numSlaves; ++i) {
//     SerialBT.connect(slaveAddresses[i]); // Sambungkan ke perangkat slave saat ini
//     SerialBT.println("Hello from Master ESP32!"); // Kirim data ke perangkat slave melalui Bluetooth
//     delay(1000);
//     SerialBT.disconnect(); // Putuskan koneksi dengan perangkat slave saat ini
//   }
// }
