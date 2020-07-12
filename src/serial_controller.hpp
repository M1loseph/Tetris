#ifndef __SERIAL_CONTROLLER_HPP__
#define __SERIAL_CONTROLLER_HPP__

#include "Controller.hpp"

// can be used with usb or bluettoth connection
class serial_controller : public controller
{
public:
  explicit serial_controller(char left, char right, char up, char down, char button);

  bool up() const;
  bool down() const;
  bool left() const;
  bool right() const;
  bool button() const;

private:
  int _left, _right, _up, _down, _button;
};

#endif // __SERIAL_CONTROLLER_HPP__