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
#include <string.h>
//#include <iterator>
using namespace std;

//Screen variables
const int WIDTH = 1280; // Screen width
const int HEIGHT = 720; // Screen height	
const int FPS = 120; // Frames-per-second
const bool fullScreen = true;

//Menu Variables
const int menuSpeed = FPS / 20;
const int menuPlayGamePosX = WIDTH / 2;
const int menuPlayGamePosY = (HEIGHT / 8) * 3;
const int menuSettingsPosX = WIDTH / 2;
const int menuSettingsPosY = (HEIGHT / 8) * 4;
const int menuExitPosX = WIDTH / 2;
const int menuExitPosY = (HEIGHT / 8) * 5;

//Game variables
const float upTime = 1 + HEIGHT * 0.1; // How long player goes up after presing space
const float upSpeed = 0.01; // at which speed player is going up
const float downSpeed = 0.5; // at which speed player is going down
const float scoreTime = 0.1; // How often points are given
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

#endif