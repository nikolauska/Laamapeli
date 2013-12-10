#ifndef VariablesDEF
#define VariablesDEF
#include "Include.h"

extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_TIMER* FPSTimer;
extern ALLEGRO_TIMER* upTimer;
extern ALLEGRO_TIMER* downTimer;
extern ALLEGRO_TIMER* scoreTimer;
extern ALLEGRO_TIMER* speedTimer;

extern Player *player;
extern vector<Ground> groundVector;
extern Ground* ground;
extern vector<Ground>::iterator it;
extern Draw* draw;
extern Audio* audio;

extern int WIDTH;
extern int HEIGHT;
extern int FPS;
extern int Volume;
extern float Pan; 
extern float upTime;
extern float upSpeed;
extern float downSpeed;
extern float scoreTime;
extern int speedScore;
extern int startSpeed;
extern int resPos;
extern int lastX;
extern int lastY;

extern float tempPan;
extern int tempFPS;
extern int tempVolume;

extern const int resolutions;
extern int resWidth[];
extern int resHeight[];
extern int gamePos;
extern string folder;
#endif