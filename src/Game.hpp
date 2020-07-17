#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "controller.hpp"
#include "renderer.hpp"
#include "brick.hpp"

// unlike renderer, the game can be played on any rendering device that supports pixel rendering
// it is not limited to 8 pixels in width, it can be any number, but needs to be specified in the static data section
template<typename Renderer>
class game
{
public:
  explicit game(controller &controller, renderer &renderer); // must be allocated staticly
  void start();

  // number of points depends on how many lines you delete at the same time
  static const size_t _points_rules[brick::_height];
  static constexpr size_t _level_change_diff = 10U;
  static constexpr size_t _init_fall_interval = 250U;
  static constexpr size_t _min_fall_interval = 50U;
  static constexpr size_t _speed_delta = 20U;
  static constexpr size_t _boost_speed = _min_fall_interval;

private:
  controller &_controller;
  renderer &_renderer;
  // again -> static cuz dynamic allocation is not the greatest idea
  bool _board[renderer::_height * renderer::_width];
  bool _create_new_brick;

  size_t _current_interval;

  brick _brick;

  size_t _points;
  size_t _level;
  size_t _lines_deleted;

  bool _boost;

private:
  bool create_brick();
  void fall();
  bool process_user_input();
  void read_user_input();
  void render();
  void random_brick();
  bool move_brick(int x_offset, int y_offset);
  bool rotate_brick();
  void copy_brick_to_board();
  void delete_full_rows();
  void greeting_screen();
  void end_screen();
  void show_score();
};

#endif // __GAME_HPP__