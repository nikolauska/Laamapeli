#include "Header.h"
#include "Player.h"
#include "Ground.h"

int main(int argc, char **argv)
{
	// initalize player and ground class
	Player player = Player();
	Ground ground[gMax];
	

	// Local variables
	int tempJumpTime = 0;
	int tempPointTime = 0;
	int tempScore = 0;
	bool isGameOver = false;
	bool done = false;
	bool start = true;

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_TIMER *pointTimer = NULL;
	ALLEGRO_TIMER *jumpTimer = NULL;
	ALLEGRO_FONT *font18 = NULL;

	//Test allegro object
	if(!al_init())										
		return -1;

	//create our display object
	display = al_create_display(WIDTH, HEIGHT);			

	//test display object
	if(!display)										
		return -1;

	// Load addons for allegro
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();

	// Create timer 
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	
	// Load font for text
	font18 = al_load_font("arial.ttf", 18, 0);

	// Register keyboard events
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	
	// Start timers
	al_start_timer(timer);

	while(!done)
	{
		if (start) {
			start = false;

			ground[0].start();
			for (int j = 1; j != gMax; j++){
				ground[j].create(ground[gMax - 1].getX(), ground[gMax - 1].getY(), ground[gMax - 1].getLenght());
				ground[j].draw();
			}

			player.start();

			// draw player, ground and text to backbuffer
			al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Score: %i", player.getScore());

			player.drawPlayer();

			// flip backbuffer to screen and empty old screen which is now in backbuffer
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));		
		}

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER) {
			// Check if game is still running
			if (!isGameOver) {		

				// Do this if player is jumping
				if (player.getJump()) {
					tempJumpTime += 1;
					if (tempJumpTime <= jumpTime){
						if (player.getY() - pSize != 0)
							player.moveUp();
					}
					else {
						tempJumpTime = 0;
						player.setJump(false);
					}
				}	

				// check if it's time to update score
				tempPointTime += 1;
				if (tempPointTime >= pointTime) {
					player.addScore();
					tempPointTime = 0;
				}

				if (tempScore != player.getScore()){
					if (player.getScore() % speedScore == 0){
						player.addSpeed();
					}
				}
				tempScore = player.getScore();

				// ckeck if player has dropped to bottom
				if (player.getY() >= HEIGHT)
					isGameOver = true;

				// draw player, ground and text to backbuffer
				al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Score: %i	Speed: %i", player.getScore(), player.getSpeed());

				if (!player.getJump() && player.getGround())
					player.moveDown();

				player.setGround(false);
			
				for (int j = 0; j != gMax; j++){
					if (ground[j].getX() <= 0)
						if (j > 0)
							ground[j].create(ground[j - 1].getX(), ground[j - 1].getY(), ground[j - 1].getLenght());
						else
							ground[j].create(ground[gMax - 1].getX(), ground[gMax - 1].getY(), ground[gMax - 1].getLenght());
				
					if(ground[j].groundCheck(player.getX(), player.getY()))
						player.setGround(true);
											
					ground[j].move(player.getSpeed());
					ground[j].draw();
				}

				

			} else {
				// Draw end text to backbuffer
				al_draw_textf(font18, al_map_rgb(0, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Game Over. Final Score: %i ! Press Enter to restart!", player.getScore());
			}
			
			player.drawPlayer();

			// flip backbuffer to screen and empty old screen which is now in backbuffer
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

		// If player closes to game
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true;

		// If player presses button
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_SPACE:{
					if (player.getGround())
						player.setJump(true);
					break;
				}
				case ALLEGRO_KEY_ENTER:{
					if (isGameOver) {
						start = true;
						isGameOver = false;
					}						
				break;
				}
			}
		}
	}

	// Destroy everything from memory
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font18);
	al_destroy_display(display);

	return 0;
}

