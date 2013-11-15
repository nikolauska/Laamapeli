#include "Header.h"
#include "Player.h"
#include "Ground.h"
#include "Text.h"

int main(int argc, char **argv)
{
	// initalize player and ground class
	Player player = Player();
	Ground ground[gMax];
	Text text = Text();
	

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
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();

	font18 = al_load_font("arial.ttf", 18, 0);

	// Create timer 
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	

	// Register keyboard events
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	
	// Start timers
	al_start_timer(timer);


	// Start audio
	ALLEGRO_SAMPLE *lamasong = al_load_sample("Data\\Audio\\llama_song.ogg");
	ALLEGRO_SAMPLE *njak = al_load_sample("Data\\Audio\\njak.ogg");
	ALLEGRO_SAMPLE *die = al_load_sample("Data\\Audio\\llama_is_kill.ogg");
	al_reserve_samples(3);
	al_play_sample(lamasong, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);


	while(!done)
	{
		if (menuBool) {

			al_draw_text(font18, al_map_rgb(255, 0, 255), menuPlayGamePosX, menuPlayGamePosY, ALLEGRO_ALIGN_CENTER, "Play game");
			al_draw_text(font18, al_map_rgb(255, 0, 255), menuSettingsPosX, menuSettingsPosY, ALLEGRO_ALIGN_CENTER, "Settings");
			al_draw_text(font18, al_map_rgb(255, 0, 255), menuExitPosX, menuExitPosY, ALLEGRO_ALIGN_CENTER, "Quit");

			if(menuSelect == 1) {
				int x1 = menuPlayGamePosX - 50;
				int y1 = menuPlayGamePosY + 25;

				int x2 = menuPlayGamePosX + 50;
				int y2 = menuPlayGamePosY + 25;

				al_draw_line(x1, y1, x2, y2, al_map_rgb(255, 0, 0), 5);
				//text.animateUp(1);
				//text.animateDown(2);
				//text.animateDown(3);
			} 
			else if(menuSelect == 2) {	
				int x1 = menuSettingsPosX - 50;
				int y1 = menuSettingsPosY + 25;

				int x2 = menuSettingsPosX + 50;
				int y2 = menuSettingsPosY + 25;

				al_draw_line(x1, y1, x2, y2, al_map_rgb(255, 0, 0), 5);
				//text.animateDown(1);
				//text.animateUp(2);
				//text.animateDown(3);
			}
			else if(menuSelect == 3) {
				int x1 = menuExitPosX - 50;
				int y1 = menuExitPosY + 25;

				int x2 = menuExitPosX + 50;
				int y2 = menuExitPosY + 25;

				al_draw_line(x1, y1, x2, y2, al_map_rgb(255, 0, 0), 5);
				//text.animateDown(1);
				//text.animateDown(2);
				//text.animateUp(3);
			}

			// flip backbuffer to screen and empty old screen which is now in backbuffer
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));	
		}

		if (!menuBool && start) {
			start = false;


			ground[0].start();
			for (int j = 1; j != gMax; j++){
				ground[j].create(ground[gMax - 1].getX(), ground[gMax - 1].getY(), ground[gMax - 1].getLenght());
				ground[j].draw();
			}

			player.start();

			// draw player, ground and text to backbuffer
			player.drawPlayer();

			// flip backbuffer to screen and empty old screen which is now in backbuffer
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));		
		}

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER) {
			// Check if game is still running
			if (!isGameOver && !menuBool) {		

				// Do this if player is jumping
				if (player.getJump()) {

					//al_play_sample(njak, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

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

				// Check if it's time to update score
				tempPointTime += 1;
				if (tempPointTime >= pointTime) {
					player.addScore();
					tempPointTime = 0;
				}

				// Add speed only once in specific score
				if (tempScore != player.getScore()){
					if (player.getScore() % speedScore == 0){
						player.addSpeed();
					}
				}
				tempScore = player.getScore();

				// check if player has dropped to bottom
				if (player.getY() >= HEIGHT) {
					isGameOver = true;
					al_play_sample(die, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				};

				// If player isn't jumping and isn't on ground then move down
				if (!player.getJump() && player.getGround())
					player.moveDown();

				player.setGround(false);
				
				// Update all ground positions and draw them to backbuffer
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

				// draw player and text to backbuffer
				player.drawPlayer();
				al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Score: %i	Speed: %i", player.getScore(), player.getSpeed());

			} else {
				// Draw end text to backbuffer
				al_draw_textf(font18, al_map_rgb(0, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Game Over. Final Score: %i ! Press Enter to restart!", player.getScore());
			}		

			// flip backbuffer to screen and empty old screen which is now in backbuffer
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

		// If player closes the game
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true;

		// If player presses button
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_SPACE:{

					al_play_sample(njak, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

					if (player.getGround())
						player.setJump(true);
					break;
				}
				case ALLEGRO_KEY_ENTER:{
					if(menuBool){
						switch(menuSelect){
							case(0):{
								menuBool = false;
							}
							case(1):{
								settingsBool = true;
							}
							case(2):{
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
	al_destroy_timer(timer);
	al_destroy_font(font18);
	al_destroy_display(display);
	al_destroy_sample(lamasong);
	al_destroy_sample(njak);
	al_destroy_sample(die);

	return 0;
}

