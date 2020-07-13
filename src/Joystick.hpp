#ifndef __JOYSTICK_HPP__
#define __JOYSTICK_HPP__

#include "controller.hpp"
#include <stdlib.h>

typedef unsigned char uint8_t;

class joystick final : public controller
{
public:
  explicit joystick(uint8_t x, uint8_t y, uint8_t button, int stickSens = DEF_SENSITIVITY);

  void read_input();

  static constexpr int DEF_SENSITIVITY = 900;
  // this value may differ among different devices
  static constexpr int MAX_ANALOG_VALUE = 1023;

private:
  const uint8_t _x_pin, _y_pin, _button_pin;
  const int _sensitivity;
};

#endif // __JOYSTICK_HPP__