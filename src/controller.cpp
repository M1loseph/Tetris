#include "controller.hpp"

controller::controller() : _up(false),
                               _down(false),
                               _left(false),
                               _right(false)
{
}

void controller::reset()
{
    _up = false;
    _down = false;
    _left = false;
    _right = false;
    _button = false;
}

bool controller::up() const
{
    return _up;
}
bool controller::down() const
{
    return _down;
}
bool controller::left() const
{
    return _left;
}
bool controller::right() const
{
    return _right;
}
bool controller::button() const
{
    return _button;
}