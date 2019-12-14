#pragma once
#include <MD_MAX72xx.h>
#include "Brick.h"

class Renderer {
  public:
    
    Renderer(int width, int height, MD_MAX72XX::moduleType_t moduleType, int dataPin, int clkPin, int csPin, int segments);
    ~Renderer();

    void Clear();
    void Display();
    bool Render(const Brick& brick);
    bool Render(int x, int y);
    int GetWidth();
    int GetHeight();

  private:

    int m_Width;
    int m_Height;
    bool* m_CurrentFrame;
    bool* m_OldFrame;
    MD_MAX72XX* m_Matrix;
};
