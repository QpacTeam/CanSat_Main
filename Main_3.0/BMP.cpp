#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "BMP.h"

const float cPress = 1013.25;    // < Constans sea level pressure in hPa (hectopascal)
const unsigned int size = 3;

double BMP_Data[size];
Adafruit_BMP280 bmp;
float temperature;
float pressure;
float altitude;

void BMP_Init(void) {
  unsigned int status;
  status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void BMP_Run(void) {
  temperature = bmp.readTemperature();    BMP_Data[0] = temperature;  // < celsius 
  pressure    = bmp.readPressure();       BMP_Data[1] = pressure;     // < Pa (pascal)
  altitude    = bmp.readAltitude(cPress); BMP_Data[2] = altitude;     // < meter
}

double* BMP_GetData(void) return BMP_Data;
//unsigned int BMP_GetDataSize(void) return size;
