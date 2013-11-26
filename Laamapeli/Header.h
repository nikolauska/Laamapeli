#ifndef headerDEF
#define headerDEF

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

//Screen variables
const int WIDTH = 1280; // Screen width
const int HEIGHT = 720; // Screen height	
const int FPS = 120; // Frames-per-second
const bool fullScreen = true;
const int volume = 100;

//Menu Variables
const int menuPos1X = WIDTH / 2;
const int menuPos1Y = (HEIGHT / 8) * 3;
const int menuPos2X = WIDTH / 2;
const int menuPos2Y = (HEIGHT / 8) * 4;
const int menuPos3X = WIDTH / 2;
const int menuPos3Y = (HEIGHT / 8) * 5;

//Game variables
const float upTime = 1 + HEIGHT * 0.1; // How long player goes up after presing space
const float upSpeed = 0.01; // at which speed player is going up
const float downSpeed = 0.5; // at which speed player is going down
const float scoreTime = 0.2; // How often points are given
const int speedScore = 100; // How often speed will rise
const int startSpeed = 2; // Starting speed

//Player variables
const int pStartX = WIDTH / 8; // player start location in X-axel
const int pStartY = HEIGHT / 2; // player start location in Y-axel
const int pSize = 30; // player size
const int pMove = 6;

//ground variables
const int gMax = (WIDTH / 300) + 3; // How many different platforms are created
const int gPosY1 = (HEIGHT / 10) * 2; // Ground Y position 1
const int gPosY2 = (HEIGHT / 10) * 4; // Ground Y position 2
const int gPosY3 = (HEIGHT / 10) * 6; // Ground Y position 3
const int gPosY4 = (HEIGHT / 10) * 8; // Ground Y position 4

// Local variables
int menuSelect = 1;
int menuText = 1; // 1 = main, 2 = settings, 3 = graphics, 4 = audio
int gamePos = 1; // 1 = menu, 2 = start, 3 = inGame, 4 = end
bool redraw = false;

#endif