#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Controller.hpp"
#include "Renderer.hpp"
#include "Brick.hpp"

class game
{
public:
  game(controller &controller, renderer &renderer, size_t update_interval, size_t uset_input_interval); // must be allocated staticly
  void start();

private:
  controller &_controller;
  renderer &_renderer;
  // again -> static cuz dynamic allocation is not the greatest idea
  bool _boards[renderer::_height * renderer::_width];
  brick _current_brick;
  bool _is_running;
  size_t _update_interval;
  size_t _uset_input_interval;

  void update_game();
  void render();
  void random_brick();
  bool move(int x_offset, int y_offset, brick::brick_rotation rotation);
  void copy_to_board();
  bool game_over();
  void update_board();
  // TODO => WYJEBAĆ W PIZDU
  void EndScreen();
};

#endif // __GAME_HPP__