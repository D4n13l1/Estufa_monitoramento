///////////////////////////////////TELAS//////////////////////////
void Tela1() //Tela mostrando hora, se está gravando, e
{
  lcd.setCursor(0, 0);
  if (hour() < 10) {
    lcd.print("0");
    lcd.print(hour());
  }
  else lcd.print(hour());
  lcd.print(F(":"));
  if (minute() < 10) {
    lcd.print("0");
    lcd.print(minute());
    lcd.print(" ");
  }
  else lcd.print(minute());
  lcd.setCursor(5, 0);
  lcd.print(F(" "));
  //--------------------Contador de gravações-----------------------
  lcd.setCursor(6, 0);
  lcd.print(countGrav);
  lcd.print("          ");

  //----------------------------------------------------------------
  //-----------------Símbolos tela inicial----------------------------
  lcd.setCursor(15, 0);
  if (g == true) //Símbolo de gravação na tela principal
  {
    if ((millis() - millisTarefa1) < 500) {
      lcd.print(" ");
    }
    else {
      lcd.printByte(0);
    }
  }
  if ((millis() - millisTarefa1) > 1000) millisTarefa1 = millis();
  //------------------------------------------------------------------

  //----------------------------------------------------------------
  lcd.setCursor(0, 1);
  if (v == true || g == true) {
    lcd.print("T: ");
    lcd.print(totalizador);
    lcd.print("ml/m         ");
  }
  else
    lcd.print("Monitor. Estufa ");
}

void Tela2() {
  lcd.print(F("               "));
  lcd.setCursor(0, 0);
  lcd.print(F("Modo de gravacao"));
  lcd.setCursor(0, 1);
  lcd.print(F("                "));
}
void Tela3() {
  lcd.setCursor(0, 0);
  lcd.print(F("    Sensores    "));
  lcd.setCursor(0, 1);
  lcd.print(F("                "));
}
void Tela20() {
  lcd.setCursor(0, 0);
  lcd.print(F("Modo de gravacao"));
  lcd.setCursor(0, 1);
  lcd.print(F("Iniciar/Terminar"));
  if (digitalRead(botao_MENOS) == HIGH)  //iniciar a gravação
  {
    if (!SD.begin(CS_PIN))
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F(" Cartao SD "));
      lcd.setCursor(0, 1);
      lcd.print(F("nao encontrado "));
      delay(1000);
      g = false;
      return;
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("   Gravacao    "));
      lcd.setCursor(0, 1);
      lcd.print(F("   iniciada    "));
      g = true;
      GravaSD();
      v = true;
      tela = 1;
      delay(1100);
    }
  }
  else if (digitalRead(botao_MAIS) == HIGH) //encerrar a gravação
  {
    lcd.clear();
    if (!SD.begin(CS_PIN))
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F(" Cartao SD "));
      lcd.setCursor(0, 1);
      lcd.print(F("nao encontrado "));
      delay(500);
      g = false;
      return;
    }
    g = false;
    //      EEPROM[0] = g;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("   Gravacao    "));
    lcd.setCursor(0, 1);
    lcd.print(F("   encerrada   "));
    tela = 1;
    turnSensorOff();
    totalizador = 0;
    resetEeprom();
    delay(1000);
    lcd.clear();
  }
}
void Tela30() {
  lcd.setCursor(0, 0);
  lcd.print(F("    Sensor 1    "));
  lcd.setCursor(0, 1);
  lcd.print(tmpChan0);
  lcd.print(F("C   "));

  lcd.setCursor(8, 1);
  lcd.print(hmdChan0);
  lcd.print(F("%     "));
}
void Tela31() {
  lcd.setCursor(0, 0);
  lcd.print(F("    Sensor 2    "));
  lcd.setCursor(0, 1);
  lcd.print(tmpChan1);
  lcd.print(F("C   "));
  lcd.setCursor(8, 1);
  lcd.print(hmdChan1);
  lcd.print(F("%     "));
}
void Tela32() {
  lcd.setCursor(0, 0);
  lcd.print(F("  Sensor vazao  "));
  lcd.setCursor(0, 1);
  lcd.print(vazao,2); 
  //    lcd.setCursor(4, 1);
  lcd.print(F("Kg/s            "));
}
void Tela321() {
  lcd.setCursor(0, 0);
  lcd.print(F("Sensor de vazao "));
  lcd.setCursor(0, 1);
  lcd.print("   ligar/desl   ");
  if (digitalRead(botao_MENOS) == HIGH) {
    turnSensorOn();
    v = true;
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(" Sensor Ligado  ");
    delay(1000);
    tela = 32;
  }
  else if (digitalRead(botao_MAIS) == HIGH) {
    if (g == false) {
      turnSensorOff();
      v = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sensor desligado");
      delay(1000);
      tela = 32;
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print("  gravacao em   ");
      lcd.setCursor(0, 1);
      lcd.print("   andamento    ");
      delay(1000);
      lcd.setCursor(0, 0);
      lcd.print("  impossivel    ");
      lcd.setCursor(0, 1);
      lcd.print("   desligar     ");
      delay(1000);
      tela = 32;
    }
  }
}
