#ifndef _SUMMA_HELPER_h
#define _SUMMA_HELPER_h

#include <Arduino.h>
#include <EEPROM.h>
#include "../../Summa_vars/src/Summa_vars.h"

///////// Default IOPins Settings
#define STATUSPIN 19
#define RESET_PIN 23

#define _SWVERSION      "v1.04a(350mA)"
#define _SWTYPE         "FusionCOB"
#define _SWDEBUG        true
#define _SWOTAPASSWORD  "esp8266"
#define _SWOTANAME      "SUMMA-"
#define _SWMQTTPASSADD  "-UtiSW26"
#define _SWMQTTSERVER   "hairdresser.cloudmqtt.com"




bool SummaDebug();
String SummaVersion();
String SummaType();
String Summa_OTAPassword();
String Summa_OTAName();
String Summa_MQTT_PW_add();
String Summa_MQTT_Server();
void Summa_println(String _input);
void Summa_print(String _input);
void Summa_initPins();
void ResetToFactoryDefaults();
void Summa_SetStatusLed(bool _input);

template <class T> int EEPROM_writeAnything(int ee, const T& value);
template <class T> int EEPROM_readAnything(int ee, T& value);

void Summa_SaveEEProm();
void Summa_ReadEEProm();

void Summa_Helper_SetRed(unsigned long _red);
void Summa_Helper_SetGreen(unsigned long _green);
void Summa_Helper_SetBlue(unsigned long _blue);
void Summa_Helper_SetCurrent(unsigned long _current);
void Summa_Helper_SetDimlevel(unsigned long _dimlevel);
unsigned long Summa_Helper_GetRed();
unsigned long Summa_Helper_GetGreen();
unsigned long Summa_Helper_GetBlue();
unsigned long Summa_Helper_GetCurrent();
unsigned long Summa_Helper_GetDimlevel();

#endif