#include <WiFi.h>
#include <WiFiMulti.h>
#include "../../Summa_Helper/src/Summa_Helper.h"

WiFiMulti swWifiMulti;

String summaSSID = "Utilicht-SW";
String summaSSID_PW = "Wifi@UTL!15";

String macToStr(const uint8_t* mac);

void Summa_Wifi_Setup(){
  char caSSID[summaSSID.length()+1];  summaSSID.toCharArray(caSSID, summaSSID.length()+1);
  char caSSID_PW[summaSSID_PW.length()+1];  summaSSID_PW.toCharArray(caSSID_PW, summaSSID_PW.length()+1);
  swWifiMulti.addAP(caSSID, caSSID_PW);
  
  Summa_println("Connecting Wifi...");
  if(swWifiMulti.run() == WL_CONNECTED) {
    Summa_println("");
    Summa_println("WiFi connected");
    Summa_print("IP address: ");
    Summa_println( WiFi.localIP().toString());
  }
}

String Summa_Wifi_GetMacAddress(){
  String clientMac = "";
  unsigned char mac[6];
  WiFi.macAddress(mac);
  clientMac += macToStr(mac);
  Summa_println("");
  Summa_print("WiFi MAC address : ");
  Summa_println(clientMac);
  return clientMac;
}





//------ Helper Funcs Wifi ------
String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    String tmpStr = String(mac[i], 16);
    if (tmpStr.length() == 1) { tmpStr = "0" + tmpStr; }
    result += tmpStr;
    if (i < 5)
      result += ""; // was ':'
    }
  return result;
}