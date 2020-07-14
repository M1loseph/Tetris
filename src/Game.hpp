#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "controller.hpp"
#include "renderer.hpp"
#include "brick.hpp"

class game
{
public:
  explicit game(controller &controller, renderer &renderer, size_t falling_interval, size_t uset_input_interval); // must be allocated staticly
  void start();

  static const size_t _points_rules[brick::_height];
  static constexpr size_t _level_change_diff = 10U;

private:
  controller &_controller;
  renderer &_renderer;
  // again -> static cuz dynamic allocation is not the greatest idea
  bool _board[renderer::_height * renderer::_width];
  bool _create_new_brick;

  brick _brick;

  size_t _falling_interval;
  size_t _uset_input_interval;

  size_t _points;
  size_t _level;
  size_t _lines_deleted;


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