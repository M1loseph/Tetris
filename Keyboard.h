#pragma once
#include "Controller.h"

// can be used with usb or bluettoth connection
class Keyboard : public Controller {
  public:

    Keyboard(char left, char right, char up, char down, char button);

    bool Up() const;
    bool Down() const;
    bool Left() const;
    bool Right() const;
    bool Button() const;
    
  private:
    char m_Left, m_Right, m_Up, m_Down, m_Button;
};
