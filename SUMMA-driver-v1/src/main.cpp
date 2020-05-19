#include <Arduino.h>
#include "../lib/Summa_Wifi/src/Summa_Wifi.h"
#include "../lib/Summa_OTA/src/Summa_OTA.h"
#include "../lib/Summa_MQTT/src/Summa_MQTT.h"
#include "../lib/Summa_Infinion/src/Summa_Infinion.h"
//#include "../lib/Summa_Helper/src/Summa_Helper.h"

///////// Time Settings
unsigned long SWT_timeNow = 0;
unsigned long SWT_timeLast = 0;
//Time start Settings:
int SWT_startingHour = 15;
// set your starting hour here, not below at int hour. This ensures accurate daily correction of time
int SWT_seconds = 0;
int SWT_minutes = 25;
int SWT_hours = SWT_startingHour;
int SWT_days = 0;

//Accuracy settings
int SWT_dailyErrorFast = 0; // set the average number of milliseconds your microcontroller's time is fast on a daily basis
int SWT_dailyErrorBehind = 0; // set the average number of milliseconds your microcontroller's time is behind on a daily basis
int SWT_correctedToday = 1; // do not change this variable, one means that the time has already been corrected today for the error in your boards crystal. This is true for the first day because you just set the time when you uploaded the sketch.

///////// Default Interval Settings
long previousMillis = 0;
long interval = 100;

String _Version = "v1.04a(350mA)";
String _Type = "FusionCOB";
double _Temp = 83.24;  

void SentMQTTMessage();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Summa_Wifi_Setup();
  Summa_OTA_Setup();
  Summa_MQTT_Setup();
  Summa_Infinion_Setup();
}

void loop() {
  //OTA
  Summa_HandleOTA();
  //MQTT - subscriptions
  if (!Summa_IsMQTT_connected()) { Summa_MQTT_Reconnect(); }
  Summa_HandleMQTT();

  previousMillis += 1;
  //calculate_time();
  if (previousMillis > interval){
    Serial.print("The time is: ");
    Serial.print(SWT_days);
    Serial.print(":");
    Serial.print(SWT_hours);
    Serial.print(":");
    Serial.print(SWT_minutes);
    Serial.print(":");
    Serial.println(SWT_seconds);
    previousMillis = 0;
    SentMQTTMessage();
  }

  // put your main code here, to run repeatedly:
  //Serial.println("Hello world!");
  delay(1000);
}

void SentMQTTMessage() {
    String messageString = "{ \"IP\": \"";
    messageString+= Summa_Wifi_GetIPAddress();
    messageString+= "\", \"ticks\": ";
    messageString+= String(millis());
    messageString+= ", \"version\": \"";
    messageString+= _Version;
    messageString+= "\", \"type\": \"";
    messageString+= _Type;
    messageString+= "\", \"temp\": ";
    messageString+= _Temp;
//    messageString+= ", ";
//    messageString+= ", \"time\": [";
//    messageString+= SWT_hours;
//    messageString+= ", ";
//    messageString+= SWT_minutes;
//    messageString+= ", ";
//    messageString+= SWT_seconds;
//    messageString+= getUtiTime();
    messageString+= "], ";
    messageString+= Summa_Infinion_UpdateColors();
    messageString+= " } ";
    Summa_MQTT_Publish(messageString); 
}
