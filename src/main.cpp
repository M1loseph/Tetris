#include "Game.hpp"
#include "Joystick.hpp"
#include "serial_controller.hpp"

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
  // KURWA TODO
  // NIE PAMIĘTAM, JAK WYGLĄDAŁ KONSTRUKTORA XDDDDDDDDDDD
  MD_MAX72XX matrix();
  renderer renderer(WIDTH, HEIGHT, HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, SEGMENTS);
  joystick joystick( JOYSTICK_X, JOYSTICK_Y, JOYSTICK_B);
  serial_controller keyboard('a','d','w','s',' ');
  game game(&joystick, &renderer);
  game.start();
}
