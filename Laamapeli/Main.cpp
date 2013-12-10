#include "Variables.h"

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
int lastX;
int lastY;

const int resolutions = 10;
int resWidth[resolutions] = {640, 800, 1024, 1280, 1280, 1366, 1600, 1600, 1680, 1920};
int resHeight[resolutions] = {480, 600, 768, 720, 960, 768, 900, 1200, 1050, 1080};

// Object variables
int initialize();
bool timerEvent(ALLEGRO_EVENT);
bool displayCloseEvent(ALLEGRO_EVENT);
bool keyPressEvent(ALLEGRO_EVENT);
bool mouseEvent(ALLEGRO_EVENT);
void drawEvent();
void destroy();

bool redraw = false;

/*
*	Beginninng of main object!
*	Here is the famous main loop which will keep our game running
*	if this is ended the whole program will end
*	
*/

int main(int argc, char **argv)
{	
	if(initialize() == -1)										// running initialize 
		return -1;

	while(true) {	
		ALLEGRO_EVENT ev;										// New event
		al_wait_for_event(event_queue, &ev);					// wait for event to arrive

		if(timerEvent(ev))										// check for timers
			redraw = true;										// if return true then redraw on true										

		if(displayCloseEvent(ev))								// Check if user has closed game from red X
			break;												// returns true if has closed window

		if(keyPressEvent(ev))									// Check if player has pressed keyboard button
			break;												// Returns true if player pressed ESC on menu or pressed enter on quit

		if(mouseEvent(ev))										// Check for muose events
			break;												// return true if player press quit with mouse
		
		if(redraw && al_is_event_queue_empty(event_queue)) {    // Check if redraw is true and event queue is empty
			redraw = false;										// set redraw to false
			drawEvent();										// draw stuff to screen
		}
	}	

	destroy();													// Destroy everything from memory

	return 0;
}
