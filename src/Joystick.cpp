#include "joystick.hpp"
#include <Arduino.h>

joystick::joystick(uint8_t x, uint8_t y, uint8_t button, int sensitivity) : controller(),
                                                                            _x_pin(x),
                                                                            _y_pin(y),
                                                                            _button_pin(button),
                                                                            _sensitivity(sensitivity),
                                                                            _up_released(false),
                                                                            _down_released(false),
                                                                            _left_released(false),
                                                                            _right_released(false),
                                                                            _button_released(false)
{
}

void joystick::read_input()
{
  static unsigned long _last_debounce = millis();
  const int x = analogRead(_x_pin);
  const int y = analogRead(_y_pin);
  const bool button_reading = digitalRead(_button_pin);

  check_reading(_max_analog - y > _sensitivity, _up, _up_released);
  check_reading(y > _sensitivity, _down, _down_released);
  check_reading(_max_analog - x > _sensitivity, _left, _left_released);
  check_reading(x > _sensitivity, _right, _right_released);
  // my joystick has a button that needs to be pulled up
  if (millis() - _last_debounce > _debounce_delay)
  {
    check_reading(button_reading == LOW, _button, _button_released);
    _last_debounce = millis();
  }
}

void joystick::check_reading(bool pred, bool &current, bool &released)
{
  if (pred)
  {
    if (released)
    {
      current = true;
      released = false;
    }
  }
  else
  {
    released = true;
  }
}