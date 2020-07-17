#include "serial_controller.hpp"
#include <Arduino.h>

serial_controller::serial_controller(Stream &stream, char left, char right, char up, char down, char button) : controller(),
                                                                                                               _stream(stream),
                                                                                                               _left_char(left),
                                                                                                               _right_char(right),
                                                                                                               _up_char(up),
                                                                                                               _down_char(down),
                                                                                                               _button_char(button)
{
}

void serial_controller::read_input()
{
  while (Serial.available())
  {
    const char c = Serial.read();
    if (c == _up_char)
      _up = true;
    else if (c == _down_char)
      _down = true;
    else if (c == _left_char)
      _left = true;
    else if (c == _right_char)
      _right = true;
    else if (c == _button_char)
      _button = true;
  }
}