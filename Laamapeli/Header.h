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

const int resolutions = 10;
int resWidth[resolutions] = {640, 800, 1024, 1280, 1280, 1366, 1600, 1600, 1680, 1920};
int resHeight[resolutions] = {480, 600, 768, 720, 960, 768, 900, 1200, 1050, 1080};
int menuSelect = 1;
int menuText = 1; // 1 = main, 2 = settings, 3 = graphics, 4 = audio
int gamePos = 1; // 1 = menu, 2 = start, 3 = inGame, 4 = end
bool redraw = false;

#endif