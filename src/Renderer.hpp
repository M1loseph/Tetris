#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <MD_MAX72xx.h>
#include "brick.hpp"

class renderer
{
public:
  renderer(MD_MAX72XX &matrix);

  void init();
  void clear();
  void display();
  void render(const brick &brick);
  bool render_line(int y, uint8_t hex);
  bool render(int x, int y);

  static constexpr size_t _width = 8U;
  static constexpr size_t _height = 8U;

private:
  bool _current_frame[_width * _height];
  bool _old_frame[_width * _height];
  // reference to the external MD_MAX72XX, needs to live longer than Renderer object
  // removed 'new' operatuz cuz its not the greatest idea to use it one microcontroller, right?
  MD_MAX72XX &_matrix;
};

#endif // __RENDERER_HPP__