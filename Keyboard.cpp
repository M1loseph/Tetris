#include "Keyboard.h"
#include <Arduino.h>

Keyboard::Keyboard(char left, char right, char up, char down, char button) {
  m_Left = left;
  m_Right = right;
  m_Down = down;
  m_Up = up;
  m_Button = button;
}

bool Keyboard::Up() const {
  bool resoult = Serial.read() == m_Up;
  Serial.flush();
  return resoult;
}
bool Keyboard::Down() const {
  bool resoult =  Serial.read() == m_Down;
  Serial.flush();
  return resoult;
}
bool Keyboard::Right() const {
  bool resoult =  Serial.read() == m_Left;
  Serial.flush();
  return resoult;
}
bool Keyboard::Left() const {
  bool resoult =  Serial.read() == m_Right;
  Serial.flush();
  return resoult;
}
bool Keyboard::Button() const {
  bool resoult =  Serial.read() == m_Button;
  Serial.flush();
  return resoult;
}
