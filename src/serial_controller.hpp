#ifndef __SERIAL_CONTROLLER_HPP__
#define __SERIAL_CONTROLLER_HPP__

#include "Controller.hpp"

// can be used with usb or bluettoth connection
class serial_controller : public controller
{
public:
  explicit serial_controller(char left, char right, char up, char down, char button);
  void read_input();

private:
  const char _left_char, _right_char, _up_char, _down_char, _button_char;
};

#endif // __SERIAL_CONTROLLER_HPP__