
void Summa_MQTT_Setup();
void Summa_MQTT_Reconnect();
void subscribeReceiveDataFromMQTT(char* topic, byte* payload, unsigned int _length);
void Summa_MQTT_Publish(String input);
bool Summa_IsMQTT_connected();
void Summa_HandleMQTT();
