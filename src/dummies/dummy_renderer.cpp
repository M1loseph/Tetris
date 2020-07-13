#ifdef __DUMMY_RENDERER__
#ifndef UNIT_TEST
#include <Arduino.h>
#include "renderer.hpp"

// screen info
constexpr uint8_t CLK_PIN = 13;
constexpr uint8_t DATA_PIN = 11;
constexpr uint8_t CS_PIN = 10;
constexpr uint8_t SEGMENTS = 4;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    MD_MAX72XX matrix(MD_MAX72XX::FC16_HW, DATA_PIN, CLK_PIN, CS_PIN, SEGMENTS);
    renderer renderer(matrix);
    renderer.init();
    renderer.render(100);
}

#endif // UNIT_TEST
#endif // __DUMMY_RENDERER__