#ifndef _SUMMA_VARS_h
#define _SUMMA_VARS_h

#include <Arduino.h>

class SummaVars
{    
    public:
        String SSID;
        String SSID_password;
        String MQTT_Server;

        unsigned long Infinion_Red;
        unsigned long Infinion_Green;
        unsigned long Infinion_Blue;
        unsigned long Infinion_Current;
        unsigned long Infinion_Offset;
        unsigned long Infinion_DimLevel;
};

#endif