#include "Summa_Infinion.h"

bool RGB_BOARD_ENABLED = true;

unsigned int swSumma_Infinion_on = 0;

unsigned long setOffset = 0x00;   // default 0x38     // 0x01         0x00          0x00          0x00
unsigned long setCurrent = 0x39;  // default 0x15     // 0x23 = 190mA 0x33 = 290mA  0x38 = 320mA  0x42 = 380mA 0x40 = 370mA 0x80 = 780mA 0x56 = 500mA
unsigned long redcurr = 0;
unsigned long greencurr = 0;
unsigned long bluecurr = 0;
unsigned long redoff = 0;
unsigned long greenoff = 0;
unsigned long blueoff = 0;
unsigned long redint = 0x00;
unsigned long greenint = 0x00;
unsigned long blueint = 0x00;
unsigned long fadetime = 0x00;
unsigned long walk = 0x00;
unsigned long brightness = 1;

void Summa_Infinion_Setup(){
    Serial.println("Init RGB Board");
    Wire.begin();
    while (swSumma_Infinion_on != 1) // Wait for shield to respond
    {
        I2CDMX (ADDRESS, DMXOFF); // disable DMX
        I2CWRITE2BYTES (ADDRESS, FADERATE, 0x0000); // Immediate fade
        I2CWRITE2BYTES (ADDRESS, DIMMINGLEVEL, 0x0000); // 0% brightness level
        swSumma_Infinion_on = I2CREAD(ADDRESS, READ_DIMMINGLEVEL); // Request for brightness level
        delay(500);
        Serial.print("Init : Reading DIMMING LEVEL : ");
        Serial.print(swSumma_Infinion_on);
        Serial.print("/");
        Serial.println(Summa_I2C_read_message());
        if (Summa_I2C_read_message() == 1 && swSumma_Infinion_on == 0) // If message received and brightness level = 9%
        {
        Summa_I2C_change_message(0);
        swSumma_Infinion_on = 1; // break out of loop
        }
    }
    while (redcurr != setCurrent || greencurr != setCurrent || bluecurr != setCurrent || redoff != setOffset || greenoff != setOffset || blueoff != setOffset || brightness != 0)
    {
        delay(500);
        Serial.print("Init : set Current : ");
        Serial.println(swSumma_Infinion_on);
        I2CWRITE6BYTES (ADDRESS, INTENSITY_RGB, 0x0000, 0x000, 0x0000); // Off Light
        // Ensure that parameters are set up correctly. Read back and check. If wrong, write and read again.
        redcurr     = I2CREAD (ADDRESS, READ_CURRENT_RED);    // Read the red current intensity
        greencurr   = I2CREAD (ADDRESS, READ_CURRENT_GREEN);  // Read the green current intensity
        bluecurr    = I2CREAD (ADDRESS, READ_CURRENT_BLUE);   // Read the blue current intensity
        redoff      = I2CREAD (ADDRESS, READ_OFFTIME_RED);    // Read the off-time of the red channel
        greenoff    = I2CREAD (ADDRESS, READ_OFFTIME_GREEN);  // Read the off-time of the green channel
        blueoff     = I2CREAD (ADDRESS, READ_OFFTIME_BLUE);   // Read the off-time of the blue channel
        brightness  = I2CREAD (ADDRESS, READ_DIMMINGLEVEL);   // Read the dimming level
                
        I2CWRITE2BYTES (ADDRESS, OFFTIME_RED, setOffset);     // Set off-time of red channel to 0x38
        I2CWRITE2BYTES (ADDRESS, OFFTIME_GREEN, setOffset);   // Set off-time of green channel to 0x39
        I2CWRITE2BYTES (ADDRESS, OFFTIME_BLUE, setOffset);    // Set off-time of blue channel to 0x38
        I2CWRITE2BYTES (ADDRESS, CURRENT_RED, setCurrent);    // Set current intensity of red channel to 0x15 / 0x73 max 0x80
        I2CWRITE2BYTES (ADDRESS, CURRENT_GREEN, setCurrent);  // Set current intensity of green channel to 0x15
        I2CWRITE2BYTES (ADDRESS, CURRENT_BLUE, setCurrent);   // Set current intensity of blue channel to 0x15
        I2CWRITE2BYTES (ADDRESS, DIMMINGLEVEL, 0x0000);
        I2CWRITE2BYTES (ADDRESS, WALKTIME, 48); // set walk-time 480ms

    }

    //    I2CWRITE2BYTES (ADDRESS, INTENSITY_RED, 0x0000);
    //    I2CWRITE2BYTES (ADDRESS, INTENSITY_GREEN, 0x0000);
    //    I2CWRITE2BYTES (ADDRESS, INTENSITY_BLUE, 0x0000);

    I2CWRITE2BYTES (ADDRESS, FADERATE, 0x0000); // Fade Rate --> 0.7s
    I2CWRITE2BYTES (ADDRESS, WALKTIME, 0x0000);   
    I2CWRITE2BYTES (ADDRESS, DIMMINGLEVEL, 0x0FFF);
    I2CWRITE6BYTES (ADDRESS, INTENSITY_RGB, Summa_Helper_GetRed(), Summa_Helper_GetGreen(), Summa_Helper_GetBlue()); // White Light

    
}

void Summa_Infinion_Demo(){
    Serial.println("Default Demo");    
    delay(100);
    I2CWRITE2BYTES (ADDRESS, FADERATE, 0x0014); // Fade Rate --> 0.7s
    I2CWRITE2BYTES (ADDRESS, WALKTIME, 0x000F);
    I2CWRITE6BYTES (ADDRESS, INTENSITY_RGB, 0x0555, 0x0555, 0x0555); // White Light
    I2CWRITE2BYTES (ADDRESS, DIMMINGLEVEL, 0x0FFF); // Maximum Brightness

    delay(500); // wait 2 sec
    // change lamp colour to red
    I2CWRITE2BYTES (ADDRESS, INTENSITY_RED, 0x0FFF); // change red colour intensity to 0xFFF
    I2CWRITE2BYTES (ADDRESS, INTENSITY_GREEN, 0x0000); // change green colour intensity to 0x000
    I2CWRITE2BYTES (ADDRESS, INTENSITY_BLUE, 0x0000); // change blue colour intensity to 0x000 
    delay(200);
    I2CWRITE2BYTES (ADDRESS, INTENSITY_RED, 0x0000);
    I2CWRITE2BYTES (ADDRESS, INTENSITY_GREEN, 0x0FFF);
    delay(200);
    I2CWRITE2BYTES (ADDRESS, INTENSITY_GREEN, 0x0000);
    I2CWRITE2BYTES (ADDRESS, INTENSITY_BLUE, 0x0FFF);

    delay(200); // Read back values from slave
    Serial.print("Red Int: ");
    redint = I2CREAD (ADDRESS, READ_INTENSITY_RED); // request from shield red colour intensity
    Serial.print("Green Int: ");
    greenint = I2CREAD (ADDRESS, READ_INTENSITY_GREEN); // request from shield green colour intensity
    Serial.print("Blue Int: ");
    blueint = I2CREAD (ADDRESS, READ_INTENSITY_BLUE); // request from shield blue colour intensity
    Serial.print("Red Curr: ");    
    redcurr = I2CREAD (ADDRESS, READ_CURRENT_RED); // request from shield peak current reference of red channel
    Serial.print("Green Curr ");
    greencurr = I2CREAD (ADDRESS, READ_CURRENT_GREEN); // request from shield peak current reference of green channel
    Serial.print("Blue Curr: ");
    bluecurr = I2CREAD (ADDRESS, READ_CURRENT_BLUE); // request from shield peak current reference of blue channel
    Serial.print("Red PWM: ");
    redoff = I2CREAD (ADDRESS, READ_OFFTIME_RED); // request from shield off-time of red channel
    Serial.print("Green PWM: ");
    greenoff = I2CREAD (ADDRESS, READ_OFFTIME_GREEN); // request from shield off-time of green channel
    Serial.print("Blue PWM: ");    
    blueoff = I2CREAD (ADDRESS, READ_OFFTIME_BLUE); // request from shield off-time of blue channel
    Serial.print("Walk: ");    
    walk = I2CREAD (ADDRESS, READ_WALKTIME); // request from shield walk-time
    Serial.print("Brightness: ");    
    brightness = I2CREAD (ADDRESS, READ_DIMMINGLEVEL); // request from shield brightness level
    Serial.print("FadeTime: ");    
    fadetime = I2CREAD (ADDRESS, READ_FADERATE); // request from shield fade rate


    // Turn off Light !
    I2CWRITE2BYTES (ADDRESS, INTENSITY_RED, 0x0000);
    I2CWRITE2BYTES (ADDRESS, INTENSITY_GREEN, 0x0000);
    I2CWRITE2BYTES (ADDRESS, INTENSITY_BLUE, 0x0000);
}

void Summa_Infinion_Short_Demo(){
    // change lamp colour to red
    I2CWRITE2BYTES (ADDRESS, INTENSITY_GREEN, 0x0000);
    I2CWRITE2BYTES (ADDRESS, INTENSITY_BLUE, 0x0000);
    I2CWRITE2BYTES (ADDRESS, INTENSITY_RED, 0x0FFF); // Red
    delay(1000); // wait 1s
    // change lamp colour to green
    I2CWRITE2BYTES (ADDRESS, INTENSITY_RED, 0x0000); 
    I2CWRITE2BYTES (ADDRESS, INTENSITY_GREEN, 0x0FFF); // Green
    delay(1000); 
    // change lamp colour to blue
    I2CWRITE2BYTES (ADDRESS, INTENSITY_GREEN, 0x0000); 
    I2CWRITE2BYTES (ADDRESS, INTENSITY_BLUE, 0x0FFF); // Blue
    delay(1000); 
}

String GetInfinionData(){
    String GetInfinionDataString = "";
    GetInfinionDataString+= "\"channels\": [";
    GetInfinionDataString+= redint;
    GetInfinionDataString+= ", ";
    GetInfinionDataString+= greenint;
    GetInfinionDataString+= ", ";
    GetInfinionDataString+= blueint;
    GetInfinionDataString+= "]";
    GetInfinionDataString+= ", \"dimlevel\": ";
    GetInfinionDataString+= brightness;
    return GetInfinionDataString;
}

String Summa_Infinion_UpdateColors() {
//    sensors.requestTemperatures();
//    _Temp = sensors.getTempCByIndex(0);
//    if (_Temp < 0) { _Temp = 0; }

    if (RGB_BOARD_ENABLED) {
        redint    = I2CREAD (ADDRESS, READ_INTENSITY_RED);    // request from shield red colour intensity
        greenint  = I2CREAD (ADDRESS, READ_INTENSITY_GREEN);  // request from shield green colour intensity
        blueint   = I2CREAD (ADDRESS, READ_INTENSITY_BLUE);   // request from shield blue colour intensity
        redcurr   = I2CREAD (ADDRESS, READ_CURRENT_RED);      // Read the red current intensity
        greencurr = I2CREAD (ADDRESS, READ_CURRENT_GREEN);    // Read the green current intensity
        bluecurr  = I2CREAD (ADDRESS, READ_CURRENT_BLUE);     // Read the blue current intensity
        redoff    = I2CREAD (ADDRESS, READ_OFFTIME_RED);      // Read the off-time of the red channel
        greenoff  = I2CREAD (ADDRESS, READ_OFFTIME_GREEN);    // Read the off-time of the green channel
        blueoff   = I2CREAD (ADDRESS, READ_OFFTIME_BLUE);     // Read the off-time of the blue channel
        brightness = I2CREAD (ADDRESS, READ_DIMMINGLEVEL);    // Read Dimming Level
    }
    String messageString = "";
    messageString+= "\"channels\": [";
    messageString+= redint;
    messageString+= ", ";
    messageString+= greenint;
    messageString+= ", ";
    messageString+= blueint;
    messageString+= "]";
    messageString+= ", \"dimlevel\": ";
    messageString+= brightness;
    messageString+= ", \"Current\": ";
    messageString+= redcurr;
    messageString+= ", \"Offset\": ";
    messageString+= redoff;
    return messageString;
}

bool Summa_Infinion_IsEnabled(){
    return RGB_BOARD_ENABLED;
}
unsigned long Summa_Infinion_GetBrightness(){
    return brightness;
}
unsigned long Summa_Infinion_GetCurrent(){
    return setCurrent;
}


void Summa_Infinion_SetCurrent(unsigned long _newCurrent){
    setCurrent = _newCurrent;
}