#ifndef __JOYSTICK_HPP__
#define __JOYSTICK_HPP__

#include "Controller.hpp"

#define DEF_STICK_SENS 900

class Joystick : public Controller {
  public:

    Joystick(int xAxile, int yAxile, int button, int stickSens = DEF_STICK_SENS);

    bool Up() const;
    bool Down() const;
    bool Left() const;
    bool Right() const;
    bool Button() const;
    
  private:
    bool IfPressedOnce(bool& released, bool pressed) const;
    int m_xAxile, m_yAxile, m_Button, m_StickSens;
};

#endif // __JOYSTICK_HPP__ 