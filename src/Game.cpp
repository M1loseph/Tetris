#include "game.hpp"

#define DEF_SPEED 5
#define USER_UPDATE_RATE 2

game::game(controller &controller, renderer &renderer, size_t falling_interval, size_t uset_input_interval) : _controller(controller),
                                                                                                              _renderer(renderer),
                                                                                                              _falling_interval(falling_interval),
                                                                                                              _uset_input_interval(uset_input_interval),
                                                                                                              _make_new_brick(true)
{
}

void game::start()
{
  _running = true;
  _renderer.clear();

  greeting_screen();
  while (!_controller.button())
    ;

  unsigned long last_fall_update = millis();
  unsigned long last_uset_input = last_fall_update;

  while (_running)
  {
    if (millis() - last_fall_update > _falling_interval)
    {
      last_fall_update = millis();
      fall();
      render();
    }

    if (millis() - last_uset_input > _uset_input_interval)
    {
      last_uset_input = millis();
      // render only if something has actually changed
      if (process_user_input())
        render();
    }
    read_user_inpup();
  }
  end_screen();
  show_score();
}

void game::fall()
{
  if (_make_new_brick)
  {
    delete_full_rows();
    random_brick();
    // if brick cant be in this place, it menas that the hame is over
    if (!move_user_brick(0, 0))
    {
      _running = false;
      return;
    }
  }
  if (!move_user_brick(0, -1))
    copy_brick_to_board();
}

bool game::process_user_input()
{
}

void game::read_user_inpup()
{
}

void game::render()
{
  for (size_t y = 0; y < renderer::_height; y++)
    for (size_t x = 0; x < renderer::_width; x++)
      if (_boards[x + y * _renderer._width])
        _renderer.render(x, y);

  _renderer.render(_current_brick);
  _renderer.show();
}

void game::random_brick()
{
  int y = renderer::_height * 3 / 4;
  int x = 0;
  int random_number = random(brick::_models_count);
  _current_brick = brick(x, y, brick::_models[random_number]);
}

bool game::move_user_brick(int x_offset, int y_offeset)
{
  for (uint8_t y = 0; y < brick::_height; y++)
    for (uint8_t x = 0; x < brick::_width; x++)
      if (_current_brick.pixel_at(x, y) == brick::pixel_info::TRUE)
      {
        int new_x = _current_brick.x() + x + x_offset;
        int new_y = _current_brick.y() + y + y_offeset;

        if (new_x >= renderer::_width || new_x < 0)
          return false;
        if (new_y >= renderer::_height || new_y < 0)
          return false;
        if (_boards[new_x + new_y * renderer::_width])
          return false;
      }
  _current_brick.move(x_offset, y_offeset);
  return true;
}

bool game::rotate_user_brick()
{

}

void game::copy_brick_to_board()
{
  for (int y = 0; y < brick::_height; y++)
    for (int x = 0; x < brick::_width; x++)
      if (_current_brick.pixel_at(x, y) == brick::pixel_info::TRUE)
      {
        int x_cor = _current_brick.x() + x;
        int y_cor = _current_brick.y() + y;
        _boards[x_cor + y_cor * renderer::_width] = true;
      }
  // after this copying we need a new brick
  _make_new_brick = true;
}

void game::delete_full_rows()
{
  for (size_t y = 0; y < renderer::_height; y++)
  {
    bool fullLine = true;
    for (size_t x = 0; x < renderer::_width && fullLine; x++)
    {
      if (!_boards[x + y * renderer::_width])
        fullLine = false;
    }
    if (fullLine)
    {
      for (size_t i = y * renderer::_width; i < (renderer::_height - 1) * renderer::_width; i++)
        _boards[i] = _boards[i + renderer::_width];

      for (size_t i = (renderer::_height - 1) * renderer::_height; i < renderer::_height * renderer::_width; i++)
        _boards[i] = false;
      --y;
    }
  }
}

void game::greeting_screen()
{
}

// reimplementacja -> zrobić to na zasadzie stringów, nie takich gównianych tablic
void game::end_screen()
{
  /*
  _renderer->Clear();
  delay(200);
  const uint8_t letters[72] = {0x7E, 0x81, 0x80, 0x8F, 0x81, 0x81, 0x81, 0x7E, 0x0,
                               0xFF, 0x81, 0x81, 0x81, 0xFF, 0x81, 0x81, 0x81, 0x0,
                               0x81, 0xC3, 0xA5, 0x99, 0x81, 0x81, 0x81, 0x81, 0x0,
                               0xFF, 0x80, 0x80, 0xF8, 0xF8, 0x80, 0x80, 0xFF, 0x0,
                               0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF, 0x0,
                               0x81, 0x81, 0x42, 0x42, 0x24, 0x24, 0x18, 0x18, 0x0,
                               0xFF, 0x80, 0x80, 0xF8, 0xF8, 0x80, 0x80, 0xFF, 0x0,
                               0xFC, 0x84, 0x84, 0xFC, 0xA0, 0x90, 0x88, 0x84, 0x0};
  for (int i = 0; i < m_Height + 72; i++)
  {
    for (int j = 0; j < 72; j++)
    {
      _renderer->RenderLine(i - j, letters[j]);
    }
    _renderer->Display();
    delay(200);
  }*/
  delay(5000);
}

void show_score()
{

}