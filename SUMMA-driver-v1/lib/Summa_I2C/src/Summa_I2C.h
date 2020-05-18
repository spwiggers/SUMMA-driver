#ifndef _SUMMA_I2C_h
#define _SUMMA_I2C_h

#include <Arduino.h>
#include <Wire.h>

#define SAVEPARAMETERS             0xA0U

void Summa_I2C_change_message(unsigned int _message);
unsigned int Summa_I2C_read_message();
void I2CWRITE2BYTES (int Address, int Command, unsigned int Data);
void I2CWRITE6BYTES (unsigned int Address, unsigned int Command, unsigned int DataOne, unsigned int DataTwo, unsigned int DataThree);
unsigned int I2CREAD (unsigned int Address, unsigned int Command);
unsigned long I2CREAD_DIRECTACCESS (unsigned int Address, unsigned int Command, unsigned long registerAddress);
void I2CWRITE_DIRECTACCESS (unsigned int Address, unsigned int Command, unsigned long registerAddress, unsigned long Data);
void CHANGEADDRESS (unsigned int Address, unsigned int newAddress);
void I2CDMX (unsigned int Address, unsigned int Command);
void I2CSAVEPARAM (unsigned int Address);

#endif