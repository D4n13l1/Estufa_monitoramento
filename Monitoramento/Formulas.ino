double UA(float Temp, float UR) //UMIDADE ABSOLUTA
{
  return (UR * 1330 * pow(M_E, ((17.62 * Temp) / (Temp + 243.12)))) / (Temp + 273.16);
}

double TS(float vazao, float UAint, float UAext) //Taxa de secagem
{
  return (UAint - UAext) * vazao;
}
double getTempChan0() {
  selChan0();
  selChan0();
  double b, c, x = hdc1080.readTemperature() , i = 0;
  while (i < 10)
  {
    b = 0.95 * b + 0.05 * x;
    c = 0.95 * c + 0.05 * b;
    x = hdc1080.readTemperature();
    i++;
  }
  return c;
}

double getTempChan1() {
  selChan1();
  selChan1();
  double b, c, x = hdc1080.readTemperature(), i = 0;
  while (i < 10)
  {
    b = 0.99 * b + 0.01 * x;
    c = 0.97 * c + 0.03 * b;
    x = hdc1080.readTemperature();
    i++;
  }
  return c;
}
double getHumidChan0() {
  selChan0();
  selChan0();
  double b, c, x, i = 0;
  while (i < 5) {
    x = hdc1080.readHumidity();
    b = 0.99 * b + 0.01 * x;
    c = 0.97 * c + 0.03 * b;
    i++;
  }
  return c;
}
double getHumidChan1() {
  selChan1();
  selChan1();
  double b, c, x, i = 0;
  while (i < 5) {
    x = hdc1080.readHumidity();
    b = 0.95 * b + 0.05 * x;
    c = 0.95 * c + 0.05 * b;
    i++;
  }
  return c;
}
void turnSensorOn(){
  digitalWrite(43, HIGH);
  digitalWrite(33, HIGH);
}
void turnSensorOff(){
  digitalWrite(43, LOW);
  digitalWrite(33, LOW);
}
