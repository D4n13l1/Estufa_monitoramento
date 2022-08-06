double UA(double Temp, double UR) //UMIDADE ABSOLUTA
{
  return ((UR / 100) * 1330 * pow(M_E, ((17.62 * Temp) / (Temp + 243.12)))) / (Temp + 273.16);
}

double TS(double vazao, double UAint, double UAext) //Taxa de secagem
{
  return ((UAint - UAext) * vazao) * (3600 / 1.4);
}
double getTempChan0() {
  selChan0();
  selChan0();
  double x, i = 0;
  while (i < 11)
  {
    x = hdc1080.readTemperature();
    bt1 = 0.9 * bt1 + 0.1 * x;
    ct1 = 0.9 * ct1 + 0.1 * bt1;
    i++;
  }
  totTemp0 += tmpChan0;
  return ct1;
}

double getTempChan1() {
  selChan1();
  selChan1();
  double x, i = 0;
  while (i < 11)
  {
    x = hdc1080.readTemperature();
    bt2 = 0.9 * bt2 + 0.1 * x;
    ct2 = 0.9 * ct2 + 0.1 * bt2;
    i++;
  }
  totTemp1 += tmpChan1;
  return ct2;
}
double getHumidChan0() {
  selChan0();
  selChan0();
  double x, i = 0;
  while (i < 7) {
    x = hdc1080.readHumidity();
    bh1 = 0.9 * bh1 + 0.1 * x;
    ch1 = 0.9 * ch1 + 0.1 * bh1;
    i++;
  }
  totHum0 += hmdChan0;
  return ch1;
}
double getHumidChan1() {
  selChan1();
  selChan1();
  double x, i = 0;
  while (i < 7) {
    x = hdc1080.readHumidity();
    bh2 = 0.9 * bh2 + 0.1 * x;
    ch2 = 0.9 * ch2 + 0.1 * bh2;
    i++;
  }
  totHum1 += hmdChan1;
  return ch2;
}
double getVazao(){
  if (vazao>=1.8745)return -0.435467672218868*(pow(vazao, 5))+10.206210718879237*(pow(vazao, 4))-65.2745254859448*(pow(vazao, 3))+206.60381440186202*(pow(vazao, 2))-280.6873778911369*(pow(vazao, 1));
  else return 0;
}
void turnSensorOn() {
  digitalWrite(43, HIGH);
  digitalWrite(33, HIGH);
}
void turnSensorOff() {
  digitalWrite(43, LOW);
  digitalWrite(33, LOW);
}
