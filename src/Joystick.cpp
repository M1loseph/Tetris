#include "joystick.hpp"
#include <Arduino.h>

joystick::joystick(int x, int y, int button, int sensitivity)
{
  _x = x;
  _y = y;
  _button = button;
  _sensitivity = sensitivity;
}

bool joystick::up() const
{
  return MAX_ANALOG_VALUE - analogRead(_y) > _sensitivity;
}

bool joystick::down() const
{
  return analogRead(_y) > _sensitivity;
}

bool joystick::left() const
{
  return MAX_ANALOG_VALUE - analogRead(_x) > _sensitivity;
}

bool joystick::right() const
{
  return analogRead(_x) > _sensitivity;
}

bool joystick::button() const
{
  // it turned out joystick button works in pullup mode
  return digitalRead(_button) == LOW;
}
