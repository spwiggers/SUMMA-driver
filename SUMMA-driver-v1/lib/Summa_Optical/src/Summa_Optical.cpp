#include "Summa_Optical.h"

AS726X AS726Xsensor;

void Summa_Optical_Setup(){
  Wire.begin();
  AS726Xsensor.begin();
}

void Summa_Optical_Demo(){
  //Prints all measurements
  Serial.println(AS726Xsensor.getVersion());
  if (AS726Xsensor.getVersion() == SENSORTYPE_AS7262)
  {
    //Visible readings
    Serial.print(" Reading: V[");
    Serial.print(AS726Xsensor.getCalibratedViolet(), 2);
    Serial.print("] B[");
    Serial.print(AS726Xsensor.getCalibratedBlue(), 2);
    Serial.print("] G[");
    Serial.print(AS726Xsensor.getCalibratedGreen(), 2);
    Serial.print("] Y[");
    Serial.print(AS726Xsensor.getCalibratedYellow(), 2);
    Serial.print("] O[");
    Serial.print(AS726Xsensor.getCalibratedOrange(), 2);
    Serial.print("] R[");
    Serial.print(AS726Xsensor.getCalibratedRed(), 2);
  }
  else if (AS726Xsensor.getVersion() == SENSORTYPE_AS7263)
  {
    //Near IR readings
    Serial.print(" Reading: R[");
    Serial.print(AS726Xsensor.getCalibratedR(), 2);
    Serial.print("] S[");
    Serial.print(AS726Xsensor.getCalibratedS(), 2);
    Serial.print("] T[");
    Serial.print(AS726Xsensor.getCalibratedT(), 2);
    Serial.print("] U[");
    Serial.print(AS726Xsensor.getCalibratedU(), 2);
    Serial.print("] V[");
    Serial.print(AS726Xsensor.getCalibratedV(), 2);
    Serial.print("] W[");
    Serial.print(AS726Xsensor.getCalibratedW(), 2);
  }
  else if (AS726Xsensor.getVersion() == SENSORTYPE_AS7261)
  {
    //XYZ xy CCT readings
    Serial.print(" Reading: X[");
    Serial.print(AS726Xsensor.getCalibrated_X(), 2);
    Serial.print("] Y[");
    Serial.print(AS726Xsensor.getCalibrated_Y(), 2);
    Serial.print("] Z[");
    Serial.print(AS726Xsensor.getCalibrated_Z(), 2);
    Serial.print("] x[");
    Serial.print(AS726Xsensor.getCalibrated_x(), 4);
    Serial.print("] y[");
    Serial.print(AS726Xsensor.getCalibrated_y(), 4);
    Serial.print("] LUX[");
    Serial.print(AS726Xsensor.getCalibrated_LUX(), 4);
    Serial.print("] CCT[");
    Serial.print(AS726Xsensor.getCalibrated_CCT(), 4);
    Serial.print("] duv[");
    Serial.print(AS726Xsensor.getCalibrated_duv(), 4);
    Serial.print("] CCT2[");
    Serial.print(AS726Xsensor.getCalculated_CCT(), 4);
  }

  Serial.print("] tempC[");
  Serial.print(AS726Xsensor.getTemperature(), 1);
  Serial.print("]");

  Serial.println();
}