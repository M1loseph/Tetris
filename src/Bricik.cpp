#include <stdio.h>
#include <string.h>
#include "brick.hpp"

brick::brick() : _x(0),
                 _y(0),
                 _rotation(brick_rotation::UP)
{
  memset(_pixels, true, sizeof(_pixels));
}

// memset is for debuggin purposes
// if specified pointer is invalid, the shape will become a square
brick::brick(int x, int y, const bool *shape) : _x(x),
                                                _y(y),
                                                _rotation(brick_rotation::UP)
{
  if (shape)
    memcpy(_pixels, shape, sizeof(_pixels));
  else
    memset(_pixels, true, sizeof(_pixels));
}

brick::brick(const brick &other) : _x(other._x),
                                   _y(other._y),
                                   _rotation(other._rotation)
{
  memcpy(_pixels, other._pixels, brick::_width * brick::_height);
}

brick &brick::operator=(const brick &other)
{
  _x = other._x;
  _y = other._y;
  memcpy(_pixels, other._pixels, brick::_width * brick::_height);
  return *this;
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
      break;
    case brick_rotation::RIGHT:
      is_active = _pixels[(_height - 1) * _width + y - x * _height];
      break;
    case brick_rotation::DOWN:
      is_active = _pixels[(_width * _height - 1) - x - y * _height];
      break;
    case brick_rotation::LEFT:
      is_active = _pixels[(_height - 1) - y + x * _height];
      break;
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
  switch (_rotation)
  {
  case brick_rotation::UP:
    _rotation = brick_rotation::LEFT;
    break;
  case brick_rotation::RIGHT:
    _rotation = brick_rotation::UP;
    break;
  case brick_rotation::DOWN:
    _rotation = brick_rotation::RIGHT;
    break;
  case brick_rotation::LEFT:
    _rotation = brick_rotation::DOWN;
    break;
  }
}
void brick::rotate_right()
{
  switch (_rotation)
  {
  case brick_rotation::UP:
    _rotation = brick_rotation::RIGHT;
    break;
  case brick_rotation::RIGHT:
    _rotation = brick_rotation::DOWN;
    break;
  case brick_rotation::DOWN:
    _rotation = brick_rotation::LEFT;
    break;
  case brick_rotation::LEFT:
    _rotation = brick_rotation::UP;
    break;
  }
}

const bool brick::_models[_models_count][brick::_height * brick::_width] = {
    {0, 0, 0, 0,
     0, 1, 1, 0,
     0, 1, 1, 0,
     0, 0, 0, 0},
    {0, 0, 1, 0,
     0, 0, 1, 0,
     0, 0, 1, 0,
     0, 0, 1, 0},
    {0, 1, 0, 0,
     0, 1, 1, 0,
     0, 0, 1, 0,
     0, 0, 0, 0},
    {0, 1, 0, 0,
     0, 1, 0, 0,
     0, 1, 1, 0,
     0, 0, 0, 0},
    {0, 0, 1, 0,
     0, 0, 1, 0,
     0, 1, 1, 0,
     0, 0, 0, 0},
    {0, 0, 0, 0,
     0, 0, 1, 0,
     0, 1, 1, 1,
     0, 0, 0, 0}};