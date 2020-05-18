#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;

char* summaSSID = "Utilicht-SW";
char* summaSSID_PW = "Wifi@UTL!15";

void Summa_Wifi_Setup(){
  wifiMulti.addAP(summaSSID, summaSSID_PW);
  
  Serial.println("Connecting Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
  }
}