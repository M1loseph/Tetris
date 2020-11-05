#ifndef __DUMMY__
#ifndef UNIT_TEST
#include <Arduino.h>
#include "brick.hpp"
#include "game.hpp"
#include "serial_controller.hpp"
#include "config.hpp"

void setup()
{
    // to generate random seed
    randomSeed(analogRead(A2));
    Serial.begin(115200);
}

void loop()
{
    MD_MAX72XX matrix(MD_MAX72XX::FC16_HW, DATA_PIN, CLK_PIN, CS_PIN, SEGMENTS);
    renderer renderer(matrix);
    renderer.init();
    serial_controller keyboard(Serial, 'a', 'd', 'w', 's', ' ');
    game<serial_controller> game(keyboard, renderer);
    game.start();
}
#endif // UNIT_TEST
#endif //__DUMMY__