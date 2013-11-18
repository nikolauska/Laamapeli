#include "Header.h"
#include "Player.h"
#include "Ground.h"
#include "Audio.h"
#include "Draw.h"

// Local variables
int tempJumpTime = 0;
int tempPointTime = 0;
int tempScore = 0;
int menuSelect = 1;
bool isGameOver = false;
bool done = false;
bool start = true;
bool menuBool = false;
bool settingsBool = false;

int main(int argc, char **argv)
{			
	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *FPSTimer = NULL;
	ALLEGRO_TIMER *upTimer = NULL;
	ALLEGRO_TIMER *downTimer = NULL;
	ALLEGRO_TIMER *scoreTimer = NULL;
	ALLEGRO_TIMER *speedTimer = NULL;
	
	//Test allegro object
	if(!al_init())										
		return -1;

	//create our display object
	display = al_create_display(WIDTH, HEIGHT);			

	//test display object
	if(!display)										
		return -1;

	// initalize player and ground class
	Player player = Player();
	Ground ground[gMax];
	Draw draw = Draw();
	Audio audio = Audio();

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
	
	// Start timers
	al_start_timer(FPSTimer);

	while(!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);		

		if(ev.type == ALLEGRO_EVENT_TIMER){
			if(ev.timer.source == FPSTimer) {
				if (menuBool) {
					if(audio.isInGamePlaying())
						audio.stopLoopInGame();

					if(!audio.isMenuPlaying())
						audio.loopMenu();

					draw.menu(menuSelect);

					// flip backbuffer to screen and empty old screen which is now in backbuffer
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));	
				}

				if (!menuBool && start) {
					if(audio.isMenuPlaying())
						audio.stopLoopMenu();

					if(!audio.isInGamePlaying())
						audio.loopInGame();

					start = false;

					ground[0].start();
					for (int j = 1; j != gMax; j++){
						ground[j].create(ground[gMax - 1].getX(), ground[gMax - 1].getY(), ground[gMax - 1].getLenght());
						draw.ground(ground[j].getX(), ground[j].getY());
					}

					player.start();

					// draw player, ground and text to backbuffer
					draw.player(player.getX(), player.getY());

					// flip backbuffer to screen and empty old screen which is now in backbuffer
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));	

					al_start_timer(scoreTimer);
					al_start_timer(downTimer);
					al_start_timer(speedTimer);
				}

				// Check if game is still running
				if (!isGameOver && !menuBool) {		
					// Do this if player is jumping
					/*if (player.getJump()) {
						tempJumpTime += 1;
						if (tempJumpTime <= jumpTime){
							if (player.getY() - pSize != 0)
								player.moveUp();
							} else {
								tempJumpTime = 0;
								player.setJump(false);
							}
					}*/

					// If player isn't jumping and isn't on ground then move down
					/*if (!player.getJump() && player.getGround())
						player.moveDown();*/


					// Add speed only once in specific score
					/*if (tempScore != player.getScore()){
						if (player.getScore() % speedScore == 0){
							player.addSpeed();
						}
					}
					tempScore = player.getScore();*/

					// check if player has dropped to bottom
					if (player.getY() + draw.picHeight() >= HEIGHT) {
						isGameOver = true;
						audio.death();
					};		
				
					// Update all ground positions and draw them to backbuffer
					player.setGround(false);

					for (int j = 0; j != gMax; j++){											
						draw.ground(ground[j].getX(),ground[j].getY());
					}

					// draw player and text to backbuffer
					draw.player(player.getX(), player.getY());
					draw.gameText(player.getScore(), player.getSpeed());

				} if(isGameOver) {
					// Draw end text to backbuffer
					draw.endText(player.getScore());
				}		

				al_flip_display();
				al_clear_to_color(al_map_rgb(0,0,0));
			}
			
			if (!isGameOver && !menuBool) {
				if(al_get_timer_started(upTimer)){
					if(ev.timer.source == upTimer) {
						if(al_get_timer_count(upTimer) == upTime){
							al_stop_timer(upTimer);
							al_set_timer_count(upTimer, 0);
						}

						player.moveUp();			
					}
										
				} else {
					if(ev.timer.source == downTimer) {
						if(!player.getGround())
							player.moveDown();			
					}
				}

				if(ev.timer.source == scoreTimer) {
					player.addScore();
					if(al_get_timer_count(scoreTimer) % speedScore == 0){
						player.addSpeed();
					}
				}

				if(al_get_timer_started(speedTimer)){
					if(al_get_timer_count(speedTimer) >= (1/player.getSpeed())) {
						for (int j = 0; j != gMax; j++){
							if (ground[j].getX() <= 0)
								if (j > 0)
									ground[j].create(ground[j - 1].getX(), ground[j - 1].getY(), ground[j - 1].getLenght());
								else
									ground[j].create(ground[gMax - 1].getX(), ground[gMax - 1].getY(), ground[gMax - 1].getLenght());
				
							if(ground[j].groundCheck(player.getX(), player.getY()))
									player.setGround(true);
											
							ground[j].move(player.getSpeed());
						}
					}
				}
			}
		}

		// If player closes the game
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			done = true;
		}

		// If player presses button
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_SPACE:{
					audio.jump();
					if (player.getGround())
						al_start_timer(upTimer);
					break;
				}
				case ALLEGRO_KEY_ENTER:{
					if(menuBool){
						switch(menuSelect){
							case(1):{
								menuBool = false;
							}
							case(2):{
								settingsBool = true;
							}
							case(3):{
								done = true;
							}
						}
					}					
					break;
				}
				case ALLEGRO_KEY_DOWN:{
					if (menuBool) {
						if(menuSelect != 3)
							menuSelect += 1;
					}						
					break;
				}
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

	// Destroy everything from memory
	al_destroy_event_queue(event_queue);
	al_destroy_timer(FPSTimer);
	al_destroy_timer(upTimer);
	al_destroy_timer(downTimer);
	al_destroy_timer(scoreTimer);
	al_destroy_display(display);

	return 0;
}