#ifndef __SERIAL_CONTROLLER_HPP__
#define __SERIAL_CONTROLLER_HPP__

#include "Controller.hpp"

// can be used with usb or bluettoth connection
class SerialController : public Controller {
  public:

    SerialController(char left, char right, char up, char down, char button);

    bool Up() const;
    bool Down() const;
    bool Left() const;
    bool Right() const;
    bool Button() const;
    
  private:
    int m_Left, m_Right, m_Up, m_Down, m_Button;
};

#endif // __SERIAL_CONTROLLER_HPP__