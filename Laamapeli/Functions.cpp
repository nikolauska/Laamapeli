#include "Header.h"
#include "Player.h"
#include "Ground.h"
#include "Audio.h"
#include "Draw.h"
#include "SimpleIni.h"

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* FPSTimer;
ALLEGRO_TIMER* upTimer;
ALLEGRO_TIMER* downTimer;
ALLEGRO_TIMER* scoreTimer;
ALLEGRO_TIMER* speedTimer;

// Class variables
Player *player;
vector<Ground> groundVector;
Ground* ground;
vector<Ground>::iterator it;
Draw* draw;
Audio* audio;
CSimpleIniA* ini;

void timerInitalize(ALLEGRO_EVENT_QUEUE*);
void timerEvent();
void startTimer(int);

int initialize(){

	//Test allegro object
	if(!al_init())										
		return -1;

	//create our display object
	display = al_create_display(WIDTH, HEIGHT);	

	//test display object
	if(!display)										
		return -1;	

	// Load addons for allegro	
	al_install_keyboard();

	player = new Player();
	draw = new Draw();
	audio = new Audio();
	ini = new CSimpleIniA();

	ini->SetUnicode();
	ini->LoadFile("Data/Config/settings.ini");

	// Create timer 
	FPSTimer = al_create_timer(1.0 / FPS);
	upTimer = al_create_timer(upSpeed);
	downTimer = al_create_timer(downSpeed);
	scoreTimer = al_create_timer(scoreTime);
	speedTimer = al_create_timer(startSpeed);

	event_queue = al_create_event_queue();

	// Register keyboard events
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(FPSTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(upTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(downTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(scoreTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(speedTimer));
	

	// Start timer
	al_start_timer(FPSTimer);

	return 0;
}

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
				audio->jump();
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
										break;
									}
									case(2):{

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
										break;
									}
									case(2):{
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
					audio->loopMenu();

				draw->menu(menuText, menuSelect);
				break;
			}
			case(2):{
				gamePos = 3;

				player->start();
	
				ground = new Ground();
				ground->start();
				groundVector.push_back(*ground);
				delete ground;

				for (int j = 0; j != gMax; j++){
					ground = new Ground();

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
					audio->loopInGame();

				draw->bg();

				// check if player has dropped to bottom
				if (player->getY() + draw->picHeight() >= HEIGHT) {
					gamePos = 4;
					audio->stopLoopInGame();
					audio->death();
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



void startTimer(int timer){
	if(timer == 1){
		al_start_timer(upTimer);
	} else {
		// Start inGame timers
		al_start_timer(scoreTimer);
		al_start_timer(downTimer);
		al_start_timer(speedTimer);
	}
}

/*
*	Beginninng of upTimer object!
*	Here we make the player jump or go down 
*	if player has pressed jump button and is on ground he will start ro rise certain time
*	If player is not on ground and is not going up he will go down
*/

void upTimerEvent(ALLEGRO_EVENT ev){
	if(al_get_timer_started(upTimer)){
		if(ev.timer.source == upTimer) {
			if(al_get_timer_count(upTimer) == upTime){
				al_stop_timer(upTimer);
				al_set_timer_count(upTimer, 0);
			}

			player->moveUp();			
		}
										
	} else {
		if(ev.timer.source == downTimer) {
			if(!player->getGround())
				player->moveDown();			
		}
	}
}

/*
*	Beginninng of scoreTimer object!
*	This is the function that will run when scoretimer has ticked to it's specific time 
*	Here we add points to player and add speed to him/her
*	Speed i update only certain point interval
*/

void scoreTimerEvent(ALLEGRO_EVENT ev) {
	if(ev.timer.source == scoreTimer){
		player->addScore();
		if(al_get_timer_count(scoreTimer) % speedScore == 0)
			player->addSpeed();
	}
}

/*
*	Beginninng of speedTimer object!
*	This is the function that will run if speed timer has ticked to it's specific time
*	Here we update ground position and move out of screen grounds back to screen
*
*/

void speedTimerEvent(){
	if(al_get_timer_started(speedTimer)){
		if(al_get_timer_count(speedTimer) >= (1/player->getSpeed())) {
			for (it = begin(groundVector); it != end(groundVector); it++){
						
				if (it->getX() + 300 <= 0)
					if(it != groundVector.begin())
						it->create(prev(it)->getX(), prev(it)->getY());						
							
				if(it->groundCheck(player->getX(), player->getY()))
					player->setGround(true);
											
				it->move(player->getSpeed());
			}				
		}
	}
}

/*
*	Beginninng of timer object!
*	This function is being run when timer has ticked to specific time
*	example FPS so it's time to draw to screen or score so it's time to add points to player 
*
*/

void timerEvent(ALLEGRO_EVENT ev){

	if(ev.type == ALLEGRO_EVENT_TIMER){
		if(ev.timer.source == FPSTimer)
			redraw = true;			
			
		if (gamePos == 3) {
			upTimerEvent(ev);

			scoreTimerEvent(ev);

			speedTimerEvent();
		}
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

	timerEvent(ev);

	if(displayCloseEvent(ev))
		return true;

	if(keyPressEvent(ev))
		return true;
	
	drawEvent();

	return false;
}

void iniWrite(string section, string key, string defaultValue, string newValue){	
	const char * pVal = ini->GetValue(section.c_str(), key.c_str(), defaultValue.c_str());
	string cppstr(cstr, cstr + min(max_length, strlen(cstr)));
	ini->SetValue(section.c_str(), key.c_str(), newValue.c_str());
}

void iniRead(

/*
*	Beginninng of destroy object!
*	Here we destroy everything from memory
*	This prevents memory leaks (we don't want your PC to run slow)
*	
*/

void destroy(){
	// Destroy all classes from vector
	for (it = groundVector.begin(); it != groundVector.end(); it++){
		it->~Ground();
	}

	// Destroy vector 
	groundVector.erase(groundVector.begin(), groundVector.end());

	al_destroy_event_queue(event_queue);
	al_destroy_timer(FPSTimer);
	al_destroy_timer(upTimer);
	al_destroy_timer(downTimer);
	al_destroy_timer(scoreTimer);
	al_destroy_display(display);

	delete player;
	delete draw;
	delete audio;
	
}