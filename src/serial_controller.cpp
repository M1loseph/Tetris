#include "serial_controller.hpp"
#include <Arduino.h>

serial_controller::serial_controller(char left, char right, char up, char down, char button)
{
  _left = left;
  _right = right;
  _down = down;
  _up = up;
  _button = button;
}

bool serial_controller::up() const
{
  bool resoult = Serial.read() == _up;
  return resoult;
}

bool serial_controller::down() const
{
  bool resoult = Serial.read() == _down;
  return resoult;
}

bool serial_controller::right() const
{
  bool resoult = Serial.read() == _right;
  return resoult;
}

bool serial_controller::left() const
{
  bool resoult = Serial.read() == _left;
  return resoult;
}

bool serial_controller::button() const
{
  bool resoult = Serial.read() == _button;
  return resoult;
}
