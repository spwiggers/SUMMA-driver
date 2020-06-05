
#ifndef _SUMMA_INFINION_h
#define _SUMMA_INFINION_h

#include <Arduino.h>
#include "../../Summa_I2C/src/Summa_I2C.h"
#include "../../Summa_Helper/src/Summa_Helper.h"

void Summa_Infinion_Available(bool _isAvailable);
void Summa_Infinion_Check();
void Summa_Infinion_Setup();
void Summa_Infinion_Demo();
void Summa_Infinion_Short_Demo();
String Summa_Infinion_GetJSONData();
String Summa_Infinion_UpdateColors();

bool Summa_Infinion_IsEnabled();
unsigned long Summa_Infinion_GetBrightness();
unsigned long Summa_Infinion_GetCurrent();
void Summa_Infinion_SetCurrent(unsigned long _newCurrent);


//#define ADDRESS                    0x015EUL
#define ADDRESS                    0x025EUL

#define INTENSITY_RED              0x11U
#define INTENSITY_GREEN            0x12U
#define INTENSITY_BLUE             0x13U
#define INTENSITY_RGB              0x14U
#define CURRENT_RED                0x21U
#define CURRENT_GREEN              0x22U
#define CURRENT_BLUE               0x23U
#define CURRENT_RGB                0x24U

#define DMXOFF                     0x30U
#define DMXON                      0x31U
#define DMXSLOT                    0x32U
#define DMX8BIT                    0x33U
#define DMX16BIT                   0x34U
#define OFFTIME_RED                0x41U
#define OFFTIME_GREEN              0x42U
#define OFFTIME_BLUE               0x43U
#define WALKTIME                   0x50U
#define DIMMINGLEVEL               0x60U
#define FADERATE                   0x61U

#define READ_INTENSITY_RED         0x81U
#define READ_INTENSITY_GREEN       0x82U
#define READ_INTENSITY_BLUE        0x83U
#define READ_CURRENT_RED           0x84U
#define READ_CURRENT_GREEN         0x85U
#define READ_CURRENT_BLUE          0x86U
#define READ_OFFTIME_RED           0x87U
#define READ_OFFTIME_GREEN         0x88U
#define READ_OFFTIME_BLUE          0x89U
#define READ_WALKTIME              0x8AU
#define READ_FADERATE              0x8CU
#define READ_DIMMINGLEVEL          0x8BU


#endif