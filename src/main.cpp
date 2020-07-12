#include <Arduino.h>
#include "brick.hpp"
#include "game.hpp"
#include "joystick.hpp"
#include "serial_controller.hpp"

// screen info
uint8_t CLK_PIN = 13;
uint8_t DATA_PIN = 11;
uint8_t CS_PIN = 10;

// joystick pins
uint8_t JOYSTICK_X = A4;
uint8_t JOYSTICK_Y = A5;
uint8_t JOYSTICK_B = 2;

constexpr size_t falling_interval = 1000U;
constexpr size_t user_input_interval = 1000U;

void setup()
{
  randomSeed(analogRead(A2));
  Serial.begin(9600);
}

void loop()
{
  MD_MAX72XX matrix(MD_MAX72XX::FC16_HW, DATA_PIN, CLK_PIN, CS_PIN);
  renderer renderer(matrix);
  renderer.init();
  joystick joystick(JOYSTICK_X, JOYSTICK_Y, JOYSTICK_B);
  serial_controller keyboard('a', 'd', 'w', 's', ' ');
  game game(joystick, renderer, falling_interval, user_input_interval);
  game.start();
}
