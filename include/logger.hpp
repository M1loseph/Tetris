#include <Arduino.h>

#ifdef __DEBUG__

#define SERIAL_PRINTLN(string) Serial.println(F(string));
#define SERIAL_PRINTLN_INT(number) Serial.println(number);
#define SERIAL_PRINT(string) Serial.print(F(string));
#define SERIAL_PRINT_INT(number) Serial.print(number);

#else

#define SERIAL_PRINTLN(string)
#define SERIAL_PRINTLN_INT(number)
#define SERIAL_PRINT(string)
#define SERIAL_PRINT_INT(number)

#endif