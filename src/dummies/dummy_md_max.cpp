#ifdef __DUMMY_MD_MAX__
#ifndef UNIT_TEST
#include <Arduino.h>
#include <MD_MAX72xx.h>

// screen info
constexpr uint8_t CLK_PIN = 13;
constexpr uint8_t DATA_PIN = 11;
constexpr uint8_t CS_PIN = 10;
constexpr uint8_t SEGMENTS = 4;

MD_MAX72XX matrix(MD_MAX72XX::FC16_HW, DATA_PIN, CLK_PIN, CS_PIN, SEGMENTS);
void setup()
{
    matrix.begin();
    matrix.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    matrix.clear();
}

void loop()
{
    for (uint8_t i = 0; i < 32; i++)
    {
        matrix.setColumn(i, 255U);
        delay(200);
    }
    delay(1000);
    matrix.clear();
    delay(1000);
}

#endif // __DUMMY_MD_MAX__
#endif // UNIT_TEST