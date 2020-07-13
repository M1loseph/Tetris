#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <MD_MAX72xx.h>
#include "brick.hpp"

class renderer
{
public:
  explicit renderer(MD_MAX72XX &matrix);

  void init();
  void clear();
  void show();
  void render(const brick &brick);
  bool render_line(int y, uint8_t hex);
  bool render(int x, int y);
  bool render(const char *string);
  // negative numbers are not yet supported
  void render(size_t number);

  static constexpr size_t _width = 8U;
  static constexpr size_t _height = 32U;
  static constexpr size_t _rendering_interval = 200;

  static constexpr size_t _letter_height = 8U;
  static constexpr size_t _letter_width = 8U;

private:
  bool _current_frame[_width * _height];
  bool _previous_frame[_width * _height];

  // english alphabet contains 26 letters, that souldnt change in the nearest future
  // they are implemented only for 8 pixel wide display
  static const uint8_t _aplhabet[26][_letter_height];
  static const uint8_t _digits[10][_letter_height];

  // reference to the external MD_MAX72XX, needs to live longer than Renderer object
  // removed 'new' operatuz cuz its not the greatest idea to use it one microcontroller
  MD_MAX72XX &_matrix;
};


#endif // __RENDERER_HPP__