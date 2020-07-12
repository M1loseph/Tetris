#include "game.hpp"

#define DEF_SPEED 5
#define USER_UPDATE_RATE 2

game::game(controller &controller, renderer &renderer, size_t update_interval, size_t uset_input_interval) : _controller(controller),
                                                                                                             _renderer(renderer),
                                                                                                             _update_interval(update_interval),
                                                                                                             _uset_input_interval(uset_input_interval)
{
}

void game::start()
{
  _is_running = true;
  _renderer.clear();

  unsigned long lastTime = millis();
  unsigned long delta = ;

  while (!_controller->Button())
    ;
  while (_running)
  {
    if (millis() - lastTime >= delta)
    {
      lastTime = millis();
      update_game();
      render();
    }
  }
  EndScreen();
  delete _current_brick;
  delete _boards;
  _boards = nullptr;
  _current_brick = nullptr;

  return true;
}

void game::update_game()
{
  static unsigned long counter = 0;
  if (!_current_brick)
  {
    update_board();
    _speed = DEF_SPEED;
    _current_brick = random_brick();
    if (!move(0, 0, 0))
    {
      _running = false;
      return;
    }
  }

  if (counter % USER_UPDATE_RATE == 0)
  {
    if (_controller->Right())
      move(-1, 0, 0);
    else if (_controller->Left())
      move(1, 0, 0);
    else if (_controller->ButtonPressed())
      move(0, 0, 1);
    if (_controller->Down() && _speed != 1)
      _speed -= 1;
    if (_controller->Up() && _speed < DEF_SPEED)
      _speed += 1;
  }
  if (counter++ % _speed == 0)
  {
    if (!move(0, -1, 0))
    {
      copy_to_board();
    }
  }
}
void game::render()
{
  for (int y = 0; y < m_Height; y++)
    for (int x = 0; x < m_Width; x++)
      if (_boards[x + y * m_Width])
        _renderer->render(x, y);

  if (_current_brick)
    _renderer->render(*_current_brick);

  _renderer->Display();
}

brick *game::random_brick()
{
  int defHeight = m_Height * 3 / 4;
  int defWidth = 0;
  int brick = random(6);
    return new brick(defWidth, defHeight, model);
    break;
  }
  case 3:
  {
    return new brick(defWidth, defHeight, model);
    break;
  }
  case 4:
  {
    return new brick(defWidth, defHeight, model);
    break;
  }
  case 5:
  {
    return new brick(defWidth, defHeight, model);
    break;
  }
  }
  return nullptr;
}

bool game::move(int xOffset, int yOffeset, int rotation)
{

  if (_current_brick)
  {
    int finalRotation = _current_brick->rotation() + rotation;

    for (int y = 0; y < _current_brick->_height(); y++)
    {
      for (int x = 0; x < _current_brick->_width(); x++)
      {
        if (_current_brick->pixel_at(x, y, finalRotation))
        {
          int newX = _current_brick->x() + x + xOffset;
          int newY = _current_brick->y() + y + yOffeset;

          if (newX >= m_Width || newX < 0)
            return false;
          if (newY >= m_Height || newY < 0)
            return false;
          if (_boards[newX + newY * m_Width])
            return false;
        }
      }
    }
    _current_brick->move_x(xOffset);
    _current_brick->move_y(yOffeset);
    _current_brick->rotate_right(rotation);
    return true;
  }
  return false;
}

void game::copy_to_board()
{
  for (int y = 0; y < _current_brick->_height(); y++)
  {
    for (int x = 0; x < _current_brick->_width(); x++)
    {
      if (_current_brick->pixel_at(x, y))
      {
        int xCor = _current_brick->x() + x;
        int yCor = _current_brick->y() + y;
        _boards[xCor + yCor * m_Width] = true;
      }
    }
  }
  delete _current_brick;
  _current_brick = nullptr;
}

void game::update_board()
{
  for (int y = 0; y < m_Height; y++)
  {
    bool fullLine = true;
    for (int x = 0; x < m_Width && fullLine; x++)
    {
      if (!_boards[x + y * m_Width])
        fullLine = false;
    }
    if (fullLine)
    {
      for (int i = y * m_Width; i < (m_Height - 1) * m_Width; i++)
        _boards[i] = _boards[i + m_Width];

      for (int i = (m_Height - 1) * m_Width; i < m_Height * m_Width; i++)
        _boards[i] = false;
      --y;
    }
  }
}

// reimplementacja -> zrobić to na zasadzie stringów, nie takich gównianych tablic
void game::EndScreen()
{
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
  }
  delay(5000);
}
