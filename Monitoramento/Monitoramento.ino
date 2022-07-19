//Importação das bibliotecas
#include <ClosedCube_HDC1080.h>
#include <DS3232RTC.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <ResponsiveAnalogRead.h>
#include <SD.h>
#include <SPI.h>
#include <Streaming.h>
#include <TimeLib.h>
#include <Wire.h>
Sd2Card card;

const int ANALOG_PIN = A6;
ResponsiveAnalogRead analog(ANALOG_PIN, true, 0.2);

#define M_E 2.7182818284590452353602874713527 //Constante de Euler
void (*funcReset)() = 0;//reset do sistema
unsigned long period = 60000;  //modifique aqui o intervalo entre medidas, utilize multiplos de 60000ms
unsigned long time_now = 0;
unsigned long sensor_Hdc = 30000; //variavel pra auxiliar o millis() obter as ifnormações do sensor de temperatura
int tempo = 1;

//Variáveis para controlar a mudança de tela no menu---------------------------------------------------------
#define botao_MAIS 27                  //define o botão no pino 27 (MAIS)
#define botao_ENTER 29                 //define o botão no pino 29 (ENTER/VOLTAR)
#define botao_MENOS 31                 //define o botão no pino 31 (MENOS)
bool L_botao_MAIS = 1;                //variável para fazer a leitura do botão              (MAIS)
bool LA_botao_MAIS = 1;               //variável para verificar a leitura anterior do botão (MAIS)
bool L_botao_ENTER = 1;               //variável para fazer a leitura do botão              (ENTER/VOLTAR)
bool LA_botao_ENTER = 1;              //variável para verificar a leitura anterior do botão (ENTER/VOLTAR)
bool L_botao_MENOS = 1;               //variável para fazer a leitura do botão              (MENOS)
bool LA_botao_MENOS = 1;              //variável para verificar a leitura anterior do botão (MENOS)
int tela = 1;

//Símbolos no display LCD----------------------------------------------
#if defined(ARDUINO) && ARDUINO >= 100 //desenhos pro lcd
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif
//Array que desenha simbolos
uint8_t branco[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t grava[] =  {0x00, 0x1F, 0x10, 0x17, 0x11, 0x1F, 0x00, 0x00};
uint8_t cubico[] = {  0x1C, 0x04, 0x0C, 0x04, 0x1C, 0x00, 0x00, 0x00};

unsigned long millisTarefa1 = millis();
//----------------------------------------------------------------------

//-----------------Gravação na EEPROM-----------------------------------
int countGrav = 0;
#define espacoEEPROM 1000   //1Kb para todos os Arduinos com ATMega328P
void EEPROMWriteInt(int address, int value); //2 Bytes
int  EEPROMReadInt(int address);
bool g; //booleano que verifica se a gravação está ocorrendo
bool v; //booleano que verifica se o sensor de vazão está ativo
//-----------------------------------------------------------------------

//Display LCD
LiquidCrystal_I2C lcd(0x3F, 16, 2);

//Cartão_SD
#define CS_PIN 4
File dataFile;

//Sensor de temperatura e umidade
ClosedCube_HDC1080 hdc1080;

//Relógio RTC DS3231--------------------------------
DS3232RTC RTC;
int   ano, h, m, s, D, M, A; //Variáveis pra o relógio RTC

//Multiplexador---------------------------------------
#define pinAddA 7
#define pinAddB 6
#define pinAddC 5

//Variáveis-----------------------------------------------------------
/*
   tmpChan0 e hmdChan0 se referem ao sensor de temperatura que ficará internamente(Chan0);
   tmpChan1 e hmdChan1 se referem ao sensor de temperatura que ficará externamente(Chan1);
*/
double tmpChan0 = 0.0, hmdChan0 = 0.0;
double tmpChan1 = 0.0, hmdChan1 = 0.0;
double vazao = 0.0;
double taxaSecagem = 0;
double totTemp0 = 0, totTemp1 = 0, totHum0 = 0, totHum1 = 0; //media das temperaturas
double totalSensores[4]; //[0] = totTemp0, [1] = totTemp1, [2] = totHum0, [3] = totHum1
double UAint = 0;//Umidade absoluta Sensor interno
double UAext = 0;//Umidade absoluta Sensor externo
double totalizador;

void setup() {


  g = EEPROM[0]; //g recebe o estado anterior que estava
  countGrav  = EEPROMReadInt(1);//Posicao 1 e 2 da EEPROM
  inicia_lcd();  //Inicializa o display LCD
  inicia_SD();//inicializa o sd_card
  Serial.begin(9600); //Inicia o monitor serial

  //---------------pin modes-----
  pinModes();
  //---------------------------
  //inicializar sensores de temperatura e umidade
  selChan0();
  selChan0();
  hdc1080.begin(0x40);

  selChan1();
  selChan1();
  hdc1080.begin(0x40);

  //Sincroniza a biblioteca Time com o RTC
  RTCSync();
  delay(300);
}

void loop() {
  EEPROM[0] = g; //EEPROM fica recebendo o valor de g
  analog.update();
  selChan0();
  tmpChan0 = getTempChan0();
  hmdChan0 = getHumidChan0();
  vazao = analog.getValue();
  selChan1();
  tmpChan1 = getTempChan1();
  hmdChan1 = getHumidChan1();
  UAext = UA(tmpChan1, hmdChan1);
  taxaSecagem = TS(vazao, UAint, UAext);

  Serial.print(tmpChan0);
  Serial.print("\t");
  Serial.println(tmpChan1);
  //  Serial.println(tmpChan0);
  // =========== Ações no display LCD ============================= //
  if (tela == 1)
    Tela1();//Tela1() é chamada
  else if (tela == 2)
    Tela2();
  else if (tela == 3)
    Tela3();
  else if (tela == 4)
    Tela4();
  else if (tela == 20)
    Tela20();
  else if (tela == 30)
    Tela30();
  else if (tela == 31)
    Tela31();
  else if (tela == 32)
    Tela32();
  else if (tela == 321)
    Tela321();
  else if (tela == 40)
    Tela40();
  AcaoBotoes();
  //verificações que ocorrem durante o programa----------------------------------
  if (digitalRead(botao_MENOS) == HIGH && digitalRead(botao_MAIS) == HIGH)Relogio();
  if (second() % 15 == 0) {
    if (!card.init(SPI_HALF_SPEED, CS_PIN))g = false;
    totTemp0 += tmpChan0;
    totTemp1 += tmpChan1;
    totHum0 += hmdChan0;
    totHum1 += hmdChan1;
  }
  if (g == true)GravaSD();
  if ((digitalRead(botao_ENTER) == HIGH) && (digitalRead(botao_MENOS) == HIGH))funcReset(); //reiniciar
}
