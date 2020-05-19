#ifndef _SUMMA_MQTT_h
#define _SUMMA_MQTT_h

#include "../../PubSubClient/src/PubSubClient.h"
#include "../../Summa_Helper/src/Summa_Helper.h"
#include "../../Summa_Wifi/src/Summa_Wifi.h"
#include "../../Summa_Json/src/Summa_Json.h"
#include "../../Summa_Temp/src/Summa_Temp.h"
#include "../../Summa_Time/src/Summa_Time.h"

void Summa_MQTT_Setup();
void Summa_MQTT_Reconnect();
void subscribeReceiveDataFromMQTT(char* topic, byte* payload, unsigned int _length);
void Summa_MQTT_Publish(String input);
bool Summa_IsMQTT_connected();
void Summa_HandleMQTT();
void Summa_MQTT_SentMessage();

#endif