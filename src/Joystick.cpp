#include "joystick.hpp"
#include <Arduino.h>

joystick::joystick(uint8_t x, uint8_t y, uint8_t button, int sensitivity) : controller(),
                                                                            _x_pin(x),
                                                                            _y_pin(y),
                                                                            _button_pin(button),
                                                                            _sensitivity(sensitivity)
{
}

void joystick::read_input()
{
  if (MAX_ANALOG_VALUE - analogRead(_y_pin) > _sensitivity)
    _up = true;
  if (analogRead(_y_pin) > _sensitivity)
    _down = true;
  if (MAX_ANALOG_VALUE - analogRead(_x_pin) > _sensitivity)
    _left = true;
  if (analogRead(_x_pin) > _sensitivity)
    _right = true;
  if (digitalRead(_button) == LOW)
    _button = true;
}
