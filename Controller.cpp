#include "Controller.h"

bool Controller::ButtonPressed() const {
  static bool released = true;
  return IfPressedOnce(released, Button());
}
bool Controller::DownPressed() const {
  static bool released = true;
  return IfPressedOnce(released, Down());
}
bool Controller::UpPressed() const {
  static bool released = true;
  return IfPressedOnce(released, Up());
}
bool Controller::LeftPressed() const {
  static bool released = true;
  return IfPressedOnce(released, Left());
}
bool Controller::RightPressed() const {
  static bool released = true;
  return IfPressedOnce(released, Right());
}
bool Controller::IfPressedOnce(bool& released, bool pressed) const
{
  if (pressed)
  {
    if (released)
    {
      released = false;
      return true;
    }
    return false;
  }
  released = true;
  return false;
}
