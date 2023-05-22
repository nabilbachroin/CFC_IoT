#include <FS.h>
#include <SD.h>
#include <SPI.h>

#define SD_CS 13 // Ubah ini sesuai dengan konfigurasi perangkat Anda.

void setup() {
  Serial.begin(9600);

  if (!SD.begin(SD_CS)) {
    Serial.println("Card Mount Failed");
    return;
  }

  readFile(SD, "/status_and_balance.txt");
  readFile(SD, "/registered.txt");
}

void loop() {
  // Tidak ada logika di loop.
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }
  
    Serial.println("File Content:");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}
