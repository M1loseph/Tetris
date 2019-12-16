#include "SerialController.h"
#include <Arduino.h>

SerialController::SerialController(char left, char right, char up, char down, char button) {
  m_Left = left;
  m_Right = right;
  m_Down = down;
  m_Up = up;
  m_Button = button;
}

bool SerialController::Up() const {
  bool resoult = Serial.read() == m_Up;
  Serial.flush();
  return resoult;
}
bool SerialController::Down() const {
  bool resoult =  Serial.read() == m_Down;
  Serial.flush();
  return resoult;
}
bool SerialController::Right() const {
  bool resoult =  Serial.read() == m_Right;
  Serial.flush();
  return resoult;
}
bool SerialController::Left() const {
  bool resoult =  Serial.read() == m_Left;
  Serial.flush();
  return resoult;
}
bool SerialController::Button() const {
  bool resoult =  Serial.read() == m_Button;
  Serial.flush();
  return resoult;
}
