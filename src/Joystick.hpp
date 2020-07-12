#ifndef __JOYSTICK_HPP__
#define __JOYSTICK_HPP__

#include "controller.hpp"
#include <stdlib.h>

class joystick final : public controller
{
public:
  explicit joystick(int x, int y, int button, int stickSens = DEF_SENSITIVITY);

  void read_input();

  static constexpr int DEF_SENSITIVITY = 900;
  // this value may differ among different devices
  static constexpr int MAX_ANALOG_VALUE = 1023;

private:
  const int _x_pin, _y_pin, _button_pin, _sensitivity;
};

#endif // __JOYSTICK_HPP__