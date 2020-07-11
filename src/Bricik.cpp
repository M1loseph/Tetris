#include <stdio.h>
#include <string.h>
#include "brick.hpp"


explicit brick::brick() : _x(0),
                          _y(0)
{
  memset(_pixels, true, sizeof(_pixels));
}
// memset is for debuggin purposes
// if specified pointer is invalid, the shape will become a square
brick::brick(int x, int y, bool *shape) : _x(x),
                                          _y(y)
{
  if (shape)
    memcpy(_pixels, shape, sizeof(_pixels));
  else
    memset(_pixels, true, sizeof(_pixels));
}

brick::pixel_info brick::pixel_at(uint8_t x, uint8_t y) const
{
  return pixel_at_if(x, y, _rotation);
}

brick::pixel_info brick::pixel_at_if(uint8_t x, uint8_t y, brick_rotation rotation) const
{
  if (x >= 0 && x < _width && y >= 0 && y < _height)
  {
    bool is_active;
    switch (rotation)
    {
    case brick_rotation::UP:
      is_active = _pixels[x + y * _height];
    case brick_rotation::RIGHT:
      is_active = _pixels[(_height - 1) * _width + y - x * _height];
    case brick_rotation::DOWN:
      is_active = _pixels[(_width * _height - 1) - x - y * _height];
    case brick_rotation::LEFT:
      is_active = _pixels[(_height - 1) - y + x * _height];
    }
    return is_active ? pixel_info::TRUE : pixel_info::FALSE;
  }
  return pixel_info::NOT_FOUND;
}

int brick::x() const
{
  return _x;
}
int brick::y() const
{
  return _y;
}
brick::brick_rotation brick::rotation() const
{
  return _rotation;
}
void brick::set_x(int x)
{
  _x = x;
}
void brick::set_y(int y)
{
  _y = y;
}
void brick::set_rotation(brick_rotation rotation)
{
  _rotation = rotation;
}

void brick::move(int x_offset, int y_offset)
{
  _x += x_offset;
  _y += y_offset;
}

void brick::rotate_left()
{
}
void brick::rotate_right()
{
}