#ifndef __BRICK_HPP__
#define __BRICK_HPP__

class brick
{
public:
  enum class brick_rotation
  {
    UP,
    RIGHT,
    DOWN,
    LEFT
  };

  enum class pixel_info
  {
    TRUE,
    FALSE,
    NOT_FOUND
  };

  // creates square at (0, 0)
  explicit brick();
  explicit brick(int x, int y, const bool *shape);
  explicit brick(const brick &other);

  brick &operator=(const brick &other);

  pixel_info pixel_at(uint8_t x, uint8_t y) const;
  pixel_info pixel_at_if(uint8_t x, uint8_t y, brick_rotation rotation) const;

  int x() const;
  int y() const;
  brick_rotation rotation() const;

  void set_x(int x);
  void set_y(int y);
  void set_rotation(brick_rotation rotation);

  void move(int x_offset, int y_offset);
  void rotate_left();
  void rotate_right();

  static constexpr uint8_t _width = 4U;
  static constexpr uint8_t _height = 4U;

  static constexpr size_t _models_count = 6U;

  static const bool _models[_models_count][brick::_height * brick::_width];

private:
  int _x;
  int _y;
  brick_rotation _rotation;
  bool _pixels[_width * _height];
};

#endif // __BRICK_HPP__