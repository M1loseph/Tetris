#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

class Controller {
  public:
    virtual bool Up() const;
    virtual bool Down() const;
    virtual bool Left() const;
    virtual bool Right() const;
    virtual bool Button() const;
    bool ButtonPressed() const;
    bool DownPressed() const;
    bool UpPressed() const;
    bool LeftPressed() const;
    bool RightPressed() const;
    

  private:
    bool IfPressedOnce(bool& released, bool pressed) const;
};

#endif // __CONTROLLER_HPP__