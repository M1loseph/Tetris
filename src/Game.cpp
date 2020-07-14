#include "logger.hpp"
#include "game.hpp"

game::game(controller &controller, renderer &renderer, size_t falling_interval, size_t uset_input_interval) : _controller(controller),
                                                                                                              _renderer(renderer),
                                                                                                              _falling_interval(falling_interval),
                                                                                                              _uset_input_interval(uset_input_interval),
                                                                                                              _create_new_brick(true)
{
  memset(_boards, false, sizeof(_boards));
}

void game::start()
{
  SERIAL_PRINTLN("Starting game");
  _create_new_brick = true;
  _renderer.clear();

  greeting_screen();

  unsigned long last_fall_update = millis();
  unsigned long last_uset_input = last_fall_update;

  SERIAL_PRINTLN("Entering loop");
  while (create_brick())
  {
    read_user_input();
    if (millis() - last_uset_input > _uset_input_interval)
    {
      last_uset_input = millis();
      // render only if something has actually changed
      if (process_user_input())
        render();
    }
    if (millis() - last_fall_update > _falling_interval)
    {
      last_fall_update = millis();
      fall();
      render();
    }
  }
  end_screen();
  show_score();
}

bool game::create_brick()
{
  if (_create_new_brick)
  {
    random_brick();
    _create_new_brick = false;
    // if brick cant be in this place, it menas that the hame is over
    if (!move_brick(0, 0))
      return false;
  }
  return true;
}

void game::fall()
{
  // fall ONE STEP down
  if (!move_brick(0, -1))
  {
    copy_brick_to_board();
    delete_full_rows();
  }
}

bool game::process_user_input()
{
  SERIAL_PRINTLN("Processing user input");
  int x_dir = 0;
  if (_controller.left())
    x_dir += 1;
  if (_controller.right())
    x_dir -= 1;

  SERIAL_PRINT("Left: ");
  SERIAL_PRINTLN(_controller.left());
  SERIAL_PRINT("Right: ");
  SERIAL_PRINTLN(_controller.right());
  SERIAL_PRINT("Up: ");
  SERIAL_PRINTLN(_controller.up());
  SERIAL_PRINT("Down: ");
  SERIAL_PRINTLN(_controller.down());
  SERIAL_PRINT("Button: ");
  SERIAL_PRINTLN(_controller.button());

  bool something_changed = false;

  if (x_dir != 0)
    something_changed |= move_brick(x_dir, 0);
  if (_controller.button())
    something_changed |= rotate_brick();

  _controller.reset();
  return something_changed;
}

void game::read_user_input()
{
  SERIAL_PRINTLN("Reading user input");
  _controller.read_input();
}

void game::render()
{
  SERIAL_PRINTLN("Rendering");
  for (size_t y = 0; y < renderer::_height; y++)
    for (size_t x = 0; x < renderer::_width; x++)
      if (_boards[x + y * _renderer._width])
        _renderer.render(x, y);

  _renderer.render(_brick);
  _renderer.show();
}

void game::random_brick()
{
  SERIAL_PRINTLN("Creating random brick");
  constexpr int x = 0;
  constexpr int y = renderer::_height - brick::_height;
  int random_number = random(brick::_models_count);
  _brick = brick(x, y, brick::_models[random_number]);
}

bool game::move_brick(int x_offset, int y_offeset)
{
  SERIAL_PRINTLN("Moving brick");
  for (uint8_t y = 0; y < brick::_height; y++)
    for (uint8_t x = 0; x < brick::_width; x++)
      if (_brick.pixel_at(x, y) == brick::pixel_info::TRUE)
      {
        int new_x = _brick.x() + x + x_offset;
        int new_y = _brick.y() + y + y_offeset;

        if (new_x < 0 || static_cast<size_t>(new_x) >= renderer::_width)
          return false;
        if (new_y < 0 || static_cast<size_t>(new_y) >= renderer::_height)
          return false;
        if (_boards[new_x + new_y * renderer::_width])
          return false;
      }
  _brick.move(x_offset, y_offeset);
  return true;
}

bool game::rotate_brick()
{
  SERIAL_PRINTLN("Rotating brick");
  _brick.rotate_right();

  for (uint8_t y = 0; y < _brick._height; y++)
  {
    for (int8_t x = 0; x < _brick._width; x++)
    {
      if (_brick.pixel_at(x, y) == brick::pixel_info::TRUE)
      {
        // for debugging purposes
        CHECK_IMPLMENTATION(_brick.pixel_at(x, y));
        // if point is out of map or it collides with seomthing from board
        // -> rotate back and return false
        int x_cor = _brick.x() + static_cast<int>(x);
        int y_cor = _brick.y() + static_cast<int>(y);
        int board_index = x_cor + y_cor * renderer::_width;
        if (x_cor < 0 || static_cast<size_t>(x_cor) >= renderer::_width || y_cor < 0 || static_cast<size_t>(y_cor) > renderer::_height || _boards[board_index])
        {
          SERIAL_PRINT("Sopmething went wrong at pixel: (");
          SERIAL_PRINT(x_cor);
          SERIAL_PRINT(',');
          SERIAL_PRINT(y_cor);
          SERIAL_PRINTLN(')');
          _brick.rotate_left();
          return false;
        }
      }
    }
  }
  return true;
}

void game::copy_brick_to_board()
{
  SERIAL_PRINTLN("Copying brick to the board");
  for (int y = 0; y < brick::_height; y++)
    for (int x = 0; x < brick::_width; x++)
      if (_brick.pixel_at(x, y) == brick::pixel_info::TRUE)
      {
        int x_cor = _brick.x() + x;
        int y_cor = _brick.y() + y;
        _boards[x_cor + y_cor * renderer::_width] = true;
      }
  // after this copying we need a new brick
  _create_new_brick = true;
}

void game::delete_full_rows()
{
  SERIAL_PRINTLN("Deleting full rows");
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
  SERIAL_PRINTLN("Greeting user");
  _renderer.render("Hello");
}

// reimplementacja -> zrobić to na zasadzie stringów, nie takich gównianych tablic
void game::end_screen()
{
  SERIAL_PRINTLN("Showing end screen");
  _renderer.render("game over");
}

void game::show_score()
{
  SERIAL_PRINTLN("Showing score");
  _renderer.render("score");
}