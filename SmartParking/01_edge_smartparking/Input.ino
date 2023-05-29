void readRFID()
  {
    if ( ! rfid.PICC_IsNewCardPresent()) return;
    if ( ! rfid.PICC_ReadCardSerial()) return;
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) 
      {
        Serial.println(F("Your tag is not of type MIFARE Classic."));
        return;
      }
    for (byte i = 0; i < 4; i++) nuidPICC[i] = rfid.uid.uidByte[i];
    cardUID = "";
    for (byte i = 0; i < 4; i++) cardUID += (nuidPICC[i] < 0x10 ? "0" : "") + String(nuidPICC[i], HEX);
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

//  The findCard and addCard functions are used to manipulate in-memory data structures 
//  because the Arduino IDE does not support all standard C++ features

void addCard(String UID, String name, String status, int balance) 
  {
    if (cardCount >= MAX_CARDS) {
      Serial.println("Database is full, can not add new card");
      return;
    }

    cardDatabase[cardCount].UID = UID;
    cardDatabase[cardCount].name = name;
    cardDatabase[cardCount].status = status;
    cardDatabase[cardCount].balance = balance;
    cardCount++;
  }


void readDatabase(fs::FS &fs, const char * registeredPath, const char * statusPath) 
{
  // read registered.txt
  File registeredFile = fs.open(registeredPath);
  cardCount = 0; // reset jumlah kartu
  while(registeredFile.available()) {
    String line = registeredFile.readStringUntil('\n');
    String uid = line.substring(0, line.indexOf('@') - 1);
    String name = line.substring(line.indexOf('@') + 1);
    cardDatabase[cardCount].UID = uid;
    cardDatabase[cardCount].name = name;
    cardCount++;
  }
  registeredFile.close();

  // read status_and_balance.txt
  File statusFile = fs.open(statusPath);
  int i = 0;
  while(statusFile.available()) {
    String line = statusFile.readStringUntil('\n');
    String uid = line.substring(0, line.indexOf('@') - 1);
    String status = line.substring(line.indexOf('@') + 1, line.indexOf('$') - 1);
    int balance = line.substring(line.indexOf('$') + 1).toInt();
    if (cardDatabase[i].UID == uid) {
      cardDatabase[i].status = status;
      cardDatabase[i].balance = balance;
    }
    i++;
  }
  statusFile.close();
}

void writeDatabase(fs::FS &fs, const char * registeredPath, const char * statusPath) 
{
  // write registered.txt
  File registeredFile = fs.open(registeredPath, FILE_WRITE);
  for(int i = 0; i < cardCount; i++) {
    registeredFile.println(cardDatabase[i].UID + "@" + cardDatabase[i].name);
  }
  registeredFile.close();

  // write status_and_balance.txt
  File statusFile = fs.open(statusPath, FILE_WRITE);
  for(int i = 0; i < cardCount; i++) {
    statusFile.println(cardDatabase[i].UID + "@" + cardDatabase[i].status + "$" + String(cardDatabase[i].balance));
  }
  statusFile.close();
}


void readFile(fs::FS &fs, const char * path)
  {
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