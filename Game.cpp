#include "Game.h"

#define DEF_SPEED 5
#define TICK_RATE 30.0f

Game::Game(Controller* controller, Renderer* renderer)
{
  m_CurrentBrick = nullptr;
  m_Controller = controller;
  m_Renderer = renderer;
  m_GameMatrix = nullptr;


  m_Width = 0;
  m_Height = 0;
  m_Speed = DEF_SPEED;
}
bool Game::Start()
{
  if (!m_Controller || !m_Renderer) return false;

  m_Running = true;
  m_Width = m_Renderer->GetWidth();
  m_Height = m_Renderer->GetHeight();

  m_GameMatrix = new bool[m_Width * m_Height];
  for (int i = 0; i < m_Width * m_Height; i++)
    m_GameMatrix[i] = false;
  m_Renderer->Clear();

  unsigned long lastTime = millis();
  unsigned long delta = 1000.0f / TICK_RATE;

  while (m_Running)
  {
    if (millis() - lastTime >= delta)
    {
      lastTime = millis();
      UpdateGame();
      Render();
    }
  }
  EndScreen();
  delete m_CurrentBrick;
  delete m_GameMatrix;
  m_GameMatrix = nullptr;
  m_CurrentBrick = nullptr;

  return true;
}


void Game::UpdateGame()
{
  static unsigned long counter = 0;
  if (!m_CurrentBrick)
  {
    UpdateMap();
    m_Speed = DEF_SPEED;
    m_CurrentBrick = RandomBrick();
    if (!Move(0, 0, 0))
    {
      m_Running = false;
      return;
    }
  }


  if (m_Controller->RightPressed()) Move(1, 0, 0);
  else if (m_Controller->LeftPressed()) Move(-1, 0, 0);
  else if (m_Controller->ButtonPressed()) Move(0, 0, 1);
  if (m_Controller->Down() && m_Speed != 1 ) m_Speed -= 1;
  if (m_Controller->Up() && m_Speed < DEF_SPEED ) m_Speed += 1;

  if ( counter++ % m_Speed == 0)
  {
    if (!Move(0, -1, 0))
    {
      CopyToGameMatrix();
    }
  }
}
void Game::Render()
{
  for (int y = 0; y < m_Height; y++)
    for (int x = 0; x <  m_Width; x++)
      if (m_GameMatrix[x + y * m_Width]) m_Renderer->Render(x, y);

  if (m_CurrentBrick)
    m_Renderer->Render(*m_CurrentBrick);

  m_Renderer->Display();
}



Brick* Game::RandomBrick()
{
  int defHeight = m_Height * 3 / 4;
  int defWidth = 0;
  int brick = random(6);
  switch (brick)
  {
    case 0 :
      {
        bool model[16] =  { 0, 0, 0, 0,
                            0, 1, 1, 0,
                            0, 1, 1, 0,
                            0, 0, 0, 0,
                          };
        return new Brick(defWidth, defHeight, model);
        break;
      }
    case 1 :
      {
        bool model[16] = { 0, 0, 1, 0,
                           0, 0, 1, 0,
                           0, 0, 1, 0,
                           0, 0, 1, 0,
                         };
        return new Brick(defWidth, defHeight, model);
        break;
      }
    case 2 :
      {
        bool model[16] = { 0, 1, 0, 0,
                           0, 1, 1, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 0,
                         };
        return new Brick(defWidth, defHeight, model);
        break;
      }
    case 3 :
      {
        bool model[16] = { 0, 1, 0, 0,
                           0, 1, 0, 0,
                           0, 1, 1, 0,
                           0, 0, 0, 0,
                         };
        return new Brick(defWidth, defHeight, model);
        break;
      }
    case 4 :
      {
        bool model[16] = { 0, 0, 1, 0,
                           0, 0, 1, 0,
                           0, 1, 1, 0,
                           0, 0, 0, 0,
                         };
        return new Brick(defWidth, defHeight, model);
        break;
      }
    case 5 :
      {
        bool model[16] = { 0, 0, 0, 0,
                           0, 0, 1, 0,
                           0, 1, 1, 1,
                           0, 0, 0, 0,
                         };
        return new Brick(defWidth, defHeight, model);
        break;
      }
  }
  return nullptr;
}



bool Game::Move(int xOffset, int yOffeset, int rotation) {

  if (m_CurrentBrick)
  {
    int finalRotation = m_CurrentBrick->GetRotation() + rotation;

    for (int y = 0; y < m_CurrentBrick->GetHeight(); y++)
    {
      for (int x = 0; x < m_CurrentBrick->GetWidth(); x++)
      {
        if (m_CurrentBrick->GetPixel(x, y, finalRotation))
        {
          int newX = m_CurrentBrick->GetX() + x + xOffset;
          int newY = m_CurrentBrick->GetY() + y + yOffeset;

          if (newX >= m_Width || newX < 0) return false;
          if (newY >= m_Height || newY < 0) return false;
          if (m_GameMatrix[newX + newY * m_Width]) return false;
        }
      }
    }
    m_CurrentBrick->ChangeX(xOffset);
    m_CurrentBrick->ChangeY(yOffeset);
    m_CurrentBrick->ChangeRotation(rotation);
    return true;
  }
  return false;
}


void Game::CopyToGameMatrix()
{
  for (int y = 0; y < m_CurrentBrick->GetHeight(); y++)
  {
    for (int x = 0; x < m_CurrentBrick->GetWidth(); x++)
    {
      if (m_CurrentBrick->GetPixel(x, y))
      {
        int xCor = m_CurrentBrick->GetX() + x;
        int yCor = m_CurrentBrick->GetY() + y;
        m_GameMatrix[xCor + yCor * m_Width] = true;
      }
    }
  }
  delete m_CurrentBrick;
  m_CurrentBrick = nullptr;
}

void Game::UpdateMap() {
  for (int y = 0; y < m_Height; y++)
  {
    bool fullLine = true;
    for (int x = 0; x < m_Width && fullLine; x++)
    {
      if (!m_GameMatrix[ x + y * m_Width]) fullLine = false;
    }
    if (fullLine)
    {
      for (int i = y * m_Width; i < (m_Height - 1)*m_Width; i++)
        m_GameMatrix[i] = m_GameMatrix[i + m_Width];

      for (int i = (m_Height - 1) * m_Width; i < m_Height * m_Width; i++)
        m_GameMatrix[i] = false;
      --y;
    }
  }
}


void Game::EndScreen()
{
  m_Renderer->Clear();
  delay(200);
  const uint8_t letters[72] = { 0x7E, 0x81, 0x80, 0x8F, 0x81, 0x81, 0x81, 0x7E, 0x0,
                                0xFF, 0x81, 0x81, 0x81, 0xFF, 0x81, 0x81, 0x81, 0x0,
                                0x81, 0xC3, 0xA5, 0x99, 0x81, 0x81, 0x81, 0x81, 0x0,
                                0xFF, 0x80, 0x80, 0xF8, 0xF8, 0x80, 0x80, 0xFF, 0x0,
                                0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF, 0x0,
                                0x81, 0x81, 0x42, 0x42, 0x24, 0x24, 0x18, 0x18, 0x0,
                                0xFF, 0x80, 0x80, 0xF8, 0xF8, 0x80, 0x80, 0xFF, 0x0,
                                0xFC, 0x84, 0x84, 0xFC, 0xA0, 0x90, 0x88, 0x84, 0x0
                              };
  for (int i = 0; i < m_Height + 72; i++)
  {
    for (int j = 0; j < 72; j++)
    {
      m_Renderer->RenderLine(i - j, letters[j]);
    }
    delay(200);
  }
  delay(5000);
}
