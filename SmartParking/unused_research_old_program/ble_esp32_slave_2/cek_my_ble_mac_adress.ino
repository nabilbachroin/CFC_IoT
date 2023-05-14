// #include <WiFi.h>
// #include <BluetoothSerial.h>

// BluetoothSerial SerialBT;

// void setup() {
//   Serial.begin(115200);
//   SerialBT.begin("Slave_SmartParking_2"); // Nama Bluetooth yang digunakan pada perangkat ESP32

//   // Dapatkan alamat MAC Bluetooth
//   uint64_t mac = ESP.getEfuseMac();
//   uint8_t* baseMac = (uint8_t*)(void*)&mac;
//   char macStr[18];
//   snprintf(macStr, 18, "%02X:%02X:%02X:%02X:%02X:%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);

//   // Cetak alamat MAC Bluetooth ke Serial Monitor
//   Serial.print("Bluetooth MAC Address: ");
//   Serial.println(macStr);

//   delay(5000);
// }

// void loop() {
//   // Anda bisa menambahkan kode lain di sini
// }
