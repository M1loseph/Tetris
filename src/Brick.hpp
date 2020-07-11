#ifndef __BRICK_HPP__
#define __BRICK_HPP__

class Brick {
  public:

    Brick(int x, int y, bool shape[16]);

    bool GetPixel(int x, int y, bool* succ = nullptr) const;
    bool GetPixel(int x, int y, int rotation, bool* succ = nullptr) const;
    
    int GetWidth() const;
    int GetHeight() const;
    
    int GetX() const;
    int GetY() const;
    int GetRotation() const;
    
    void SetX(int newX);
    void SetY(int newY);
    void SetRotation(int rotation);
    
    void ChangeX(int offset);
    void ChangeY(int offset);
    void ChangeRotation(int offset);


  private:

    int m_X, m_Y;
    int m_Rotation;
    // rotation % 4 = 0 -> 0
    // rotation % 4 = 1 -> 90
    // rotation % 4 = 2 -> 180
    // rotation % 4 = 3 -> 270
    bool m_Shape[16];
};

#endif // __BRICK_HPP__