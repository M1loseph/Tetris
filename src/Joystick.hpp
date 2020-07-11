#ifndef __JOYSTICK_HPP__
#define __JOYSTICK_HPP__

#include "Controller.hpp"

class joystick : public controller
{
public:
  joystick(int x, int y, int button, int stickSens = DEF_SENSITIVITY);

  bool up() const;
  bool down() const;
  bool left() const;
  bool right() const;
  bool button() const;

  static constexpr size_t DEF_SENSITIVITY = 900;
  // this value may differ among different devices
  static constexpr size_t MAX_ANALOG_VALUE = 1023;

private:
  int _x, _y, _button, _sensitivity;
};

#endif // __JOYSTICK_HPP__