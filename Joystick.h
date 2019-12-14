#pragma once
#define DEF_STICK_SENS 900
#define DEF_BUTTON_SENS 100

class Joystick {
  public:

    Joystick(int xAxile, int yAxile, int button, int stickSens = DEF_STICK_SENS, int buttonSens = DEF_BUTTON_SENS);

    int GetX() const;
    int GetY() const;
    bool Up() const;
    bool Down() const;
    bool Left() const;
    bool Right() const;
    bool ButtonPressed() const;
    bool DownPressed() const;
    bool UpPressed() const;
    bool LeftPressed() const;
    bool RightPressed() const;
    

  private:
    bool IfPressedOnce(bool& released, bool pressed) const;
    int m_xAxile, m_yAxile, m_Button, m_StickSens, m_ButtonSens;
};
