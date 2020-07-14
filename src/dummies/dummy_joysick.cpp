#ifdef __DUMMY_JOYSIC__
#ifndef UNIT_TEST
#include <Arduino.h>
#include "joystick.hpp"
#include "serial_controller.hpp"

// joystick pins
constexpr uint8_t JOYSTICK_X = A4;
constexpr uint8_t JOYSTICK_Y = A5;
constexpr uint8_t JOYSTICK_B = 2;

joystick j(JOYSTICK_X, JOYSTICK_Y, JOYSTICK_B);
serial_controller s(Serial, 'a', 'd', 'w', 's', ' ');
unsigned long last_time;

void setup()
{
    pinMode(JOYSTICK_B, INPUT_PULLUP);
    Serial.begin(115200);
    last_time = millis();
}

void loop()
{
    j.read_input();
    s.read_input();
    if (millis() - last_time > 1000)
    {
        last_time = millis();
        Serial.println("JOYSTICK");
        Serial.print("Left: ");
        Serial.println(j.left());
        Serial.print("Right: ");
        Serial.println(j.right());
        Serial.print("Up: ");
        Serial.println(j.up());
        Serial.print("Down: ");
        Serial.println(j.down());
        Serial.print("Button: ");
        Serial.println(j.button());
        j.reset();

        Serial.println("\nSERIAL");
        Serial.print("Left: ");
        Serial.println(s.left());
        Serial.print("Right: ");
        Serial.println(s.right());
        Serial.print("Up: ");
        Serial.println(s.up());
        Serial.print("Down: ");
        Serial.println(s.down());
        Serial.print("Button: ");
        Serial.println(s.button());
        s.reset();
    }
}

#endif // UNIT_TEST
#endif // __DUMMY_JOYSIC__