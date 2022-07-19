
void GravaSD() {

  if (g == true) {
    turnSensorOn();
    if (millis() >= time_now + period) {
      
      time_now += period;

      File dataFile = SD.open("Estufa.csv", FILE_WRITE);
      String dataString = "";
      dataString += String(String(day()) + "/" + String(month()) + "/" + String(year() - 2000) + " " + String(hour()) + ":" + String(minute()) + ":" + String(second()));
/*      dataString += ",";      //separa cada dado com uma virgula
      dataString += String(tmpChan0);
      dataString += ",";
      dataString += String(hmdChan0);
      dataString += ",";
      dataString += String(tmpChan1);
      dataString += ",";
      dataString += String(hmdChan1);
      dataString += ",";
      dataString += String(vazao);
      dataString += ",";
      dataString += String(countGrav);
*/

      if (dataFile) {
        dataFile.println(dataString);
        dataFile.close();
        Serial.println(dataString);
        countGrav++;
        EEPROMWriteInt(1, countGrav);       //Posicao 1 e 2 da EEPROM
      }
      else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("    ERRO AO     "));
        lcd.setCursor(0, 1);
        lcd.print(F("  GRAVAR DADOS  "));
        g = false;
        delay(2000);
      }
      tempo++;
    }
  }
}
