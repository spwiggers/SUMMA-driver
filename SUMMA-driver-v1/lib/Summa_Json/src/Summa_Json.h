#ifndef _SUMMA_JSON_h
#define _SUMMA_JSON_h

#include "../../Summa_Infinion/src/Summa_Infinion.h"
#include "../../Summa_I2C/src/Summa_I2C.h"
//#include "../../Summa_MQTT/src/Summa_MQTT.h"
#include "../../Summa_Helper/src/Summa_Helper.h"
//#include "../../Summa_vars/src/Summa_vars.h"


#include "ArduinoJson.h"

void decodeJson(char * payload);

#endif