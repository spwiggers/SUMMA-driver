#include "Summa_I2C.h"


unsigned int swSumma_I2C_message = 0;
unsigned int c[2] = {0};
unsigned int d[4] = {0};

void Summa_I2C_change_message(unsigned int _message){
     swSumma_I2C_message = _message;
}
unsigned int Summa_I2C_read_message(){
     return swSumma_I2C_message;
}

void I2CWRITE2BYTES (int Address, int Command, unsigned int Data) {
/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                int Command - Defined I2C Commands i.e. INTENSITY_RED, INTENSITY_GREEN, INTENSITY_BLUE
                unsigned int Data - 16bit data to be written to slave
Parameters (OUT): None
Return Value: None
Description: This function will write 2 bytes of word to the I2C bus line
*/
    unsigned int upperByte, lowerByte; // Separate 4 byte data into 2 byte values
    lowerByte = Data;
    upperByte = Data >> 8;

    unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF); // Putting address into correct format
    unsigned int upperSLAD = Address >> 8;
    upperSLAD |= 0x79; // First 5 bits 11110 and last bit '1' for a write

    Wire.beginTransmission(byte(upperSLAD)); // Start I2C transmission
    Wire.write(byte(lowerSLAD)); // address lower 8 bits of i2c address
    Wire.write(byte(Command)); // write command
    Wire.write(byte(upperByte)); // write data
    Wire.write(byte(lowerByte));
    Wire.endTransmission(true);
}

void I2CWRITE6BYTES (unsigned int Address, unsigned int Command, unsigned int DataOne, unsigned int DataTwo, unsigned int DataThree) {// DataOne: Red, DataTwo: Green, DataThree: Blue
/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                int Command - Defined I2C Commands i.e. INTENSITY_RGB, CURRENT_RGB
                unsigned int DataOne, unsigned int DataTwo, unsigned int DataThree - Three 16bit data to be written to slave
Parameters (OUT): None
Return Value: None
Description: This function will write 6 bytes of word to the I2C bus line
*/
    unsigned int upperByte, lowerByte; // Split each Data parameter into upper and lower 8 bytes because I2C format sends 8 bytes of data each time
    lowerByte = DataOne;
    upperByte = DataOne >> 8;

    unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF);
    unsigned int upperSLAD = Address >> 8;
    upperSLAD |= 0x79; // First 5 bits 11110 and last bit '1' for a write

    Wire.beginTransmission(byte(upperSLAD)); // Red
    Wire.write(byte(lowerSLAD));
    Wire.write(byte(Command));
    Wire.write(byte(upperByte));
    Wire.write(byte(lowerByte));
    lowerByte = DataTwo;
    upperByte = DataTwo >> 8;
    Wire.write(byte(upperByte));
    Wire.write(byte(lowerByte));
    lowerByte = DataThree;
    upperByte = DataThree >> 8;
    Wire.write(byte(upperByte));
    Wire.write(byte(lowerByte));
    Wire.endTransmission(true);
}

void I2CWRITE12BYTES (unsigned int Address, unsigned int Command, unsigned int DataOne, unsigned int DataTwo, unsigned int DataThree, unsigned int DataFour, unsigned int DataFive, unsigned int DataSix) {// DataOne: Red, DataTwo: Green, DataThree: Blue
/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                int Command - Defined I2C Commands i.e. DMX16Bit
                unsigned int DataOne, unsigned int DataTwo, unsigned int DataThree, usigned int DataFour, unsigned int DataFive - Three 16bit data to be written to slave
Parameters (OUT): None
Return Value: None
Description: This function will write 12 bytes of word to the I2C bus line
*/  
    unsigned int upperByte, lowerByte;
    lowerByte = DataOne;
    upperByte = DataOne >> 8;

    unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF);
    unsigned int upperSLAD = Address >> 8;
    upperSLAD |= 0x79; // First 5 bits 11110 and last bit '1' for a write

    Wire.beginTransmission(byte(upperSLAD)); 
    Wire.write(byte(lowerSLAD));
    Wire.write(byte(Command)); // write command
    Wire.write(byte(upperByte)); // write 2 bytes
    Wire.write(byte(lowerByte));

    lowerByte = DataTwo;
    upperByte = DataTwo >> 8;
    Wire.write(byte(upperByte)); // write next two bytes
    Wire.write(byte(lowerByte));

    lowerByte = DataThree;
    upperByte = DataThree >> 8;
    Wire.write(byte(upperByte));
    Wire.write(byte(lowerByte));

    lowerByte = DataFour;
    upperByte = DataFour >> 8;
    Wire.write(byte(upperByte));
    Wire.write(byte(lowerByte));

    lowerByte = DataFive;
    upperByte = DataFive >> 8;
    Wire.write(byte(upperByte));
    Wire.write(byte(lowerByte));

    lowerByte = DataSix;
    upperByte = DataSix >> 8;
    Wire.write(byte(upperByte));
    Wire.write(byte(lowerByte));
    Wire.endTransmission(true);
}

unsigned int I2CREAD (unsigned int Address, unsigned int Command) {// Returns data sent by slave 
/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                int Command - Defined read I2C Commands i.e. READ_INTENSITY_RED, READ_INTENSITY_GREEN, READ_INTENSITY_BLUE
Parameters (OUT): None
Return Value: Requested data from Shield will be sent back
Description: This function will request 2 bytes of word from the shield
*/
    int i = 0;
    unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF);
    unsigned int upperSLAD = Address >> 8;
    upperSLAD |= 0x79;

    Wire.beginTransmission(byte(upperSLAD)); // Red
    Wire.write(byte(lowerSLAD));
    Wire.write(byte(Command));
    Wire.endTransmission(false); // false for Repeated Start

    Wire.beginTransmission(byte(upperSLAD)); 
    Wire.write(byte(lowerSLAD));
    Wire.requestFrom((uint8_t)upperSLAD, (uint8_t)2, (uint8_t)true); 
    unsigned int data = 0;

    while(Wire.available())    // slave may send less than requested. Print out received data byte
    { 
        Summa_I2C_change_message(1);
        c[i] = Wire.read(); // receive a byte as character
        i++;
        
    }
    Wire.endTransmission(true);

    data = c[1]; // write data to serial monitor. c[1] is higher byte
    data = (data << 8) | c[0];  // shift left and combine with lower byte
    /*
    Serial.print("0x");
    if (data < 0x1000)
        Serial.print("0");
    Serial.println(data, HEX); 
    */
    return data; 
}

unsigned long I2CREAD_DIRECTACCESS (unsigned int Address, unsigned int Command, unsigned long registerAddress){
/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                int Command - DIRECTACCESS_READ
Parameters (OUT): None
Return Value: Requested data from the Shield will be returned
Description: This function will request 4 bytes of data from shield.
*/
    int i = 0;
    unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF); // sending command + address
    unsigned int upperSLAD = Address >> 8;
    upperSLAD |= 0x79; // First 5 bits 11110 and last bit '1' for a write

    Wire.beginTransmission(byte(upperSLAD)); 
    Wire.write(byte(lowerSLAD));
    Wire.write(byte(Command));

    unsigned int firstByte, secondByte, thirdByte, fourthByte;
    firstByte = registerAddress >> 24; // top byte
    secondByte = registerAddress >> 16;
    thirdByte = registerAddress >> 8;
    fourthByte = registerAddress; // bottom byte

    Wire.write(byte(firstByte));
    Wire.write(byte(secondByte));
    Wire.write(byte(thirdByte));
    Wire.write(byte(fourthByte));

    Wire.endTransmission(false); // false for Repeated Start

    Wire.beginTransmission(byte(upperSLAD)); // request for read
    Wire.write(byte(lowerSLAD));
    Wire.requestFrom((uint8_t)upperSLAD, (uint8_t)4, (uint8_t)true); 
    unsigned long data = 0;

    while(Wire.available())    // slave may send less than requested. Print out received data byte
    { 
        d[i] = 0;
        d[i] = Wire.read(); // receive a byte as character
        i++;   
    }

    Wire.endTransmission(true);

    data = d[3]; // combining into one variable. Highest byte received first
    data = (data << 8) | d[2];
    data = (data << 8) | d[1];
    data = (data << 8) | d[0];
    /* SWI20200107
    Serial.print("0x");
    if (data < 0x10000000)
        Serial.print("0");
    Serial.println(data, HEX); 
    */
    return data;
}

void I2CWRITE_DIRECTACCESS (unsigned int Address, unsigned int Command, unsigned long registerAddress, unsigned long Data) {// For accessing registers directly{
/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                int Command - Defined I2C Commands i.e. DIRECTACCESS_OR, DIRECTACCESS_AND, DIRECTACCESS_MOVE
                unsigned long registerAddress - address of target register
                unsigned long Data - 32 bits data to be written to register
Parameters (OUT): None
Return Value: None
Description: This function will write 4 bytes of data to specified register
*/
    unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF); // sending command + address
    unsigned int upperSLAD = Address >> 8;
    upperSLAD |= 0x79; // First 5 bits 11110 and last bit '1' for a write

    Wire.beginTransmission(byte(upperSLAD)); 
    Wire.write(byte(lowerSLAD));
    Wire.write(byte(Command));

    unsigned int firstByte, secondByte, thirdByte, fourthByte; // Send address of register first
    firstByte = registerAddress >> 24; // top byte
    secondByte = registerAddress >> 16;
    thirdByte = registerAddress >> 8;
    fourthByte = registerAddress; // bottom byte

    Wire.write(byte(firstByte));
    Wire.write(byte(secondByte));
    Wire.write(byte(thirdByte));
    Wire.write(byte(fourthByte));

    firstByte = Data >> 24; // top byte
    secondByte = Data >> 16;
    thirdByte = Data >> 8;
    fourthByte = Data; // bottom byte

    Wire.write(byte(firstByte)); // send 4 bytes of data
    Wire.write(byte(secondByte));
    Wire.write(byte(thirdByte));
    Wire.write(byte(fourthByte));
    Wire.endTransmission(true);
}

void CHANGEADDRESS (unsigned int Address, unsigned int newAddress) {  
/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                unsigned int newAddress - Address the shield should change to 
Parameters (OUT): None
Return Value: None
Description: This function will change the I2C address of the slave
*/
    unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF);
    unsigned int upperSLAD = Address >> 8;
    upperSLAD |= 0x79; // First 5 bits 11110 and last bit '1' for a write
        
    Wire.beginTransmission(byte(upperSLAD)); // Red
    Wire.write(byte(lowerSLAD));
    Wire.write(byte(0x70)); // Command to change address
    lowerSLAD = (unsigned int) (newAddress & 0x00FF);
    upperSLAD = newAddress >> 7; // Split address into 2 bytes
    upperSLAD |= 0xF0; // 10 bit addressing: First 5 bits have to be 11110.  
    upperSLAD &= 0xFE;
    Wire.write(byte(upperSLAD));
    Wire.write(byte(lowerSLAD));
    Wire.endTransmission(true);
}

void I2CDMX (unsigned int Address, unsigned int Command) {// Switch off / on the DMX { 
/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                unsigned int Command - DMXON, DMXOFF
Parameters (OUT): None
Return Value: None
Description: This function will enable or disable DMX512 control on shield
*/
    unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF); // Putting address into correct format
    unsigned int upperSLAD = Address >> 8;
    upperSLAD |= 0x79;

    Wire.beginTransmission(byte(upperSLAD)); // Start I2C transmission
    Wire.write(byte(lowerSLAD));
    Wire.write(byte(Command)); 
    Wire.endTransmission(true);
}

void I2CSAVEPARAM (unsigned int Address) {
/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
Parameters (OUT): None
Return Value: None
Description: This function will request the shield to save configurations to flash memory
*/
    int i = 0;
    unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF);
    unsigned int upperSLAD = Address >> 8;
    upperSLAD |= 0x79; 

    Wire.beginTransmission(byte(upperSLAD)); 
    Wire.write(byte(lowerSLAD));
    Wire.write(byte(SAVEPARAMETERS)); // write SAVEPARAMETERS command
    Wire.endTransmission(false); // false for Repeated Start

    Wire.beginTransmission(byte(upperSLAD)); 
    Wire.write(byte(lowerSLAD)); // write to address lower 8 bits of slave address
    Wire.requestFrom((uint8_t)upperSLAD, (uint8_t)2, (uint8_t)true);  // send READ request with upper slave address
    unsigned int data = 0;

    while(Wire.available())    // slave may send less than requested. Print out received data byte
    { 
        Summa_I2C_change_message(1);
        c[i] = Wire.read(); // receive a byte as character
        i++;
    }
    Wire.endTransmission(true); // STOP condition

    data = c[1]; // print the data on serial monitor
    data = (data << 8) | c[0];
    /* SWI20200107
    Serial.print("0x");
    if (data < 0x1000)
        Serial.print("0");
    Serial.println(data, HEX); 
    */
}