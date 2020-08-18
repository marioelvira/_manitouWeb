
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#include "e2prom.h"
#include "http.h"
#include "io.h"
#include "ip.h"
#include "main.h"
#include "manitou.h"
#include "wifi.h"

///////////////////
// IO definition //
///////////////////
int inMotor;
int outReleCorte;
int outLed;
int outAlarma;
int inAgua;
int inAceite;

///////////
// Wi-Fi //
///////////
//unsigned long wifiAPTick = 0;
unsigned long wifiLEDTick = 0;

/*
#if (_WRITE_SSID_EEPROM_ == 1)
const char* ssidSt = SSIDST;
const char* passwordSt = PSKST;
#endif
*/

// Station Mode
//char ssid[WIFI_SSID_MAX];
//char password[WIFI_PSWD_MAX];

IPAddress wifiIP;

// Accesspoint Mode
const char* ssidAp = SSIDAP;
const char* passwordAp = PSKAP;

int wifiStatus;
//int wifiMode;

////////////////
// IP Address //
////////////////
/*
int       ipMode;

IPAddress ipAddress (192, 168, 43, 200);
IPAddress gateWay   (192, 168, 43, 1);
IPAddress netMask   (255, 255, 255, 0);

byte mac[6];
*/

/////////////////
// Device Name //
/////////////////
#define DEVICENAME      "mani8266"
char* deviceName = DEVICENAME;

/////////////////
// Http server //
/////////////////
ESP8266WebServer httpServer(HTTP_PORT);

int httpStatus;

/////////////////////
// Manitou Control //
/////////////////////
int manitouNumberOfOns = 0;
int manitouNumberOfOns2Save = 1;
int manitouNumberOfHours = 0;
int manitouNumberOfHours2Save = 1;
int manitouNumberOfHours2Increment = 1;

//////////
// Time //
//////////
unsigned long timeTick = 0;
int timeSec = 0;
int timeMin = 0;
int timeHour = 0;

//============//
// MAIN SETUP //
//============//
void setup(void)
{ 
  // IO setup
  _IOSetup();

  #if (_SERIAL_DEBUG_ == 1)
  delay(5000);  // 5 secs
  Serial.begin(115200);
  Serial.println("");
  #endif

  // Config setup
  _ConfigSetup();

  // Wi-Fi setup
  _WifiSetup();

  // Http setup
  _HttpSetup();

  // Time Setup
  _TimeSetup();

  // Manitou setup
  _ManitouSetup();
}

//////////////
// IO steup //
//////////////
void _IOSetup(void)
{ 
  pinMode(DO_LED, OUTPUT);
  digitalWrite(DO_LED, DOUT_OFF);
  outLed = IO_OFF;

  pinMode(DO_RELE_CORTE, OUTPUT);
  digitalWrite(DO_RELE_CORTE, DOUT_OFF);
  outReleCorte = IO_OFF;

  pinMode(DO_ALARMA, OUTPUT);
  digitalWrite(DO_ALARMA, DOUT_OFF);
  outAlarma = IO_OFF;

  pinMode(DI_MOTOR, INPUT);
  inMotor = IO_OFF;

  pinMode(DI_AGUA, INPUT);
  inAgua = IO_OFF;

  pinMode(DI_ACEITE, INPUT);
  inAceite = IO_OFF;
}

//////////////////////
// IO state machine //
//////////////////////
void _IOLoop()
{
  if (outLed == IO_OFF)
    digitalWrite(DO_LED, DOUT_OFF);
  else
    digitalWrite(DO_LED, DOUT_ON);

  if (outAlarma == IO_OFF)
    digitalWrite(DO_ALARMA, DOUT_OFF);
  else
    digitalWrite(DO_ALARMA, DOUT_ON);

  if (outReleCorte == IO_OFF)
    digitalWrite(DO_RELE_CORTE, DOUT_OFF);
  else
    digitalWrite(DO_RELE_CORTE, DOUT_ON);

  if (digitalRead(DI_MOTOR))
    inMotor = IO_OFF;
  else
    inMotor = IO_ON;

  if (digitalRead(DI_AGUA))
    inAgua = IO_OFF;
  else
    inAgua = IO_ON;

  if (digitalRead(DI_ACEITE))
    inAceite = IO_OFF;
  else
    inAceite = IO_ON;
  
}

//===========//
// MAIN LOOP //
//===========//
void loop()
{
  _IOLoop();

  _WifiLoop();
  _WifiLedLoop();

  if ((wifiStatus == WIFI_ON_ACCESSPOINT) /*|| (wifiStatus == WIFI_STATION_CONNECTED)*/)
  {
    _HttpLoop();
  }

  _ManitouLoop();
  _TimeLoop();
}
