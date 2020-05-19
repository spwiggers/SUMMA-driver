#ifndef _SUMMA_HELPER_h
#define _SUMMA_HELPER_h

#include <Arduino.h>

///////// Default IOPins Settings
#define STATUSPIN 19
#define RESET_PIN 23

bool SummaDebug();
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