#include "Header.h"
#include "Player.h"
#include "Ground.h"
#include "Audio.h"
#include "Draw.h"
#include "Menu.h"

/*
*	Beginninng of global variables!
*	Here are the variables for every object in this file
*	it includes allegro object, class objects and also objects that will come later
*	
*/

// Local variables
int tempJumpTime = 0;
int tempPointTime = 0;
int tempScore = 0;
int menuSelect = 1;
bool isGameOver = false;
bool redraw = false;
bool start = true;
bool menuBool = false;
bool settingsBool = false;

//Allegro variables
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *FPSTimer = NULL;
ALLEGRO_TIMER *upTimer = NULL;
ALLEGRO_TIMER *downTimer = NULL;
ALLEGRO_TIMER *scoreTimer = NULL;
ALLEGRO_TIMER *speedTimer = NULL;
ALLEGRO_DISPLAY *display = NULL;

// Class variables
Player *player = NULL;
vector<Ground> groundVector;
Ground *ground;
vector<Ground>::reverse_iterator it;
vector<Ground>::reverse_iterator tempIt;
Draw *draw = NULL;
Audio *audio = NULL;
Menu *menu = NULL;


/*
*	Beginninng of initialize object!
*	Here we initialize all allegro and class objects
*	This function will return error if that happens
*	
*/

int initialize(){
	//Test allegro object
	if(!al_init())										
		return -1;

	//create our display object
	display = al_create_display(WIDTH, HEIGHT);	

	//test display object
	if(!display)										
		return -1;


	// initalize player and ground class
	player = new Player();
	draw =  new Draw();
	audio = new Audio();
	menu = new Menu();

	// Load addons for allegro	
	al_install_keyboard();

	// Create timer 
	event_queue = al_create_event_queue();
	FPSTimer = al_create_timer(1.0 / FPS);
	upTimer = al_create_timer(upSpeed);
	downTimer = al_create_timer(downSpeed);
	scoreTimer = al_create_timer(scoreTime);
	speedTimer = al_create_timer(startSpeed);

	// Register keyboard events
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(FPSTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(upTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(downTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(scoreTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(speedTimer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	return 0;
}


/*
*	Beginninng of groundInitialize object!
*	Here we create ground before player can see it
*	This is done so that ground won't appear from nowhere
*	
*/

void groundInitialize() {
	ground = new Ground();
	ground->start();
	groundVector.push_back(*ground);
	delete ground;

	for (int j = 0; j != gMax; j++){
		ground = new Ground();

		groundVector.push_back(*ground);
		delete ground;
	}

	for (it = groundVector.rbegin() + 1; it != groundVector.rend(); it++){
		it->create((it - 1)->getX(), (it - 1)->getY());
	}

	// Start timers
	al_start_timer(FPSTimer);
}

/*
*	Beginninng of destroy object!
*	Here we destroy everything from memory
*	This prevents memory leaks (we don't want your PC to run slow)
*	
*/

void destroy(){
	// Destroy all classes from vector
	for (it = groundVector.rbegin(); it != groundVector.rend(); it++){
		it->~Ground();
	}

	// Destroy vector 
	groundVector.erase(groundVector.begin(), groundVector.end());

	// Destroy allegro objects
	al_destroy_event_queue(event_queue);
	al_destroy_timer(FPSTimer);
	al_destroy_timer(upTimer);
	al_destroy_timer(downTimer);
	al_destroy_timer(scoreTimer);
	al_destroy_display(display);
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
	if(ev.timer.source == scoreTimer)
		player->addScore();
		if(al_get_timer_count(scoreTimer) % speedScore == 0)
			player->addSpeed();
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
			for (it = groundVector.rbegin(); it != groundVector.rend(); it++){
						
				if (it->getX() + 300 <= 0)
					if(it != groundVector.rbegin())
						it->create((it - 1)->getX(), (it - 1)->getY());
							
				if((groundVector.rbegin() + 2)->groundCheck(player->getX(), player->getY()))
					player->setGround(true);
											
				it->move(player->getSpeed());
			}

			it = groundVector.rend();
			int tempX = it->getX();
			int tempY = it->getY();

			it = groundVector.rbegin();
			if (it->getX() + 300 <= 0){
				it->create(tempX, tempY);
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
			
		if (!isGameOver && !menuBool) {
			upTimerEvent(ev);

			scoreTimerEvent(ev);

			speedTimerEvent();
		}
	}
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
			// ESC button
			case ALLEGRO_KEY_ESCAPE:{
				temp = true;
				break;
			}
			// SPACE button
			case ALLEGRO_KEY_SPACE:{
				audio->jump();
				if (player->getGround())
					al_start_timer(upTimer);
				break;
			}
			// ENTER button
			case ALLEGRO_KEY_ENTER:{
				if(!settingsBool){
					switch (menuSelect){
						case(1):{
							menuBool = false;
							break;
						}
						case(2):{
							settingsBool = true;
							menu->setAnimState(true);
							break;
						}
						case(3):{
							temp = true;
							break;
						}
					}
				} else {
					switch(menuSelect){
						case(1):{
							menuBool = false;
							break;
						}
						case(2):{
							settingsBool = true;
							break;
						}
						case(3):{
							settingsBool = false;
							menu->setAnimState(true);
							break;
						}
					}
					break;
				}
				// DOWN button
				case ALLEGRO_KEY_DOWN:{
					if (menuBool) {
						if(menuSelect != 3)
							menuSelect += 1;
					}						
					break;
				}
				// UP button
				case ALLEGRO_KEY_UP:{
					if (menuBool) {
						if(menuSelect != 1)
							menuSelect -= 1;
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
		if (menuBool) {
			// Menu music
			if(audio->isInGamePlaying())
				audio->stopLoopInGame();

			if(!audio->isMenuPlaying())
				audio->loopMenu();

			// Settings
			if(settingsBool){
				menu->animateUp();
				draw->mainMenu(menuSelect, menu->getPlayY(), menu->getSettingsY(), menu->getQuitY());
			} else {
				menu->animateDown();
				draw->mainMenu(menuSelect, menu->getPlayY(), menu->getSettingsY(), menu->getQuitY());
			}
		} 

		// Starting game
		if (!menuBool && start) {
			start = false;

			// Ingame music
			if(audio->isMenuPlaying())
				audio->stopLoopMenu();

			if(!audio->isInGamePlaying())
				audio->loopInGame();
		
			// set player to start position
			player->start();

			// draw player, ground and text to backbuffer
			draw->player(player->getX(), player->getY());

			// Start inGame timers
			al_start_timer(scoreTimer);
			al_start_timer(downTimer);
			al_start_timer(speedTimer);
		}

		// Draw backround first so it's behind
		if (!isGameOver && !menuBool) {	
			draw->bg();

		// check if player has dropped to bottom
		if (player->getY() + draw->picHeight() >= HEIGHT) {
			isGameOver = true;
			audio->stopLoopInGame();
			audio->death();
		};		
				
		// Update all ground positions and draw them to backbuffer
		player->setGround(false);
		
		// Draw grounds to screen
		for (it = groundVector.rbegin(); it != groundVector.rend(); it++){											
			draw->ground(it->getX(), it->getY());
		}

		// draw player and text to backbuffer
		draw->player(player->getX(), player->getY());
		draw->gameText(player->getScore(), player->getSpeed());

		} if(isGameOver) {
			// Draw end text to backbuffer
			draw->endText(player->getScore());
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
	bool done = false;

	ALLEGRO_EVENT ev;
	al_wait_for_event(event_queue, &ev);

	timerEvent(ev);

	done = displayCloseEvent(ev);

	done = keyPressEvent(ev);
	
	drawEvent();

	return done;
}