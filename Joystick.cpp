#include "Joystick.h"
#include <Arduino.h>

Joystick::Joystick(int xAxile, int yAxile, int button, int sensitivity, int buttonSens) {
  m_xAxile =  xAxile;
  m_yAxile = yAxile;
  m_Button = button;
  m_StickSens = sensitivity;
  m_ButtonSens = buttonSens;
}

int Joystick::GetX() const {
  return analogRead(m_xAxile);
}

int Joystick::GetY() const {
  return analogRead(m_yAxile);
}

bool Joystick::Up() const {
  return 1023 - analogRead(m_yAxile) > m_StickSens;
}
bool Joystick::Down() const {
  return analogRead(m_yAxile) > m_StickSens;
}
bool Joystick::Right() const {
  return 1023 - analogRead(m_xAxile) > m_StickSens;
}
bool Joystick::Left() const {
  return analogRead(m_xAxile) > m_StickSens;
}
bool Joystick::ButtonPressed() const {
  static bool released = true;
  return IfPressedOnce(released, analogRead(m_Button) < m_ButtonSens);
}
bool Joystick::DownPressed() const {
  static bool released = true;
  return IfPressedOnce(released, Down());
}
bool Joystick::UpPressed() const {
  static bool released = true;
  return IfPressedOnce(released, Up());
}
bool Joystick::LeftPressed() const {
  static bool released = true;
  return IfPressedOnce(released, Left());
}
bool Joystick::RightPressed() const {
  static bool released = true;
  return IfPressedOnce(released, Right());
}
bool Joystick::IfPressedOnce(bool& released, bool pressed) const
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
