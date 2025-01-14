//
//    FILE: MS5611_performance_all.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo application
//    DATE: 2021-12-24
//     URL: https://github.com/RobTillaart/MS5611


#include "MS5611.h"

MS5611 MS5611(0x77);   // 0x76 = CSB to VCC; 0x77 = CSB to GND

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.print(__FILE__);
  Serial.print("MS5611 lib version: ");
  Serial.println(MS5611_LIB_VERSION);

  if (MS5611.begin())
  {
    Serial.println("MS5611 found.");
  }
  else
  {
    Serial.println("MS5611 not found. halt.");
    while(1);
  }

  Serial.println("OSR \t TIME");


  start = micros();
  MS5611.read();   // uses default OSR_ULTRA_LOW  (fastest)
  stop = micros();
  Serial.print( (uint8_t) MS5611.getOversampling());
  Serial.print("\t");
  Serial.println(stop - start);
  delay(10); // to flush serial.


  MS5611.setOversampling(OSR_LOW);
  start = micros();
  MS5611.read();
  stop = micros();
  Serial.print( (uint8_t) MS5611.getOversampling());
  Serial.print("\t");
  Serial.println(stop - start);
  delay(10); // to flush serial.


  MS5611.setOversampling(OSR_STANDARD);
  start = micros();
  MS5611.read();
  stop = micros();
  Serial.print( (uint8_t) MS5611.getOversampling());
  Serial.print("\t");
  Serial.println(stop - start);
  delay(10); // to flush serial.


  MS5611.setOversampling(OSR_HIGH);
  start = micros();
  MS5611.read();
  stop = micros();
  Serial.print( (uint8_t) MS5611.getOversampling());
  Serial.print("\t");
  Serial.println(stop - start);
  delay(10); // to flush serial.


  MS5611.setOversampling(OSR_ULTRA_HIGH);
  start = micros();
  MS5611.read();
  stop = micros();
  Serial.print( (uint8_t) MS5611.getOversampling());
  Serial.print("\t");
  Serial.println(stop - start);
  delay(10); // to flush serial.


  Serial.println("\ndone...");
}

void loop()
{
}


// -- END OF FILE --

