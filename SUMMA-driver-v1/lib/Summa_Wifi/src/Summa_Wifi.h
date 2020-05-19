#ifndef _SUMMA_WIFI_h
#define _SUMMA_WIFI_h


#include <WiFi.h>
#include <WiFiMulti.h>
#include "../../Summa_Helper/src/Summa_Helper.h"


void Summa_Wifi_Setup();
String Summa_Wifi_GetMacAddress();
String Summa_Wifi_GetIPAddress();

//------ Helper Funcs Wifi ------
String macToStr(const uint8_t* mac);

#endif