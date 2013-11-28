#include "Variables.h"

void iniInitialize();
void loadingScreen();
void getResPos();

int initialize(){

	//Test allegro object
	if(!al_init())										
		return -1;
	
	iniInitialize();

	//create our display object
	display = al_create_display(WIDTH, HEIGHT);
	//test display object
	if(!display)										
		return -1;	

	loadingScreen();

	getResPos();

	player = new Player();
	draw = new Draw(HEIGHT, WIDTH);
	audio = new Audio();	

	// Load addons for allegro
	al_install_keyboard();

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
*	Beginninng of destroy object!
*	Here we destroy everything from memory
*	This prevents memory leaks (we don't want your PC to run slow)
*	
*/

void groundVectorDestroy(){
	// Destroy all classes from vector
	for (it = groundVector.begin(); it != groundVector.end(); it++){
		it->~Ground();
	}

	// Destroy vector 
	groundVector.erase(groundVector.begin(), groundVector.end());
}

void destroy(){
	groundVectorDestroy();

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