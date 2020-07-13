#include <Arduino.h>

#ifdef __DEBUG__
#define SERIAL_PRINTLN(string) Serial.println(string)
#define SERIAL_PRINT(string) Serial.print(string)
#else
#define SERIAL_PRINTLN(string)
#define SERIAL_PRINT(string)
#endif