#include "Joystick.h"
#include <Arduino.h>

Joystick::Joystick(int xAxile, int yAxile, int button, int sensitivity) {
  pinMode(button, INPUT_PULLUP);
  m_xAxile =  xAxile;
  m_yAxile = yAxile;
  m_Button = button;
  m_StickSens = sensitivity;
}


bool Joystick::Up() const {
  return 1023 - analogRead(m_yAxile) > m_StickSens;
}
bool Joystick::Down() const {
  return analogRead(m_yAxile) > m_StickSens;
}
bool Joystick::Left() const {
  return 1023 - analogRead(m_xAxile) > m_StickSens;
}
bool Joystick::Right() const {
  return analogRead(m_xAxile) > m_StickSens;
}
bool Joystick::Button() const {
  return digitalRead(m_Button) == LOW;
}
