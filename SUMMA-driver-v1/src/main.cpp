#include <Arduino.h>
#include "../lib/Summa_Wifi/src/Summa_Wifi.h"
#include "../lib/Summa_OTA/src/Summa_OTA.h"
#include "../lib/Summa_MQTT/src/Summa_MQTT.h"
#include "../lib/Summa_Infinion/src/Summa_Infinion.h"
#include "../lib/Summa_Helper/src/Summa_Helper.h"
#include "../lib/Summa_Time/src/Summa_Time.h"

///////// Default Interval Settings
long previousMillis = 0;
long interval = 100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Summa_initPins();
  Summa_SetStatusLed(true);
  Summa_Wifi_Setup();
  Summa_OTA_Setup();
  Summa_MQTT_Setup();
  Summa_Infinion_Setup();
  Summa_SetStatusLed(false);
}

void loop() {
  //OTA
  Summa_HandleOTA();
  //MQTT - subscriptions
  if (!Summa_IsMQTT_connected()) { Summa_MQTT_Reconnect(); }
  Summa_HandleMQTT();

  previousMillis += 1;
  Summa_Time_Calculate();
  if (previousMillis > interval){
    Summa_MQTT_SentMessage();
    previousMillis = 0;
  }

  // put your main code here, to run repeatedly:
  //Serial.println("Hello world!");
  delay(100);
}


