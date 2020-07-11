#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

// interface, that needs to be implemented to use different types of controlls to play Tetris
// it can be anything, from joystick, some buttons, keypad or ever Serial communication
class controller
{
public:
  virtual bool up() const = 0;
  virtual bool down() const = 0;
  virtual bool left() const = 0;
  virtual bool right() const = 0;
  virtual bool button() const = 0;
};

#endif // __CONTROLLER_HPP__