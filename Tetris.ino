#include "Game.h"
#include "Joystick.h"
#include "SerialController.h"

// screen resolution
#define WIDTH   8
#define HEIGHT 32

// screen info
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define SEGMENTS   4
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// joystick pins
#define JOYSTICK_X A4
#define JOYSTICK_Y A5
#define JOYSTICK_B 2


void setup()
{
  randomSeed(analogRead(A2));
  Serial.begin(9600);
}


void loop()
{
  Renderer renderer(WIDTH, HEIGHT, HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, SEGMENTS);
  Joystick joystick( JOYSTICK_X, JOYSTICK_Y, JOYSTICK_B);
  SerialController keyboard('a','d','w','s',' ');
  Game game(&joystick, &renderer);
  game.Start();
}
