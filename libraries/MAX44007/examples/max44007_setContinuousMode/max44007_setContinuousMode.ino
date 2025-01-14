//
//    FILE: Max44007_setContinuousMode.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Max44007 library
//    DATE: 2022-01-04
//
//  note that lux values are repeated a number of times
//  if read faster than the integration time.
//  So it makes no sense to call getLux() more than once
//  per integration time.
//  NB the getLux() call takes a bit more than 1 millisecond


#include "Wire.h"
#include "Max44007.h"

Max44007 myLux(0x5A);

uint32_t lastDisplay = 0;
uint32_t start = 0;
uint32_t stop = 0;
int count = 0;


void setup()
{
  Serial.begin(115200);
  Serial.print("\nStart Max44007_setContinuousMode : ");
  Serial.println(Max44007_LIB_VERSION);

  Wire.begin();

  myLux.setContinuousMode();
}


void loop()
{
  uint32_t interval = 100;
  if (millis() - lastDisplay >= interval)
  {
    lastDisplay += interval;
    count++;
    start = micros();
    float lux = myLux.getLux();
    stop = micros();
    int err = myLux.getError();
    if (err != 0)
    {
      Serial.print("Error:\t");
      Serial.println(err);
    }
    else
    {
      Serial.print("lux:\t");
      Serial.print(lux);
      Serial.print("\ttime:\t");
      Serial.print(stop - start);
      Serial.println();
    }
  }
  if (count == 5) myLux.clrContinuousMode();
  if (count == 10)
  {
    count = 0;
    myLux.setContinuousMode();
  }
}


// -- END OF FILE --

