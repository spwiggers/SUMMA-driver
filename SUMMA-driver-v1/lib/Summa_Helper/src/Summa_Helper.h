#ifndef _SUMMA_HELPER_h
#define _SUMMA_HELPER_h

#include <Arduino.h>

bool SummaDebug();
String Summa_OTAPassword();
String Summa_OTAName();
String Summa_MQTT_PW_add();
String Summa_MQTT_Server();
void Summa_println(String _input);
void Summa_print(String _input);

#endif