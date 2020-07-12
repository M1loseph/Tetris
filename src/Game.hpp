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

private:
  controller &_controller;
  renderer &_renderer;
  // again -> static cuz dynamic allocation is not the greatest idea
  bool _boards[renderer::_height * renderer::_width];
  brick _current_brick;
  bool _running;
  size_t _falling_interval;
  size_t _uset_input_interval;
  bool _make_new_brick;

  void fall();
  bool process_user_input();
  void read_user_input();
  void render();
  void random_brick();
  bool move_brick(int x_offset, int y_offset);
  bool rotate_brick();
  void copy_brick_to_board();
  void delete_full_rows();
  // TODO => WYJEBAĆ W PIZDU
  void greeting_screen();
  void end_screen();
  void show_score();
};

#endif // __GAME_HPP__