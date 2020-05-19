#include "Summa_Temp.h"

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); 

float Summa_Temp_GetC(){
    sensors.requestTemperatures();
    float _Temp = sensors.getTempCByIndex(0);
    return _Temp;
}