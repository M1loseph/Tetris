#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

// abstract class, that needs to be implemented to use different types of controlls to play Tetris
// it can be anything, from joystick, some buttons, keypad or ever Serial communication
template <class Derived>
class controller
{
public:
  explicit controller() : _up(false),
                          _down(false),
                          _left(false),
                          _right(false)
  {
  }

  // controller(const controller<Derived>& other) = delete;

  void read_input()
  {
    static_cast<Derived *>(this)->read_input();
  }

  void reset()
  {
    _up = false;
    _down = false;
    _left = false;
    _right = false;
    _button = false;
  }

  bool up() const
  {
    return _up;
  }
  bool down() const
  {
    return _down;
  }
  bool left() const
  {
    return _left;
  }
  bool right() const
  {
    return _right;
  }
  bool button() const
  {
    return _button;
  }

protected:
  bool _up, _down, _left, _right, _button;
};

#endif // __CONTROLLER_HPP__