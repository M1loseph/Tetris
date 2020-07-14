#ifndef __DUMMY__
#ifndef UNIT_TEST
#include <Arduino.h>
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
constexpr size_t user_input_interval = 500U;

void setup()
{
  randomSeed(analogRead(A2));
  Serial.begin(115200);
  pinMode(JOYSTICK_B, INPUT_PULLUP);
}

void loop()
{
  MD_MAX72XX matrix(MD_MAX72XX::FC16_HW, DATA_PIN, CLK_PIN, CS_PIN, SEGMENTS);
  renderer renderer(matrix);
  renderer.init();
  joystick joystick(JOYSTICK_X, JOYSTICK_Y, JOYSTICK_B);
  serial_controller keyboard(Serial, 'a', 'd', 'w', 's', ' ');
  game game(joystick, renderer, falling_interval, user_input_interval);
  game.start();
}
#endif // UNIT_TEST
#endif //__DUMMY__