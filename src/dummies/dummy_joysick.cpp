#ifdef __DUMMY_MAIN__
#ifndef UNIT_TEST
#include <Arduino.h>
#include "logger.hpp"
#include "brick.hpp"
#include "game.hpp"
#include "joystick.hpp"
#include "serial_controller.hpp"

// screen info
constexpr uint8_t CLK_PIN = 13;
constexpr uint8_t DATA_PIN = 11;
constexpr uint8_t CS_PIN = 10;
constexpr uint8_t SEGMENTS = 4;

// joystick pins
constexpr uint8_t JOYSTICK_X = A4;
constexpr uint8_t JOYSTICK_Y = A5;
constexpr uint8_t JOYSTICK_B = 2;

constexpr size_t falling_interval = 1000U;
constexpr size_t user_input_interval = 1000U;

joystick joystick(JOYSTICK_X, JOYSTICK_Y, JOYSTICK_B);
unsigned long last_time;

void setup()
{
    randomSeed(analogRead(A2));
    pinMode(JOYSTICK_B, INPUT_PULLUP);
    Serial.begin(115200);
    last_time = millis();
}

void loop()
{
    joystick.read_input();
    if (millis() - last_time > 500)
    {
        last_time = millis();
        SERIAL_PRINT("Left: ");
        SERIAL_PRINTLN(joystick.left());
        SERIAL_PRINT("Right: ");
        SERIAL_PRINTLN(joystick.right());
        SERIAL_PRINT("Up: ");
        SERIAL_PRINTLN(joystick.up());
        SERIAL_PRINT("Down: ");
        SERIAL_PRINTLN(joystick.down());
        joystick.reset();
    }
}

#endif //UNIT_TEST
#endif // __DUMMY_MAIN__