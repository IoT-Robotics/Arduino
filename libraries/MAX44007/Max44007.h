#pragma once

//    FILE: Max44007.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: library for Max44007 lux sensor Arduino
// HISTORY: See Max44007.cpp


//  breakout MAX44007
//
//      +--------+
//  VCC |o       |
//  GND |o       |
//  SCL |o      o| ADDRESS
//  SDA |o      o| -INT
//      +--------+
//
// ADDRESS:
// 0 = 0x4A
// 1 = 0x4B
//
// INT:
// Connect the INT pin to an pull up resistor
// 0 = interrupt
// 1 = no interrupt
// connect to an LED or an interrupt pin of an Arduino
//


#include "Wire.h"
#include "Arduino.h"


#define Max44007_LIB_VERSION                  (F("0.1.0"))

#define Max44007_DEFAULT_ADDRESS              0x5A
#define Max44007_ALT_ADDRESS                  0x5B


// REGISTERS
#define Max44007_INTERRUPT_STATUS             0x00
#define Max44007_INTERRUPT_ENABLE             0x01
#define Max44007_CONFIGURATION                0x02
#define Max44007_LUX_READING_HIGH             0x03
#define Max44007_LUX_READING_LOW              0x04
#define Max44007_THRESHOLD_HIGH               0x05
#define Max44007_THRESHOLD_LOW                0x06
#define Max44007_THRESHOLD_TIMER              0x07


// CONFIGURATION MASKS
#define Max44007_CFG_CONTINUOUS               0x80
#define Max44007_CFG_MANUAL                   0x40
#define Max44007_CFG_CDR                      0x08
#define Max44007_CFG_TIMER                    0x07


// ERROR CODES
#define Max44007_OK                           0
#define Max44007_ERROR_WIRE_REQUEST           -10
#define Max44007_ERROR_OVERFLOW               -20
#define Max44007_ERROR_HIGH_BYTE              -30
#define Max44007_ERROR_LOW_BYTE               -31



class Max44007
{
public:
  // enum class to prevent bool to be implicitly casted to int
  enum class Boolean { True, False };

#if defined(ESP8266) || defined(ESP32)
  // dataPin and clockPin can be used for ESP8266
  Max44007(const uint8_t address, const uint8_t dataPin, const uint8_t clockPin);
#endif

  // ctor for UNO
  Max44007(const uint8_t address, const Boolean begin = Boolean::True);
  // default ctor with default address
  Max44007(const Boolean begin = Boolean::True);
  // Change I2C interface and address
  void configure(const uint8_t address, TwoWire *wire, const Boolean begin = Boolean::True);

  bool    isConnected();
  float   getLux();
  int     getError();

  // threshold must be between 0 and 188006
  bool    setHighThreshold(const float value);       // returns false if value out of range
  float   getHighThreshold(void);
  bool    setLowThreshold(const float value);        // returns false if value out of range
  float   getLowThreshold(void);
  void    setThresholdTimer(const uint8_t value);    // 2 seems practical minimum
  uint8_t getThresholdTimer();

  void    enableInterrupt()    { write(Max44007_INTERRUPT_ENABLE, 1); };
  void    disableInterrupt()   { write(Max44007_INTERRUPT_ENABLE, 0); };
  bool    interruptEnabled()   { return read(Max44007_INTERRUPT_ENABLE) & 0x01; };
  uint8_t getInterruptStatus() { return read(Max44007_INTERRUPT_STATUS) & 0x01; };

  // check datasheet for detailed behavior
  void    setConfiguration(uint8_t);
  uint8_t getConfiguration();
  void    setAutomaticMode();
  void    setContinuousMode();    // uses more power
  void    clrContinuousMode();    // uses less power
  // CDR = Current Divisor Ratio
  // CDR = 1 ==> only 1/8th is measured
  // TIM = Time Integration Measurement (table)
  // 000  800ms
  // 001  400ms
  // 010  200ms
  // 011  100ms
  // 100   50ms       manual only
  // 101   25ms       manual only
  // 110   12.5ms     manual only
  // 111    6.25ms    manual only
  void    setManualMode(uint8_t CDR, uint8_t TIM);
  int     getIntegrationTime() { return 800 >> (getConfiguration() & 0x07); };  // ms

  // TEST the math
  float   convertToLux(uint8_t datahigh, uint8_t datalow);


protected:
  bool    setThreshold(uint8_t reg, float value);
  float   getThreshold(uint8_t reg);

  uint8_t read(uint8_t reg);
  void    write(uint8_t reg, uint8_t value);

  uint8_t _address;
  uint8_t _data;
  int     _error;

  TwoWire* _wire;
};


// -- END OF FILE --

