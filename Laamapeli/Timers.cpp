#include "Variables.h"
#include "Player.h"
#include "Ground.h"

ALLEGRO_TIMER* FPSTimer;
ALLEGRO_TIMER* upTimer;
ALLEGRO_TIMER* downTimer;
ALLEGRO_TIMER* scoreTimer;

Player *player;
vector<Ground> groundVector;
vector<Ground>::iterator it;


void startTimer(int timer){
	if(timer == 1){
		al_start_timer(upTimer);			// start uptimer (up speed for jump)
	} else {
		// Start inGame timers
		al_start_timer(scoreTimer);			// start scoretimer (timeinterval for giving point)
		al_start_timer(downTimer);			// start downtimer (speed in which player goes down)
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
*	Beginninng of ground movement object!
*	This function updates ground positions once per rendered frame
*	and moves off-screen grounds back to the screen.
*
*/

void moveGrounds(){
	int tempX = player->getX();
	int tempY = player->getY();
	int tempH = draw->playerHeight();
	int tempW = draw->playerWidth();
	int speed = player->getSpeed();

	player->setGround(false);
	for (it = begin(groundVector); it != end(groundVector); it++){
		if(al_get_timer_started(upTimer) && speed > 2)
			it->move(speed - int(speed*0.2 + 1));
		else
			it->move(speed);

		if (it->getX() + 300 <= 0)
			it->create(lastX, lastY, speed);

		if(it->getX() - 300 <= (tempX - tempW*1.5) && it->getX() + 300 - tempW/2 >= (tempX))
			if(it->getY() == (tempY + tempH))
				player->setGround(true);
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
		if(ev.timer.source == FPSTimer) {		// Check if event is FPSTimer
			tempDraw = true;					// Set temp bool to true
			if (gamePos == 3)
				moveGrounds();
		}
			
		if (gamePos == 3) {					// Check if gamePos is 3 ( 3 = inGame)
			upTimerEvent(ev);				// Run upTimerEvent

			downTimerEvent(ev);				// Run downTimerEvent		

			scoreTimerEvent(ev);			// Run scoreTimerEvent
		}
	}
	return tempDraw;						// Return true or false
}
