#ifndef VariablesDEF
#define VariablesDEF
#include "Include.h"
#include "Settings.h"

extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_TIMER* FPSTimer;
extern ALLEGRO_TIMER* scoreTimer;

extern Player *player;
extern vector<Ground> groundVector;
extern vector<Ground>::iterator it;
extern Draw* draw;
extern Audio* audio;

extern int resPos;
extern int lastX;
extern int lastY;


extern const int resolutions;
extern int resWidth[];
extern int resHeight[];
extern int gamePos;
#endif