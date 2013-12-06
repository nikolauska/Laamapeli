#include "Variables.h"

ALLEGRO_FONT *fontLoading;
ALLEGRO_BITMAP *loading;
ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* event_queue;


void iniInitialize();
void getResPos();


void loadingScreen(string text){
	al_draw_scaled_bitmap(loading, 0, 0, al_get_bitmap_width(loading), al_get_bitmap_height(loading), 0, 0, WIDTH, HEIGHT, NULL);
	const char* text1C = text.c_str();
	al_draw_text(fontLoading, al_map_rgb(255, 0, 0), WIDTH/2, HEIGHT/8*7, ALLEGRO_ALIGN_CENTER, text1C);
	// Flip backbuffer to screen
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
}

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

	al_init_image_addon();
	al_init_font_addon(); 
	al_init_ttf_addon();

	string temp = folder + "/Pictures/loading.png";
	if(!(loading = al_load_bitmap(temp.c_str()))){
		al_show_native_message_box(display, "ERROR", "IMAGES", "Backround for loadingscreen not found! \nWe suggest to check if filename is correct in 'Pictures' folder. \nFilename for this file is 'loading.png'", NULL, NULL);
		
		al_destroy_display(display);
		return -1;
	}

	temp = folder + "/Font/font.ttf";
	if(!(fontLoading = al_load_font(temp.c_str(), 24, 0))){
		al_show_native_message_box(display, "ERROR", "FONT", "Font not found! \nWe suggest to check if filename is correct in 'Font' folder. \nFilename for this file is 'font.ttf'", NULL, NULL);
		
		al_destroy_display(display);
		return -1;
	}

	loadingScreen("Loading Resolutions...");

	getResPos();

	loadingScreen("Loading Player...");
	player = new Player();

	loadingScreen("Loading Draw functions...");	
	try{
		draw = new Draw(HEIGHT, WIDTH, folder);
	} catch(const char* message) {
		al_show_native_message_box(display, "ERROR", "IMAGES", message, NULL, NULL);

		al_destroy_display(display);
		delete player;
		delete draw;
		return -1;
	}

	loadingScreen("Loading Audio...");
	try{
		audio = new Audio(folder);	
	} catch(const char* message) {
		al_show_native_message_box(display, "ERROR", "AUDIO", message, NULL, NULL);

		al_destroy_display(display);
		delete player;
		delete draw;
		delete audio;
		return -1;
	}

	loadingScreen("Loading Keyboard/Mouse...");
	// Load addons for allegro
	al_install_keyboard();
	al_install_mouse();

	loadingScreen("Loading Timers...");
	// Create timer 
	FPSTimer = al_create_timer(1.0 / FPS);
	upTimer = al_create_timer(upSpeed);
	downTimer = al_create_timer(downSpeed);
	scoreTimer = al_create_timer(scoreTime);
	speedTimer = al_create_timer(startSpeed);

	event_queue = al_create_event_queue();

	loadingScreen("Loading Events...");
	// Register keyboard events
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(FPSTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(upTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(downTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(scoreTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(speedTimer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	

	// Start timer
	al_start_timer(FPSTimer);

	srand(time(NULL));
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