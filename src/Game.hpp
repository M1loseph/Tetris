#ifndef __GAME_HPP__ 
#define __GAME_HPP__ 

#include "Controller.hpp"
#include "Renderer.hpp"
#include "Brick.hpp"

class Game {
  public:
    Game(Controller* joystick, Renderer* renderer); // must be allocated staticly
    bool Start();

  private:
    Controller* m_Controller;
    Renderer* m_Renderer;
    bool* m_GameMatrix;
    Brick* m_CurrentBrick;
    int m_Width, m_Height;
    bool m_Running;
    int m_Speed;

    void UpdateGame();
    void Render();
    Brick* RandomBrick();
    bool Move(int xOffset, int yOffset, int rotation);
    void CopyToGameMatrix();
    bool GameOver();
    void UpdateMap();
    void EndScreen();
};

#endif // __GAME_HPP__