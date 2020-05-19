#include "Summa_Json.h"

void decodeJson(char * payload){
  StaticJsonDocument <300> doc;
  DeserializationError error = deserializeJson(doc, payload);
  if (error){
    Serial.printf("function deserializeJson() failed : %S\n", error.c_str());
  }

  bool _containsRed = false;
  bool _containsGreen = false;
  bool _containsBlue = false;
  bool _containsDimlevel = false;
  bool _containsHours = false;
  bool _containsMinutes = false;
  bool _containsSeconds = false;
  bool _containsCurrent = false;
  
  String _ActionString = doc["action"];
  char _Action = _ActionString.charAt(0);
  unsigned int _Red = 0;
  unsigned int _Green = 0;
  unsigned int _Blue = 0;
  int _Hours = 0;
  int _Minutes = 0;
  int _Seconds = 0;
  unsigned int _Current = 0;
  unsigned long _Dimlevel = Summa_Infinion_GetBrightness();
  String _JSON_SSID = doc["ssid"];
  String _JSON_SSIDPW = doc["ssidPW"];
  String _JSON_mqttServer = doc["mqttServer"];

  if (doc.containsKey("dimlevel")) {
    _Dimlevel = doc["dimlevel"];
    _containsDimlevel = true;
    if (_Dimlevel > 4095) { _Dimlevel = 4095;}
    Serial.println("Dimlevel adjusted.");
  }
  if (doc.containsKey("SetCurrent")) {
    _Current = doc["SetCurrent"];
    _containsCurrent = true;
    if (_Current > 0x80) { _Current = 0x80;}
    Summa_Infinion_SetCurrent(_Current);
    Serial.println("Current adjusted.");
  }

  int arraySize =  doc["channels"].size();
  for (int i = 0; i< arraySize; i++){
    int sensorValue=doc["channels"][i];
    if (sensorValue < 0) { sensorValue = 0;}
    if (sensorValue > 4095) { sensorValue = 4095;}
    switch (i){
      case 0:
        _Red = sensorValue; _containsRed = true; break;
      case 1:
        _Green = sensorValue; _containsGreen = true; break;
      case 2:
        _Blue = sensorValue; _containsBlue = true; break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
    }
    Serial.print("Arrayvalue    : ");Serial.println(sensorValue);
  }
  arraySize =  doc["time"].size();
  for (int i = 0; i< arraySize; i++){
    int sensorValue=doc["time"][i];
    if (sensorValue < 0) { sensorValue = 0;}
    if (sensorValue > 60) { sensorValue = 60;}
    switch (i){
      case 0:
        _Hours = sensorValue; _containsHours = true; break;
      case 1:
        _Minutes = sensorValue; _containsMinutes = true; break;
      case 2:
        _Seconds = sensorValue; _containsSeconds = true; break;
    }
    Serial.print("Arrayvalue    : ");Serial.println(sensorValue);
  }
  
  Serial.print("Action    : ");Serial.println(_Action);
  Serial.print("Red       : ");Serial.println(_Red);
  Serial.print("Green     : ");Serial.println(_Green);
  Serial.print("Blue      : ");Serial.println(_Blue);
  Serial.print("SSID      : ");Serial.println(_JSON_SSID);
  Serial.print("SSIDPW    : ");Serial.println(_JSON_SSIDPW);
  Serial.print("mqttServer: ");Serial.println(_JSON_mqttServer);
  Serial.print("Dimlevel  : ");Serial.println(_Dimlevel);
  
  //Serial.printf("deserializeJson Values Action: %s, Red: %d, Green %d, Blue %d\n", _Action, _Red, _Green, _Blue);
  //delay(1000);
  switch (_Action) {
    case 'c':             // if the websocket is disconnected
      if (Summa_Infinion_IsEnabled()) {
        //INIT_RGB_BOARD();
        if (_containsRed && _containsGreen && _containsBlue) {
          I2CWRITE2BYTES (ADDRESS, INTENSITY_RED, _Red); // change red colour intensity to 0x000
          I2CWRITE2BYTES (ADDRESS, INTENSITY_GREEN, _Green); // change green colour intensity to 0x000
          I2CWRITE2BYTES (ADDRESS, INTENSITY_BLUE, _Blue); // change blue colour intensity to 0x000 
        }
        if (_containsDimlevel) {
          I2CWRITE2BYTES (ADDRESS, DIMMINGLEVEL, _Dimlevel);
        }
        delay(100);
        //Summa_MQTT_SentMessage();
      }
      break;  
    case 'b':
      ESP.restart();
      break;
    case 't':
      if (_containsHours && _containsMinutes && _containsSeconds) {
//        SWT_hours = _Hours;
//        SWT_minutes = _Minutes;
//        SWT_seconds = _Seconds;
      }
      break;      
    case 'r':
      //ESP.restart();
      break;
    case 'x':
      if (Summa_Infinion_IsEnabled()) {
        if (_containsCurrent){
          Summa_Infinion_Setup();
        }     
      }
      break;
  }
}
