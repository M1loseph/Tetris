#ifndef __JOYSTICK_HPP__
#define __JOYSTICK_HPP__

#include "controller.hpp"
#include <stdint.h>

// TODO => ADD SUPPORT FOR REVERSING AXES
// TODO => IMPROVE IMPLEMENTATION TO MAKE IT EASIER TO MOVE (KEYBOARD IS GOIND MUCH BETTER RIGHT NOW)
class joystick final : public controller
{
public:
  explicit joystick(uint8_t x, uint8_t y, uint8_t button, int stickSens = _def_sens);

  void read_input();

  static constexpr int _def_sens = 900;
  // this value may differ among different devices
  static constexpr int _max_analog = 1023;
  static constexpr unsigned long _debounce_delay = 20;

private:
  void check_reading(bool pred, bool &current, bool &released);

  const uint8_t _x_pin, _y_pin, _button_pin;
  const int _sensitivity;

  bool _up_released, _down_released, _left_released, _right_released, _button_released;
};

#endif // __JOYSTICK_HPP__