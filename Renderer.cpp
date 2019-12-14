#include <Arduino.h>
#include "Renderer.h"

// Constructors


Renderer::Renderer(int width, int height, MD_MAX72XX::moduleType_t moduleType, int dataPin, int clkPin, int csPin, int segments)
{
  m_Width = width;
  m_Height = height;
  m_CurrentFrame = new bool[width * height]; // HANDLE THE POSSIBLE ERROR
  m_OldFrame = new bool[width * height];
  for (int  i = 0; i < width * height; i++)
    m_CurrentFrame[i] = m_OldFrame[i] = false;

  m_Matrix = new MD_MAX72XX(moduleType, dataPin, clkPin, csPin, segments);

  // initializing the screen
  m_Matrix->begin();
  m_Matrix->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  m_Matrix->clear();
}


Renderer::~Renderer()
{
  delete m_CurrentFrame;
  delete m_OldFrame;
}


// Interface


void Renderer::Display()
{
  for (int y = 0; y < m_Height; y++)
  {
    for (int x = 0; x < m_Width; x++)
    {
      int index = x + y * m_Width;
      if (m_OldFrame[index] != m_CurrentFrame[index])
        m_Matrix->setPoint(x, y, m_CurrentFrame[index]);
      m_OldFrame[x + y * m_Width] = m_CurrentFrame[index];
      m_CurrentFrame[index] = false;
    }
  }
}


bool Renderer::Render(const Brick& brick)
{
  bool succ = true;
  for (int y = 0; y < brick.GetHeight(); y++)
  {
    for (int x = 0; x < brick.GetWidth(); x++)
    {
      if (brick.GetPixel(x, y))
      {
        if (!Render(brick.GetX() + x, brick.GetY() + y)) succ = false;
      }
    }
  }
  return succ;
}


bool Renderer::Render(int x, int y)
{
  if ( x >= 0 && x < m_Width && y >= 0 && y < m_Height)
  {
    m_CurrentFrame[x + y * m_Width] = true;
    return true;
  }
  return false;
}


void Renderer::Clear()
{
  m_Matrix->clear();
}


int Renderer::GetWidth() {
  return m_Width;
}
int Renderer::GetHeight() {
  return m_Height;
}
