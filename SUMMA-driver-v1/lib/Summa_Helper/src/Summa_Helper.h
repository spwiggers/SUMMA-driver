#ifndef _SUMMA_HELPER_h
#define _SUMMA_HELPER_h

#include <Arduino.h>

///////// Default IOPins Settings
#define STATUSPIN 19
#define RESET_PIN 23

#define _SWVERSION      "v1.04a(350mA)"
#define _SWTYPE         "FusionCOB"
#define _SWDEBUG        true
#define _SWOTAPASSWORD  "esp8266"
#define _SWOTANAME      "SUMMA-"
#define _SWMQTTPASSADD  "-Uti-SW26"
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

#endif