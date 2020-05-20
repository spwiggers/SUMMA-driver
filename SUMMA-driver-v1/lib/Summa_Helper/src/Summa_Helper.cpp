#include "Summa_Helper.h"

bool SummaDebug(){              return _SWDEBUG; }
String SummaVersion(){          return _SWVERSION; }
String SummaType(){             return _SWTYPE; }
String Summa_OTAPassword(){     return _SWOTAPASSWORD; }
String Summa_OTAName(){         return _SWOTANAME; }
String Summa_MQTT_PW_add(){     return _SWMQTTPASSADD; }
String Summa_MQTT_Server(){     return _SWMQTTSERVER; }

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

void Summa_initPins() {
  pinMode(STATUSPIN, OUTPUT);
  digitalWrite(STATUSPIN, HIGH ); // Turn the LED off
  pinMode(RESET_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(RESET_PIN), ResetToFactoryDefaults, CHANGE);
}

void ResetToFactoryDefaults() {
  delay(250);
  ESP.restart();
}

void Summa_SetStatusLed(bool _input) {
  digitalWrite(STATUSPIN, !(_input) ); 
}

