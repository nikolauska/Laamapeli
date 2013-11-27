#include "Variables.h"

ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* event_queue;

// Class variables
Draw* draw;
Audio* audio;

int WIDTH;
int HEIGHT;
int FPS;
int Volume;
float Pan; 
float upTime;
float upSpeed;
float downSpeed;
float scoreTime;
int speedScore;
int startSpeed;
int resPos;

float tempPan;
int tempFPS;
int tempVolume;

const int resolutions = 10;
int resWidth[resolutions] = {640, 800, 1024, 1280, 1280, 1366, 1600, 1600, 1680, 1920};
int resHeight[resolutions] = {480, 600, 768, 720, 960, 768, 900, 1200, 1050, 1080};
int menuSelect = 1;
int menuText = 1; // 1 = main, 2 = settings, 3 = graphics, 4 = audio
int gamePos = 1; // 1 = menu, 2 = start, 3 = inGame, 4 = end
bool redraw = false;

void timerInitalize(ALLEGRO_EVENT_QUEUE*);
bool timerEvent(ALLEGRO_EVENT);
void startTimer(int);
int initialize();
void destroy();


void iniWrite(string, string, string);


/*
*	Beginninng of display close object!
*	If player happened to close game from top right X
*	then this function will run
*
*/

bool displayCloseEvent(ALLEGRO_EVENT ev){
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
		return true;
	}
	return false;
}

/*
*	Beginninng of keypress event object!
*	This is where program what key has been pressed 
*	Both ingame and menu functions are handled
*
*/

bool keyPressEvent(ALLEGRO_EVENT ev){
	bool temp = false;

	if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
		switch(ev.keyboard.keycode){

			// SPACE button
			case ALLEGRO_KEY_SPACE:{
				audio->jump(Volume, Pan);
				if (player->getGround())
					startTimer(1);
				break;
			}
			// ENTER button
			case ALLEGRO_KEY_ENTER:{
				switch(gamePos){
					case(1):{
						switch(menuText){
							case(1):{ // Main menu
								switch (menuSelect){
									case(1):{
										gamePos = 2;
										break;
									}
									case(2):{
										menuText = 2;
										menuSelect = 0;
										break;
									}
									case(3):{
										temp = true;
										break;
									}
								}
								break;
							}
							case(2):{ // Settings menu
								switch (menuSelect){
									case(1):{
										menuText = 3;
										menuSelect = 0;
										break;
									}
									case(2):{
										menuText = 4;
										menuSelect = 0;
										break;
									}
									case(3):{
										menuText = 1;
										menuSelect = 0;
										break;
									}
								}
								break;
							}
							case(3):{ // Graphics menu
								switch (menuSelect){
									case(1):{
										iniWrite("Display", "Width", to_string(resWidth[resPos]));
										iniWrite("Display", "Height", to_string(resHeight[resPos]));
										destroy();
										initialize();
										break;
									}
									case(2):{
										iniWrite("Display", "FPS", to_string(tempFPS));
										destroy();
										initialize();
										break;
									}
									case(3):{
										menuText = 2;
										menuSelect = 0;
										break;
									}
								}
								break;
							}
							case(4):{ // Audio menu
								switch (menuSelect){
									case(1):{
										iniWrite("Audio", "Volume", to_string(tempVolume));
										destroy();
										initialize();
										break;
									}
									case(2):{
										iniWrite("Audio", "Pan", to_string(tempPan));
										destroy();
										initialize();
										break;
									}
									case(3):{
										menuText = 2;
										menuSelect = 0;
										break;
									}
								}
								break;
							}
						}
						break;
					}
					case(4):{
						gamePos = 1;
						break;
					}
				}
			}
			// DOWN button
			case ALLEGRO_KEY_DOWN:{
				if (gamePos == 1) {
					if(menuSelect != 3)
						menuSelect += 1;
				}						
				break;
			}

			// UP button
			case ALLEGRO_KEY_UP:{
				if (gamePos == 1) {
					if(menuSelect != 1)
						menuSelect -= 1;
				}						
				break;
			}
			case ALLEGRO_KEY_LEFT:{
				if(gamePos == 1) {
					switch(menuText){
						case(3):{ // Graphics
							switch(menuSelect){
								case(1):{
									if(resPos != 0)
										resPos -= 1;
									break;
								}
								case(2):{
									if(tempFPS != 5)
										tempFPS -= 5;
									break;
								}
							}
							break;
						}
						case(4):{ // Audio
							switch(menuSelect){
								case(1):{
									if(tempVolume != 0)
										tempVolume -= 1;
									break;
								}
								case(2):{
									if(tempPan > -1)
										tempPan -= 0.1;
									else
										tempPan = -1;
									break;
								}
							}
							break;
						}
					}
				}					
				break;
			}
			case ALLEGRO_KEY_RIGHT:{
				if(gamePos == 1) {
					switch(menuText){
						case(3):{ // Graphics
							switch(menuSelect){
								case(1):{
									if(resPos != resolutions - 1)
										resPos += 1;
									break;
								}
								case(2):{
									tempFPS += 5;
									break;
								}
							}
							break;
						}
						case(4):{ // Audio
							switch(menuSelect){
								case(1):{
									if(tempVolume != 100)
										tempVolume += 1;
									break;
								}
								case(2):{
									if(tempPan < 1)
										tempPan += 0.1;
									else
										tempPan = 1;
									break;
								}
							}
							break;
						}
					}						
					break;
				}
			}	
		}
	}
	return temp;
}

/*
*	Beginninng of draw object!
*	This is where program does all the drawing to screen stuff 
*	This is also where we check if player is dead and start/stop audio
*
*/

void drawEvent(){
	if(redraw && al_is_event_queue_empty(event_queue)) {
		redraw = false;

		// Menu draw
		switch(gamePos){
			case(1):{
				// Menu music
				if(!audio->isMenuPlaying())
					audio->loopMenu(Volume, Pan);

				draw->menu(menuText, menuSelect, resWidth[resPos], resHeight[resPos], tempFPS, tempVolume, tempPan);
				break;
			}
			case(2):{
				gamePos = 3;

				player->start(startSpeed);
	
				ground = new Ground(HEIGHT);
				ground->start(WIDTH, HEIGHT, draw->picHeight());
				groundVector.push_back(*ground);
				delete ground;

				for (int j = 1; j != int((WIDTH / 300) + 3); j++){
					ground = new Ground(HEIGHT);

					groundVector.push_back(*ground);
					delete ground;
				}

				for (it = groundVector.begin() + 1; it != groundVector.end(); it++){
					it->create(prev(it)->getX(), prev(it)->getY());
				}

				startTimer(0);
				break;
			}
			case(3):{				
				// Ingame music
				if(audio->isMenuPlaying())
					audio->stopLoopMenu();

				if(!audio->isInGamePlaying())
					audio->loopInGame(Volume, Pan);

				draw->bg();

				// check if player has dropped to bottom
				if (player->getY() + draw->picHeight() >= HEIGHT) {
					gamePos = 4;
					audio->stopLoopInGame();
					audio->death(Volume, Pan);
				};		
				
				// Update all ground positions and draw them to backbuffer
				player->setGround(false);
		
				// Draw grounds to screen
				for (it = groundVector.begin(); it != groundVector.end(); it++){											
					draw->ground(it->getX(), it->getY());
				}

				// draw player and text to backbuffer
				draw->player(player->getX(), player->getY());
				draw->gameText(player->getScore(), player->getSpeed());
				break;
			}
			case(4):{
				// Draw end text to backbuffer
				draw->endText(player->getScore());
				break;
			}
		}

		// Flip backbuffer to screen
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}		
}


/*
*	Beginninng of events object!
*	This is where program handles all event related stuff
*	This includes timers, closing display, keypress, drawings
*
*/


bool Events(){
	ALLEGRO_EVENT ev;
	al_wait_for_event(event_queue, &ev);

	if(timerEvent(ev))
		redraw = true;

	if(displayCloseEvent(ev))
		return true;

	if(keyPressEvent(ev))
		return true;
	
	drawEvent();

	return false;
}