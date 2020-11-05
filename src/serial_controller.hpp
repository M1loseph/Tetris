#ifndef __SERIAL_CONTROLLER_HPP__
#define __SERIAL_CONTROLLER_HPP__

#include <Arduino.h>
#include "controller.hpp"

// can be used with usb or bluettoth connection
class serial_controller : public controller<serial_controller>
{
public:
    explicit serial_controller(Stream &stream, char left, char right, char up, char down, char button);
    void read_input();

private:
    Stream &_stream;
    const char _left_char, _right_char, _up_char, _down_char, _button_char;
};

#endif // __SERIAL_CONTROLLER_HPP__