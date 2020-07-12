#include <Arduino.h>
#include "renderer.hpp"

renderer::renderer(MD_MAX72XX &matrix) : _matrix(matrix)
{
}

void renderer::init()
{
  _matrix.begin();
  _matrix.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  _matrix.clear();
}

void renderer::show()
{
  for (int y = 0; y < _height; y++)
    for (int x = 0; x < _width; x++)
    {
      int index = x + y * _width;
      if (_old_frame[index] != _current_frame[index])
        _matrix.setPoint(x, y, _current_frame[index]);
      _old_frame[index] = _current_frame[index];
      _current_frame[index] = false;
    }
}

void renderer::render(const brick &brick)
{
  for (int y = 0; y < brick._height; y++)
    for (int x = 0; x < brick._width; x++)
      if (brick.pixel_at(x, y) == brick::pixel_info::TRUE)
        render(brick.x() + x, brick.y() + y);
}

bool renderer::render(int x, int y)
{
  if (x >= 0 && x < _width && y >= 0 && y < _height)
  {
    _current_frame[x + y * _width] = true;
    return true;
  }
  return false;
}

void renderer::clear()
{
  _matrix.clear();
}

bool renderer::render_line(int y, uint8_t hex)
{
  if (y < 0 || y >= _height)
    return false;
  for (int x = 0; x < 8; x++)
    _current_frame[x + y * _width] = (hex >> x) & 0x01;
  return true;
}
