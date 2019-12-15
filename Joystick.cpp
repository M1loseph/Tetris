#include "Joystick.h"
#include <Arduino.h>

Joystick::Joystick(int xAxile, int yAxile, int button, int sensitivity, int buttonSens) {
  m_xAxile =  xAxile;
  m_yAxile = yAxile;
  m_Button = button;
  m_StickSens = sensitivity;
  m_ButtonSens = buttonSens;
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
bool Joystick::Button() const {
  return analogRead(m_Button < 40);
}
