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

bool timerEvent(ALLEGRO_EVENT ev){
	bool tempDraw = false;
	if(ev.type == ALLEGRO_EVENT_TIMER){
		if(ev.timer.source == FPSTimer)
			tempDraw = true;			
			
		if (gamePos == 3) {
			upTimerEvent(ev);

			scoreTimerEvent(ev);

			speedTimerEvent();
		}
	}
	return tempDraw;
}
