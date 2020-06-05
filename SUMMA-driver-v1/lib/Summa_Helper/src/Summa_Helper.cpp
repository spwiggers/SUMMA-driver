#include "Summa_Helper.h"

String _SWTYPE = "FusionCOB";

SummaVars theVars;

typedef struct struct_summa_settings{
    String SSID;
    String SSID_password;
    String MQTT_Server;

    unsigned long Infinion_Red;
    unsigned long Infinion_Green;
    unsigned long Infinion_Blue;
    unsigned long Infinion_Current;
    unsigned long Infinion_Offset;
    unsigned long Infinion_DimLevel;
    
} theStruct_t __attribute__ ((packed));

theStruct_t theStruct;


bool SummaDebug(){              return _SWDEBUG; }
String SummaVersion(){          return _SWVERSION; }
String SummaType(){             return _SWTYPE; }
void SummaTypeSet(String _iType) { _SWTYPE = _iType;}

String Summa_OTAPassword(){     return _SWOTAPASSWORD; }
String Summa_OTAName(){         return _SWOTANAME; }
String Summa_MQTT_PW_add(){     return _SWMQTTPASSADD; }
String Summa_MQTT_Server(){     return _SWMQTTSERVER; }

void Summa_println(String _input) {
    if (SummaDebug()) {
        Serial.println(_input);
    }
}

void Summa_print(String _input) {
    if (SummaDebug()) {
        Serial.print(_input);
    }
}

void Summa_initPins() {
  pinMode(STATUSPIN, OUTPUT);
  digitalWrite(STATUSPIN, HIGH ); // Turn the LED off
  pinMode(RESET_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(RESET_PIN), ResetToFactoryDefaults, CHANGE);
}

void ResetToFactoryDefaults() {
  delay(250);
  ESP.restart();
}

void Summa_SetStatusLed(bool _input) {
  digitalWrite(STATUSPIN, !(_input) ); 
}

bool Summa_isI2CdeviceAtAddress(byte _address){
    Summa_print("Checking for I2C Device at address :0x");
    if (_address < 16 ) {Summa_print("0");}
    Serial.println(_address,HEX);
    bool isAvailable = false;
    delay(50);
    Wire.beginTransmission(byte(_address));
    byte error = Wire.endTransmission(true);
    if (error == 0) {
        Summa_print("I2C Device found at address :0x");
        if (_address < 16 ) {Summa_print("0");}
        Serial.println(_address,HEX);
        isAvailable = true;
    } else {
        Summa_print("I2C Device Error found at address :0x");
        if (_address < 16 ) {Summa_print("0");}
        Serial.println(_address,HEX);
        Summa_print("I2C Device Error Nr :" );
        Serial.println(error);

    }

    return isAvailable;
}

template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(ee++, *p++);
    return i;
}


template <class T> int EEPROM_readAnything(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}

void SH_storeStruct(void *data_source, size_t _size){
    EEPROM.begin(_size *2);
    for (size_t i = 0; i < _size; i++){
        char data = ((char *)data_source)[i];
        EEPROM.write(i, data);
    }
    EEPROM.commit();
} 

void SH_loadStruct(void *data_dest, size_t _size){
    EEPROM.begin(_size *2);
    for (size_t i = 0; i < _size; i++){
        char data = EEPROM.read(i);
        ((char *)data_dest)[i] = data;
    }
}



void Summa_SaveEEProm(){
    theStruct.Infinion_Blue = theVars.Infinion_Blue;
    theStruct.Infinion_Red = theVars.Infinion_Red;
    theStruct.Infinion_Green = theVars.Infinion_Green;
    theStruct.Infinion_Current = theVars.Infinion_Current;
    theStruct.Infinion_DimLevel = theStruct.Infinion_DimLevel;
    Summa_print("Write to Eprom (theVars): ");
    Summa_print(" R:" + String(theVars.Infinion_Red));
    Summa_print(" G:" + String(theVars.Infinion_Green));
    Summa_print(" B:" + String(theVars.Infinion_Blue));
    Summa_print(" Current:" + String(theVars.Infinion_Current));
    Summa_print(" Dim:" + String(theVars.Infinion_DimLevel));
    Summa_print("Write to Eprom (Struct): ");
    Summa_print(" R:" + String(theStruct.Infinion_Red));
    Summa_print(" G:" + String(theStruct.Infinion_Green));
    Summa_print(" B:" + String(theStruct.Infinion_Blue));
    Summa_print(" Current:" + String(theStruct.Infinion_Current));
    Summa_print(" Dim:" + String(theStruct.Infinion_DimLevel));
//    EEPROM_writeAnything(0, theStruct);
    SH_storeStruct(&theStruct, sizeof(theStruct_t));
}

void Summa_ReadEEProm(){
    //EEPROM_readAnything(0, theStruct);
    SH_loadStruct(&theStruct, sizeof(theStruct_t));
    theVars.Infinion_Blue = theStruct.Infinion_Blue;
    theVars.Infinion_Red = theStruct.Infinion_Red;
    theVars.Infinion_Green = theStruct.Infinion_Green;
    theVars.Infinion_Current = theStruct.Infinion_Current;
    theVars.Infinion_DimLevel = theStruct.Infinion_DimLevel;
    Summa_print("Read from Eprom : ");
    Summa_print(" R:" + String(theStruct.Infinion_Red));
    Summa_print(" G:" + String(theStruct.Infinion_Green));
    Summa_print(" B:" + String(theStruct.Infinion_Blue));
    Summa_print(" Current:" + String(theStruct.Infinion_Current));
    Summa_print(" Dim:" + String(theStruct.Infinion_DimLevel));
}

void Summa_Helper_SetRed(unsigned long _red){
    Summa_print("theVars.Inifity_Red : ");
    Summa_println(String(_red));
    theVars.Infinion_Red = _red;
}
void Summa_Helper_SetGreen(unsigned long _green){
    Summa_print("theVars.Inifity_Green : ");
    Summa_println(String(_green));
    theVars.Infinion_Green = _green;
}
void Summa_Helper_SetBlue(unsigned long _blue){
    Summa_print("theVars.Inifity_Blue : ");
    Summa_println(String(_blue));
    theVars.Infinion_Blue = _blue;
}
void Summa_Helper_SetDimlevel(unsigned long _dimlevel){
    Summa_print("theVars.Inifity_Dimlevel : ");
    Summa_println(String(_dimlevel));
    theVars.Infinion_DimLevel = _dimlevel;
}
void Summa_Helper_SetCurrent(unsigned long _current){
    Summa_print("theVars.Inifity_Current : ");
    Summa_println(String(_current));
    theVars.Infinion_Current = _current;
}
unsigned long Summa_Helper_GetRed(){
    return theVars.Infinion_Red;
}
unsigned long Summa_Helper_GetGreen(){
    return theVars.Infinion_Green;
}
unsigned long Summa_Helper_GetBlue(){
    return theVars.Infinion_Blue;
}
unsigned long Summa_Helper_GetDimlevel(){
    return theVars.Infinion_DimLevel;
}
unsigned long Summa_Helper_GetCurrent(){
    return theVars.Infinion_Current;
}

