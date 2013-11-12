#ifndef headerDEF
#define headerDEF

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

//Screen varables
const int WIDTH = 1024; 
const int HEIGHT = 768; 
const int FPS = 60;

//Game variables
const float jumpTime = FPS * 1.2;
const float pointTime = FPS * 0.2;
const int speedScore = 10;
const int startSpeed = 2;

//Player variables
const int pStartX = WIDTH / 8; // player start location in X-axel
const int pStartY = HEIGHT / 2; // player start location in Y-axel
const int pSize = 30; // player size

//ground variables
const int gMax = 5;
const int gPosY1 = (HEIGHT / 10) * 2;
const int gPosY2 = (HEIGHT / 10) * 4;
const int gPosY3 = (HEIGHT / 10) * 6;
const int gPosY4 = (HEIGHT / 10) * 8;

#endif