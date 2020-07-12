#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

// interface, that needs to be implemented to use different types of controlls to play Tetris
// it can be anything, from joystick, some buttons, keypad or ever Serial communication
class controller
{
public:
  controller();

  virtual void read_input() = 0;
  void reset();

  bool up() const;
  bool down() const;
  bool left() const;
  bool right() const;
  bool button() const;

protected:
  bool _up, _down, _left, _right, _button;
};

#endif // __CONTROLLER_HPP__