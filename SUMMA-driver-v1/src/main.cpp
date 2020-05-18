#include <Arduino.h>
#include "../lib/Summa_Wifi/src/Summa_Wifi.h"
#include "../lib/Summa_OTA/src/Summa_OTA.h"
#include "../lib/Summa_MQTT/src/Summa_MQTT.h"
//#include "../lib/Summa_Helper/src/Summa_Helper.h"



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Summa_Wifi_Setup();
  Summa_OTA_Setup();
  Summa_MQTT_Setup();


}

void loop() {
  //OTA
  Summa_HandleOTA();
  //MQTT - subscriptions
  if (!Summa_IsMQTT_connected()) { Summa_MQTT_Reconnect(); }
  Summa_HandleMQTT();



  // put your main code here, to run repeatedly:
  //Serial.println("Hello world!");





  delay(1000);
}


