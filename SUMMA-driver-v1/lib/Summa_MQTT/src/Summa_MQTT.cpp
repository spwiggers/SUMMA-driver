#include <WiFi.h>

#include "../../PubSubClient/src/PubSubClient.h"
#include "../../Summa_Helper/src/Summa_Helper.h"
#include "../../Summa_Wifi/src/Summa_Wifi.h"
#include "Summa_MQTT.h"

WiFiClient mqtt_wifi_client;
PubSubClient mqttClient(mqtt_wifi_client);

String Summa_MQTT_SubscribeTopic(){
    return "utilicht/armatuur/out/"+Summa_Wifi_GetMacAddress();
}

void Summa_MQTT_Setup() {
  Summa_println("MQTT Setup - Start");
  Summa_MQTT_Reconnect();
  Summa_println("MQTT Setup - Finish");
}

void Summa_MQTT_Reconnect() {
  // Loop until we're reconnected

    char mqttServer[Summa_MQTT_Server().length()+1];  Summa_MQTT_Server().toCharArray(mqttServer, Summa_MQTT_Server().length()+1);
    mqttClient.setServer(mqttServer, 17900);
    String sPW= Summa_Wifi_GetMacAddress() + Summa_MQTT_PW_add();
    char mqttUser[Summa_Wifi_GetMacAddress().length()+1];  Summa_Wifi_GetMacAddress().toCharArray(mqttUser, Summa_Wifi_GetMacAddress().length()+1);
    char mqttPW[sPW.length()+1];  sPW.toCharArray(mqttPW, sPW.length()+1);
    Summa_print("MQTTUser -");
    Summa_print(mqttUser);
    Summa_println("-");
    Summa_print("MQTTPass -");
    Summa_print(mqttPW);
    Summa_println("-");
    while (!mqttClient.connected()) {
    if (mqttClient.connect(mqttUser, mqttUser, mqttPW)) {  // id, username, password
      Summa_println(" MQTT reconnected");

      String MQTTSubScribe = Summa_MQTT_SubscribeTopic();
      char Topic2Receive[MQTTSubScribe.length()+1];
      MQTTSubScribe.toCharArray(Topic2Receive, MQTTSubScribe.length()+1);
      mqttClient.subscribe(Topic2Receive);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void subscribeReceiveDataFromMQTT(char* topic, byte* payload, unsigned int _length)
{
  Summa_print("MQTT Topic: ");
  Summa_print(topic);
  Summa_print("MQTT Message: ");
  char cPayload[_length];
  Summa_print(String(cPayload)); 
  for(int i = 0; i < _length; i ++)
  {      
      cPayload[i]=char(payload[i]);    
  }
  Summa_println("");
  //decodeJson(cPayload);
}

void Summa_MQTT_Publish(String input){
    char String2Send[input.length()+1];
    input.toCharArray(String2Send, input.length()+1);
    String  MQTTTopic = "utilicht/armatuur/out/"+Summa_Wifi_GetMacAddress();
    char Topic2Send[MQTTTopic.length()+1];
    MQTTTopic.toCharArray(Topic2Send, MQTTTopic.length()+1);
    Summa_print("Topic2Send  (MQTT Server): ");
    Summa_print(Topic2Send);
    Summa_print(" (");
    Summa_print(Summa_MQTT_Server());
    Summa_println(")");
    Summa_print("MQTT String2Send         : ");
    Summa_println(String2Send);

    if (!mqttClient.connected()){
        Summa_MQTT_Reconnect();
    }
    mqttClient.publish(Topic2Send , String2Send);
}

bool Summa_IsMQTT_connected(){
  return mqttClient.connected();
}

void Summa_HandleMQTT(){
  mqttClient.loop();
}