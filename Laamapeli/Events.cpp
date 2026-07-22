#include "Variables.h"

int menuSelect = 1;
int menuText = 1;	// 1 = main, 2 = settings, 3 = graphics, 4 = audio
int gamePos = 1;	// 1 = menu, 2 = start, 3 = inGame, 4 = end

int initialize(Settings&);
void destroy();
void groundVectorDestroy();


/*
*	Beginninng of display close object!
*	If player happened to close game from top right X
*	then this function will run
*
*/

bool displayCloseEvent(ALLEGRO_EVENT ev){
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){ // Check if user has closed window
		return true;
	}
	return false;
}

/*
*	Beginninng of keypress event object!
*	This is where program what key has been pressed 
*	Both ingame and menu functions are handled
*
*/

bool keyPressEvent(ALLEGRO_EVENT ev, Settings& settings){
	bool temp = false;	// Temporary bool for returning if player wnts to end game

	if(ev.type == ALLEGRO_EVENT_KEY_DOWN){	// Check if player presses keyboard button
		switch(ev.keyboard.keycode){		// Switch for selecting which button was pressed

			// ESCAPE button
			case ALLEGRO_KEY_ESCAPE:{
				// If gamePos equals to 3 (ingame) then set it to 1(menu) and destroy groundvector and ssop ingamesong from looping
				if (gamePos == 3){									
					gamePos = 1;
					groundVectorDestroy();
					audio->stopLoopInGame();
				}
				// gamePos equals to 1 (menu)
				else if(gamePos == 1)
					// menutext equals to 1 (main menu)
					if(menuText == 1)
						temp = true; // set temp value to true (for ending game)
					else
						// Return to last menu
						if(menuText != 4)	
							menuText -= 1;
						else 
							menuText = 2;
				break;
			}

			// SPACE button
			case ALLEGRO_KEY_SPACE:{
				// gamePOs equalt to 3 (ingame)
				if(gamePos == 3) {
					// Jump when the player is standing on a platform
					if (player->jump(settings.jumpSpeed))
						audio->jump(settings.volume, settings.pan);
				}
				break;
			}
			// ENTER button
			case ALLEGRO_KEY_ENTER:{
				// Switch gamePos to do different thisg on different situations
				switch(gamePos){
					// menu
					case(1):{
						// switch to select in which menu we are
						switch(menuText){
							case(1):{ // Main menu
								// switch to select in which position selection is
								switch (menuSelect){
									case(1):{ // top
										gamePos = 2; // start game
										menuSelect = 0;
										break;
									}
									case(2):{ // middle
										menuText = 2; // set menutext to 2 (settings menu)
										menuSelect = 0;
										break;
									}
									case(3):{ //down
										temp = true; // Set temp to true (end game)
										break;
									}
								}
								break;
							}
							case(2):{ // Settings menu
								switch (menuSelect){
									case(1):{ // top
										menuText = 3; // set menutext to 3 (graphics menu)
										menuSelect = 0;
										break;
									}
									case(2):{ // middle
										menuText = 4; // set menutext to 4 (audio menu)
										menuSelect = 0;
										break;
									}
									case(3):{ //down
										menuText = 1; // set menutext to 1 (main menu)
										menuSelect = 0;
										break;
									}
								}
								break;
							}
							case(3):{ // Graphics menu
								switch (menuSelect){
									case(1):{ // top
										// Save values currently shown in screen to  ini file and initialize game again
										settings.saveDisplay(resWidth[resPos], resHeight[resPos], settings.pendingFPS);
										destroy();
										initialize(settings);
										break;
									}
									case(2):{ // middle
										// Save values currently shown in screen to  ini file and initialize game again
										settings.saveDisplay(resWidth[resPos], resHeight[resPos], settings.pendingFPS);
										destroy();
										initialize(settings);
										break;
									}
									case(3):{ //down
										menuText = 2; // Return to settings menu
										menuSelect = 0;
										break;
									}
								}
								break;
							}
							case(4):{ // Audio menu
								switch (menuSelect){
									case(1):{ // top
										// Save and apply the values currently shown
										settings.saveAudio(settings.pendingVolume, settings.pendingPan);
										break;
									}
									case(2):{ // middle
										// Save and apply the values currently shown
										settings.saveAudio(settings.pendingVolume, settings.pendingPan);
										break;
									}
									case(3):{ //down
										menuText = 2; // Return to settings menu
										menuSelect = 0;
										break;
									}
								}
								break;
							}
						}
						break;
					}
					case(4):{ // End screen
						// Get to menu and destroy ground vector
						gamePos = 1;
						menuText = 1;
						groundVectorDestroy();
						break;
					}
				}
			}
			// DOWN button
			case ALLEGRO_KEY_DOWN:{
				if (gamePos == 1) {			// if in menu
					if(menuSelect != 3)		// if menuselect is not 3
						menuSelect += 1;	// then add 1
				}						
				break;
			}

			// UP button
			case ALLEGRO_KEY_UP:{
				if (gamePos == 1) {			// if in menu
					if(menuSelect != 1)		// if menuselect is not 1
						menuSelect -= 1;	// then minus 1
				}						
				break;
			}
			// LEFT button
			case ALLEGRO_KEY_LEFT:{
				if(gamePos == 1) { // if in menu
					switch(menuText){
						case(3):{ // Graphics
							switch(menuSelect){
								case(1):{ // top
									if(resPos != 0) // if not 0
										resPos -= 1; // then minus 1
									break;
								}
								case(2):{ // middle
									if(settings.pendingFPS != 5) // if not 5
										settings.pendingFPS -= 5; // then minus 5
									break;
								}
							}
							break;
						}
						case(4):{ // Audio
							switch(menuSelect){
								case(1):{ // top
									if(settings.pendingVolume != 0)  // if not 0
										settings.pendingVolume -= 1; // then minus 1
									break;
								}
								case(2):{ // middle
									if(settings.pendingPan > -1)	// if bigger -1
										settings.pendingPan -= 0.1; // then minus 0.1
									else
										settings.pendingPan = -1;   // else set to -1
									break;
								}
							}
							break;
						}
					}
				}					
				break;
			}
			case ALLEGRO_KEY_RIGHT:{
				if(gamePos == 1) {
					switch(menuText){
						case(3):{ // Graphics
							switch(menuSelect){
								case(1):{ // top 
									if(resPos != resolutions - 1)	// if not end of list
										resPos += 1;				// then add 1
									break;
								}
								case(2):{ // middle
									settings.pendingFPS += 5; // add 5
									break;
								}
							}
							break;
						}
						case(4):{ // Audio
							switch(menuSelect){
								case(1):{
									if(settings.pendingVolume != 100) // if not 100
										settings.pendingVolume += 1;  // add 1
									break;
								}
								case(2):{
									if(settings.pendingPan < 1)		// if smaller than 1
										settings.pendingPan += 0.1; // then add 0.1
									else
										settings.pendingPan = 1;	// else set to 1
									break;
								}
							}
							break;
						}
					}						
					break;
				}
			}	
		}
	}
	return temp;
}

bool mouseEvent(ALLEGRO_EVENT ev, Settings& settings){
	bool mouseTemp = false; // Temprary bool to return if player wants to quit

		if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){ // if event is mouse button is pressed
			if(gamePos == 1){ // menu
				if(ev.mouse.x <= (settings.width/2 + 150) && ev.mouse.x >= (settings.width/2 - 150)){ // if mouse is in middle of screen
					if(ev.mouse.y <= (settings.height/8*3 + 50) && ev.mouse.y >= (settings.height/8*3 - 50)){ // if mouse is in top Y position
						switch(menuText){
							case(1):{ // main menu
								gamePos = 2; // start game
								break;
							}
							case(2):{ // settings menu
								menuText = 3; // go to graphics menu
								break;
							}
							case(3):{ // graphics menu
								// Save values to ini and reinitialize game
								settings.saveDisplay(resWidth[resPos], resHeight[resPos], settings.pendingFPS);
								destroy();
								initialize(settings);
								break;
							}
							case(4):{ // audio menu
								// Save and apply the values currently shown
								settings.saveAudio(settings.pendingVolume, settings.pendingPan);
								break;
							}
						}
					}
					if(ev.mouse.y <= (settings.height/8*4 + 50) && ev.mouse.y >= (settings.height/8*4 - 50)){ // if mouse is in middle Y position
						switch(menuText){
							case(1):{ // main menu
								menuText = 2; // go to settings menu
								break;
							}
							case(2):{ // settings menu
								menuText = 4; // got to audio menu
								break;
							}
							case(3):{ // graphics menu
								// Save values to ini and reinitialize game
								settings.saveDisplay(resWidth[resPos], resHeight[resPos], settings.pendingFPS);
								destroy();
								initialize(settings);
								break;
							}
							case(4):{ // audio menu
								// Save and apply the values currently shown
								settings.saveAudio(settings.pendingVolume, settings.pendingPan);
								break;
							}
						}
					}
					if(ev.mouse.y <= (settings.height/8*5 + 50) && ev.mouse.y >= (settings.height/8*5 - 50)){ // if mouse is in bottom Y position
						switch(menuText){
							case(1):{ // main menu
								mouseTemp = true; // set exit temp to true
								break;
							}
							case(2):{ // settings menu
								menuText = 1; // go to main menu
								break;
							}
							case(3):{ // graphics menu 
								menuText = 2; // go to setting menu
								break;
							}
							case(4):{ // audio menu
								menuText = 2; // go to setting menu
								break;
							}
						}
					}
				}				
			}
			else if(gamePos == 3){ // ingame
				// Jump when the player is standing on a platform
				if (player->jump(settings.jumpSpeed))
					audio->jump(settings.volume, settings.pan);
			}
			else if(gamePos == 4){ // end screen
				// Go to menu and destroy ground vector
				gamePos = 1;
				menuText = 1;
				groundVectorDestroy();
			}
		} else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY){ // if mouse moves or enters display
			if(ev.mouse.x <= (settings.width/2 + 150) && ev.mouse.x >= (settings.width/2 - 150)){	// if mouse in middle
				if(ev.mouse.y <= (settings.height/8*3 + 50) && ev.mouse.y >= (settings.height/8*3 - 50)){ //if mouse in top y Position
					switch(menuText){
						case(3):{ // graphics menu
							if(ev.mouse.dz > 0)					// mouse scroll forward
								if(resPos != resolutions - 1)	// if not last of list
									resPos += 1;				// then add 1
								else
									resPos = 0;					// add to start
							else if(ev.mouse.dz < 0)			// mouse scroll backward
								if(resPos != 0)					// if not 0
									resPos -= 1;				// minus 1
								else
									resPos = resolutions - 1;	// set to end
							break;
						}
						case(4):{ // audio menu 
							if(ev.mouse.dz > 0)			// mouse scroll forward 		
								if(settings.pendingVolume != 100)	// if not 100
									settings.pendingVolume += 1;	// add 1
								else
									settings.pendingVolume = 100;	// set to 100
							else if(ev.mouse.dz < 0)	// mouse scroll backward
								if(settings.pendingVolume != 0)			// if not 0
									settings.pendingVolume -= 1;	// minus 1
								else
									settings.pendingVolume = 0;		// set to 0					
							break;
						}
					}
					menuSelect = 1; // set menuselect to top
				}
				if(ev.mouse.y <= (settings.height/8*4 + 50) && ev.mouse.y >= (settings.height/8*4 - 50)){
					switch(menuText){
						case(3):{
							if(ev.mouse.dz > 0)			// mouse scroll forward 
									settings.pendingFPS += 5;		// add 5
							else if(ev.mouse.dz < 0)	// mouse scroll backward
								if(settings.pendingFPS != 5)		// if not 5
									settings.pendingFPS -= 5;		// minus 5
								else
									settings.pendingFPS = 5;		// set to 5
							break;
						}
						case(4):{
							if(ev.mouse.dz > 0)			// mouse scroll forward 
								if(settings.pendingPan < 1)			// if smaller than 1
									settings.pendingPan += 0.1;		// add 0.1
								else
									settings.pendingPan = 1;		// set to 1
							else if(ev.mouse.dz < 0)	// mouse scroll backward
								if(settings.pendingPan > -1)		// if bigger than -1
									settings.pendingPan -= 0.1;		// minus 1
								else
									settings.pendingPan = -1;		// set to -1
							break;
						}
					}
					menuSelect = 2; // set menuselect to middle
				}
				if(ev.mouse.y <= (settings.height/8*5 + 50) && ev.mouse.y >= (settings.height/8*5 - 50)){
					menuSelect = 3; // set menuselect to bottom
				}
			}
		}
	return mouseTemp;
}

/*
*	Beginninng of draw object!
*	This is where program does all the drawing to screen stuff 
*	This is also where we check if player is dead and start/stop audio
*
*/

void drawEvent(const Settings& settings){
	// Menu draw
	switch(gamePos){
		case(1):{ // menu

			// Menu music
			if(!audio->isMenuPlaying())
				audio->loopMenu(settings.volume, settings.pan);

			// draw menu screen
			draw->menu(menuText, menuSelect, resWidth[resPos], resHeight[resPos], settings.pendingFPS, settings.pendingVolume, settings.pendingPan);
			break;
		}
		case(2):{ // start
			gamePos = 3; //go to ingame

			player->start(settings.startSpeed, settings.width, settings.height); // set player start position
	
			groundVector.emplace_back(settings.height);
			groundVector.back().start(settings.width, settings.height, draw->playerHeight(), lastX, lastY);

			for (int j = 0; j != int((settings.width / 300) + 15); j++){ // loop as many times as diffrent ground are needed
				groundVector.emplace_back(settings.height);
				groundVector.back().create(lastX, lastY, player->getSpeed());
			}

			al_start_timer(scoreTimer);
			break;
		}
		case(3):{ // ingame

			// If menu song is playing then stop it
			if(audio->isMenuPlaying())
				audio->stopLoopMenu();

			// If ingame song is not playing then start it
			if(!audio->isInGamePlaying())
				audio->loopInGame(settings.volume, settings.pan);

			// draw backround image
			draw->bg();

			// check if player has dropped to bottom
			if (player->getY() + draw->playerHeight() >= settings.height) {
				// set gamepos to 4 (end) and stop ingame song and play  end sound
				gamePos = 4;
				audio->stopLoopInGame();
				audio->death(settings.volume, settings.pan);
			};		

			// Draw grounds to screen
			for (it = groundVector.begin(); it != groundVector.end(); it++)
				draw->ground(it->getX(), it->getY());				

			// draw player and text to backbuffer
			draw->player(player->getX(), player->getY());
			draw->gameText(player->getScore(), player->getSpeed());
			break;
		}
		case(4):{
			// Draw end text to backbuffer
			draw->endText(player->getScore());
			break;
		}
	}
	
	al_flip_display(); // Flip backbuffer to screen
	al_clear_to_color(al_map_rgb(0,0,0)); // empty backbuffer
}		