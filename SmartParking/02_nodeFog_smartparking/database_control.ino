// bool isCardRegistered(const String& cardId) {
//   // Check if the card ID is in the SD card
//   File file = SD.open("registered_cards.txt", FILE_READ);
//   while (file.available()) {
//     String line = file.readStringUntil('\n');
//     line.trim();
//     if (line == cardId) {
//       file.close();
//       return true;
//     }
//   }
//   file.close();
//   return false;
// }