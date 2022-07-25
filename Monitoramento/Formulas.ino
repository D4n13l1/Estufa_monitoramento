double UA(double Temp, double UR) //UMIDADE ABSOLUTA
{
  return ((UR/100) * 1330 * pow(M_E, ((17.62 * Temp) / (Temp + 243.12)))) / (Temp + 273.16);
}

double TS(double vazao, double UAint, double UAext) //Taxa de secagem
{
  return (UAint - UAext) * vazao;
}
double getTempChan0() {
  selChan0();
  selChan0();
  double b, c, x, i = 0;
  while (i < 11)
  {
    x = hdc1080.readTemperature();
    b = 0.95 * b + 0.05 * x;
    c = 0.95 * c + 0.05 * b;
    i++;
  }
  totTemp0 += tmpChan0;
  return c;
}

double getTempChan1() {
  selChan1();
  selChan1();
  double b, c, x, i = 0;
  while (i < 11)
  {
    x = hdc1080.readTemperature();
    b = 0.99 * b + 0.01 * x;
    c = 0.97 * c + 0.03 * b;
    i++;
  }
  totTemp1 += tmpChan1;
  return c;
}
double getHumidChan0() {
  selChan0();
  selChan0();
  double b, c, x, i = 0;
  while (i < 7) {
    x = hdc1080.readHumidity();
    b = 0.9 * b + 0.1 * x;
    c = 0.9 * c + 0.1 * b;
    i++;
  }
  totHum0 += hmdChan0;
  return c;
}
double getHumidChan1() {
  selChan1();
  selChan1();
  double b, c, x, i = 0;
  while (i < 7) {
    x = hdc1080.readHumidity();
    b = 0.9 * b + 0.1 * x;
    c = 0.9 * c + 0.1 * b;
    i++;
  }
  totHum1 += hmdChan1;
  return c;
}
void turnSensorOn() {
  digitalWrite(43, HIGH);
  digitalWrite(33, HIGH);
}
void turnSensorOff() {
  digitalWrite(43, LOW);
  digitalWrite(33, LOW);
}
