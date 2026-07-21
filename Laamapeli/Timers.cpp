#include "Variables.h"
#include "Player.h"
#include "Ground.h"

ALLEGRO_TIMER* FPSTimer;
ALLEGRO_TIMER* scoreTimer;

Player *player;
vector<Ground> groundVector;
vector<Ground>::iterator it;




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
	int previousY = player->getPreviousY();
	int tempH = draw->playerHeight();
	int tempW = draw->playerWidth();
	int speed = player->getSpeed();

	player->setGround(false);
	for (it = begin(groundVector); it != end(groundVector); it++){
		it->move(speed);

		if (it->getX() + 300 <= 0)
			it->create(lastX, lastY, speed);

		if(it->getX() - 300 <= (tempX - tempW*1.5) && it->getX() + 300 - tempW/2 >= tempX)
			if(player->isFalling() && previousY + tempH <= it->getY() && tempY + tempH >= it->getY())
				player->land(it->getY() - tempH);
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
			if (gamePos == 3) {
				player->update(gravity, 1.0f / FPS);
				moveGrounds();
			}
		}
			
		if (gamePos == 3) {					// Check if gamePos is 3 ( 3 = inGame)

			scoreTimerEvent(ev);			// Run scoreTimerEvent
		}
	}
	return tempDraw;						// Return true or false
}
