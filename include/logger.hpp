#include <Arduino.h>

#ifdef __DEBUG__

#define SERIAL_PRINTLN(string) Serial.println(string)
#define SERIAL_PRINT(string) Serial.print(string)

#define CHECK_IMPLEMENTATION(pixel)             \
    if (pixel == brick::pixel_info::NOT_FOUND) \
    SERIAL_PRINTLN("Implementation error! Pixel was not found")

#else
#define SERIAL_PRINTLN(string)
#define SERIAL_PRINT(string)
#define CHECK_IMPLEMENTATION(pixel)
#endif