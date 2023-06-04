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

CardData* findCard(String UID) 
  {
    for (int i = 0; i < cardCount; i++) {
      if (cardDatabase[i].UID == UID) {
        return &cardDatabase[i]; // back to card
      }
    }
    return NULL; // if card not finding
  }

void readDatabase(fs::FS &fs, const char * registeredPath, const char * statusPath, const char * slotPath) 
  {
    // read registered.txt
    File registeredFile = fs.open(registeredPath);
    cardCount = 0; 
    while(registeredFile.available()) 
      {
        String line = registeredFile.readStringUntil('%');
        line.trim(); 
        String uid = line.substring(line.indexOf('#') + 1, line.indexOf('@') - 1);
        uid.trim();
        String name = line.substring(line.indexOf('@') + 1, line.indexOf('%') - 1);
        name.trim();
        cardDatabase[cardCount].UID = uid;
        cardDatabase[cardCount].name = name;
        Serial.println("Read card data: " + uid + " @" + name);
        cardCount++;
      }
    registeredFile.close();

    // read status_and_balance.txt
    File statusFile = fs.open(statusPath);
    int i = 0;
    while(statusFile.available()) 
      {
        String line = statusFile.readStringUntil('%');
        line.trim();
        String uid = line.substring(line.indexOf('#') + 1, line.indexOf('@') - 1);
        uid.trim();
        String status = line.substring(line.indexOf('@') + 1, line.indexOf('$') - 1);
        status.trim();
        int balance = line.substring(line.indexOf('$') + 1, line.indexOf('%') - 1).toInt();
        if (cardDatabase[i].UID == uid) 
          {
            cardDatabase[i].status = status;
            cardDatabase[i].balance = balance;
          }
        Serial.println("Read status data: " + uid + " @" + status + " $" + String(balance));
        i++;
      }
    statusFile.close();

    // read availableSlots.txt
    File slotFile = fs.open(slotPath);
    if(slotFile.available()) 
      {
        String line = slotFile.readStringUntil('%');
        line.trim();
        String parkingSlots = line.substring(line.indexOf('@') + 1, line.indexOf('&') - 1);
        String electricChargingSlots = line.substring(line.indexOf('&') + 1, line.indexOf('%'));
        slotData.parkingSlots = parkingSlots.toInt();
        slotData.electricChargingSlots = electricChargingSlots.toInt();
      }
    slotFile.close();
    checkRelay();
    if(WiFi.status() == WL_CONNECTED) sendDataToServer();
  }

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
  
void writeDatabase(fs::FS &fs, const char * registeredPath, const char * statusPath, const char * slotPath) 
  {
    // write registered.txt
    File registeredFile = fs.open(registeredPath, FILE_WRITE);
    for(int i = 0; i < cardCount; i++) 
      {
        if(i==cardCount-1 && i!=0) registeredFile.print("#" + cardDatabase[i].UID + " @" + cardDatabase[i].name + "%");
        else registeredFile.println("#" + cardDatabase[i].UID + " @" + cardDatabase[i].name + "%");
      }
    registeredFile.close();

    // write status_and_balance.txt
    File statusFile = fs.open(statusPath, FILE_WRITE);
    for(int i = 0; i < cardCount; i++) 
      {
        if(i==cardCount-1 && i!=0) statusFile.print("#" + cardDatabase[i].UID + " @" + cardDatabase[i].status + " $" + String(cardDatabase[i].balance) + "%");
        else statusFile.println("#" + cardDatabase[i].UID + " @" + cardDatabase[i].status + " $" + String(cardDatabase[i].balance) + "%");
      }
    statusFile.close();

    // write availableSlots.txt
    File slotFile = fs.open(slotPath, FILE_WRITE);
    slotFile.print("@" + String(slotData.parkingSlots) + " &" + String(slotData.electricChargingSlots) + "%");
    slotFile.close();
    checkRelay();
    sendDataToServer();
  }