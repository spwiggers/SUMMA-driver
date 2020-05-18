#include <Arduino.h>
#include "../lib/Summa_Wifi/src/Summa_Wifi.h"
#include "../lib/Summa_OTA/src/Summa_OTA.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Summa_Wifi_Setup();
  Summa_OTA_Setup();
}

void loop() {
  Summa_HandleOTA();
  // put your main code here, to run repeatedly:
  Serial.println("Hello world!");
  delay(1000);
}


