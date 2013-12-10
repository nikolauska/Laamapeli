#include "Variables.h"
#include "Player.h"
#include "Ground.h"

ALLEGRO_TIMER* FPSTimer;
ALLEGRO_TIMER* upTimer;
ALLEGRO_TIMER* downTimer;
ALLEGRO_TIMER* scoreTimer;
ALLEGRO_TIMER* speedTimer;

Player *player;
vector<Ground> groundVector;
Ground* ground;
vector<Ground>::iterator it;


void startTimer(int timer){
	if(timer == 1){
		al_start_timer(upTimer);			// start uptimer (up speed for jump)
	} else {
		// Start inGame timers
		al_start_timer(scoreTimer);			// start scoretimer (timeinterval for giving point)
		al_start_timer(downTimer);			// start downtimer (speed in which player goes down)
		al_start_timer(speedTimer);			// start speedtimer (speed in which ground is moving below player)
	}
}

/*
*	Beginninng of upTimer object!
*	Here we make the player jump or go down 
*	if player has pressed jump button and is on ground he will start ro rise certain time
*	If player is not on ground and is not going up he will go down
*/

void upTimerEvent(ALLEGRO_EVENT ev){
	if(al_get_timer_started(upTimer)){                      // Check if uptimer is started
		if(ev.timer.source == upTimer){                     // Check if timer id uptimer
			if(al_get_timer_count(upTimer) >= (upTime)){    // Check if timer time is bigger than uptime (time player is going up)
				al_stop_timer(upTimer);						// Stop upTimer
				al_set_timer_count(upTimer, 0);				// Reset upTimer to 0
			} 

			player->moveUp();								// Move player up
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
	if(ev.timer.source == scoreTimer){							// Check if timer is scoreTimer
		player->addScore();										// Add point to player
		if(al_get_timer_count(scoreTimer) % speedScore == 0)	// Check if score equals to interval speed is added
			player->addSpeed();									// Add speed in which ground is moving to left
	}
}

/*
*	Beginninng of speedTimer object!
*	This is the function that will run if speed timer has ticked to it's specific time
*	Here we update ground position and move out of screen grounds back to screen
*
*/

void speedTimerEvent(){
	if(al_get_timer_started(speedTimer)){																// Check if timer is speedTimer
		if(al_get_timer_count(speedTimer) >= (1/player->getSpeed())) {									// Check if speedtimer is equal or bigger than 1/player speed
			int tempX = player->getX();																	// Get player X position
			int tempY = player->getY();																	// Get player Y position
			int tempH = draw->playerHeight();															// Get player picture height
			int tempW = draw->playerWidth();															// Get player picture width
			int speed = player->getSpeed();																// Get player player speed

			player->setGround(false);																	// Set player ground to false before groundcheck						
			for (it = begin(groundVector); it != end(groundVector); it++){								// Loop through all ground classes in vector 
				if(al_get_timer_started(upTimer) && speed > 2)											// Check if player is jumping and speed is equal or smaller than 2 (workaround for weird speedboost on jumping)
					it->move(speed - int(speed*0.2 + 1));												// Move ground at smaller speed
				else
					it->move(speed);																	// Move ground at normal speed 

				if (it->getX() + 300 <= 0)																// Check if ground is outside of screen
						it->create(lastX, lastY, speed);												// Move ground to new position to right

				if(it->getX() - 300 <= (tempX - tempW*1.5) && it->getX() + 300 - tempW/2 >= (tempX))	// Check if player is in ground in X-axel
					if(it->getY() == (tempY + tempH))													// Check if player is in ground on Y-axel
						player->setGround(true);														// Set player to be in ground
			}				
		}
	}
}


void downTimerEvent(ALLEGRO_EVENT ev){
	if(!(al_get_timer_started(upTimer))){	// Check if upTImer is not started					
		if(ev.timer.source == downTimer){	// Check if timer is downTimer
			if(!player->getGround())		// Check if player is in ground
				player->moveDown();			// Move player down
		}
	}
}

/*
*	Beginninng of timer object!
*	This function is being run when timer has ticked to specific time
*	example FPS so it's time to draw to screen or score so it's time to add points to player 
*
*/

bool timerEvent(ALLEGRO_EVENT ev){	
	bool tempDraw = false;					// Temporary bool to checkif it is timer to draw to screen
	if(ev.type == ALLEGRO_EVENT_TIMER){		// Check if event is timer
		if(ev.timer.source == FPSTimer)		// Check if event is FPSTimer
			tempDraw = true;				// Set temp bool to true
			
		if (gamePos == 3) {					// Check if gamePos is 3 ( 3 = inGame)
			upTimerEvent(ev);				// Run upTimerEvent

			downTimerEvent(ev);				// Run downTimerEvent		

			scoreTimerEvent(ev);			// Run scoreTimerEvent

			speedTimerEvent();				// Run speedTimerEvent
		}
	}
	return tempDraw;						// Return true or false
}
