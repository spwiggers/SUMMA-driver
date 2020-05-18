#include <Arduino.h>

bool SWDEBUG = true;
//#define SWDEBUGMQTT               true
//#define RGB_BOARD_ENABLED         true
//#define RGB_BOARD_DEMO            false

bool SummaDebug(){
    return SWDEBUG;
}

String Summa_OTAPassword(){
    String OTAPassword = "esp8266";     return OTAPassword; }

String Summa_OTAName(){
    String OTAName = "SUMMA-";          return OTAName; }

String Summa_MQTT_PW_add(){
    String PasswordAdd = "-Uti-SW26";   return PasswordAdd; }

String Summa_MQTT_Server(){
    String MQTTServer = "hairdresser.cloudmqtt.com";   return MQTTServer; }

void Summa_println(String _input) {
    if (SummaDebug()) {
        Serial.println(_input);
    }
}

void Summa_print(String _input) {
    if (SummaDebug()) {
        Serial.print(_input);
    }
}





