#include "game.hpp"
#include "Joystick.hpp"
#include "serial_controller.hpp"

// screen info
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define SEGMENTS   4
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// joystick pins
uint8_t JOYSTICK_X = A4;
uint8_t JOYSTICK_Y = A5;
uint8_t JOYSTICK_B = 2;


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
  renderer renderer(matrix);
  joystick joystick( JOYSTICK_X, JOYSTICK_Y, JOYSTICK_B);
  serial_controller keyboard('a','d','w','s',' ');
  game game(joystick, renderer);
  game.start();
}
