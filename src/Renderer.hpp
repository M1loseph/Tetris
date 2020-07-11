#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <MD_MAX72xx.h>
#include "Brick.hpp"

class Renderer {
  public:
    
    Renderer(int width, int height, MD_MAX72XX::moduleType_t moduleType, int dataPin, int clkPin, int csPin, int segments);
    ~Renderer();

    void Clear();
    void Display();
    bool Render(const Brick& brick);
    bool RenderLine(int y, uint8_t hex);
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

#endif // __RENDERER_HPP__