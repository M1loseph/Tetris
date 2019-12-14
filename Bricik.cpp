#include "Brick.h"


Brick::Brick(int x, int y, bool shape[16])
{
  m_X = x;
  m_Y = y;
  m_Rotation = 0;
  if (shape)
  {
    for (int i = 0 ; i < 16; i++)
    {
      m_Shape[i] = shape[i];
    }
  }
}

bool Brick::GetPixel(int x, int y, bool* succ) const
{
  return GetPixel(x, y, m_Rotation, succ);
}

bool Brick::GetPixel(int x, int y, int rotation, bool* succ) const
{
  if ( x >= 0 && x < GetWidth() && y >= 0 && y < GetHeight())
  {
    if (succ) (*succ) = true;
    switch (rotation % 4)
    {
      case 0: return m_Shape[x + y * GetHeight()];
      case 1: return m_Shape[(GetHeight() - 1) * GetWidth() + y - x * GetHeight()];
      case 2: return m_Shape[(GetWidth() * GetHeight() - 1) - x - y * GetHeight()];
      case 3: return m_Shape[(GetHeight() - 1) - y + x * GetHeight()];
    }
  }
  if (succ) (*succ) = false;
  return false;
}

int Brick::GetWidth() const {
  return 4;
}
int Brick::GetHeight() const {
  return 4;
}
int Brick::GetX() const {
  return m_X;
}
int Brick::GetY() const {
  return m_Y;
}
int Brick::GetRotation() const {
  return m_Rotation;
}
void Brick::SetX(int newX) {
  m_X = newX;
}
void Brick::SetY(int newY) {
  m_Y = newY;
}
void Brick::SetRotation(int rotation) {
  m_Rotation = rotation;
}
void Brick::ChangeX(int offset){
  m_X += offset;
}
void Brick::ChangeY(int offset){
  m_Y += offset;
}
void Brick::ChangeRotation(int offset){
  m_Rotation += offset;
}
