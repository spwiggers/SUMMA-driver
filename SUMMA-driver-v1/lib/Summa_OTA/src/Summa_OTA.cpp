#include "Summa_OTA.h"

void Summa_OTA_Setup(){

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  String swOTAName = Summa_OTAName()+Summa_Wifi_GetMacAddress();
  char caOTA[swOTAName.length()+1];  swOTAName.toCharArray(caOTA, swOTAName.length()+1);
  ArduinoOTA.setHostname(caOTA);

  // No authentication by default
  String swOTAPassword = Summa_OTAPassword();
  char caOTAPW[swOTAPassword.length()+1];  swOTAPassword.toCharArray(caOTAPW, swOTAPassword.length()+1);
  ArduinoOTA.setPassword(caOTAPW);

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Summa_println("Start updating " + type);
    })
    .onEnd([]() {
      Summa_println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Summa_println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Summa_println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Summa_println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Summa_println("Receive Failed");
      else if (error == OTA_END_ERROR) Summa_println("End Failed");
    });

  ArduinoOTA.begin();
  Summa_println("\nOTA Ready");
}

void Summa_HandleOTA(){
    ArduinoOTA.handle();
}