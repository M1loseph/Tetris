#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <MD_MAX72xx.h>
#include "renderer.hpp"
#include "brick.hpp"

class renderer
{
public:
  explicit renderer(MD_MAX72XX &matrix);

  void init();
  void clear();
  void show();
  bool render_line(int y, uint8_t hex);
  bool render(int x, int y);
  bool render(const char *string);
  // negative numbers are not yet supported
  void render(int number);

  // since im using MD_MAX72 other widths are currently not supported
  static constexpr uint8_t _width = 8U;
  static constexpr uint8_t _height = 32U;
  static constexpr size_t _rendering_interval = 200;

  static constexpr uint8_t _letter_height = 8U;
  static constexpr uint8_t _letter_width = 8U;

private:
  static constexpr int _no_length = 0;

  uint8_t _current_frame[_height];
  uint8_t _previous_frame[_height];

  // english alphabet contains 26 letters, that souldnt change in the nearest future
  // they are implemented only for 8 pixel wide display
  static const uint8_t _aplhabet[26][_letter_height];
  static const uint8_t _digits[10][_letter_height];

  // reference to the external MD_MAX72XX, needs to live longer than Renderer object
  // removed 'new' operatuz cuz its not the greatest idea to use it one microcontroller
  MD_MAX72XX &_matrix;

private:
  bool is_string_valid(const char *string, size_t length = _no_length);
};

#endif // __RENDERER_HPP__