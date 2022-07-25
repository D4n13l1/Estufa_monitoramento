
void GravaSD() {
  if (g == true) {
    turnSensorOn();
    if (millis() >= time_now + period) {
      time_now += period;
      double medTemp0 = totTemp0 / contador;
      double medHum0 = totHum0 / contador;
      double medTemp1 = totTemp1 / contador;
      double medHum1 = totHum1 / contador;      
      UAChan0 = UA(medTemp0, medHum0);
      UAChan1 = UA(medTemp1, medHum1);
      taxaSecagem = (UAChan0-UAChan1)*vazao;
      totalizador+=taxaSecagem;
      
      File dataFile = SD.open("Estufa.csv", FILE_WRITE);
      String dataString = "";
      dataString += String(String(day()) + "/" + String(month()) + "/" + String(year()) + " " + String(hour()) + ":" + String(minute()) + ":" + String(second()));
      dataString += ",";      //separa cada dado com uma virgula
      dataString += String(medTemp0);
      dataString += ",";
      dataString += String(medHum0);
      dataString += ",";
      dataString += String(medTemp1);
      dataString += ",";
      dataString += String(medHum1);
      dataString += ",";
      dataString += String(UAChan0);
      dataString += ",";
      dataString += String(UAChan1);
      dataString += ",";
      dataString += String(taxaSecagem);
      dataString += ",";
      dataString += String(countGrav);

      if (dataFile) {
        dataFile.println(dataString);
        dataFile.close();
        Serial.println(dataString);
        countGrav++;
        EEPROMWriteInt(1, countGrav);       //Posicao 1 e 2 da EEPROM

        totTemp0 = 0;
        totTemp1 = 0;
        totHum0 = 0;
        totHum1 = 0;
        taxaSecagem = 0;
        contador = 0;
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
    }
  }
}
