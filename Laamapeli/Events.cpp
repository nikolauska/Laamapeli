#include "Variables.h"

int menuSelect = 1;
int menuText = 1;	// 1 = main, 2 = settings, 3 = graphics, 4 = audio
int gamePos = 1;	// 1 = menu, 2 = start, 3 = inGame, 4 = end
float tempPan;
int tempFPS;
int tempVolume;

void timerInitalize(ALLEGRO_EVENT_QUEUE*);
void startTimer(int);
int initialize();
void destroy();
void groundVectorDestroy();
string round(float);
void iniWrite(string, string, string);


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

bool keyPressEvent(ALLEGRO_EVENT ev){
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
					// If player is in ground then player jumpsound and start uptimer so player will go up
					if (player->getGround()){
						audio->jump(Volume, Pan);
						startTimer(1); // 1 (upTimer)
					}
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
										iniWrite("Display", "Width", to_string(resWidth[resPos]));
										iniWrite("Display", "Height", to_string(resHeight[resPos]));
										iniWrite("Display", "FPS", to_string(tempFPS));
										destroy();
										initialize();
										break;
									}
									case(2):{ // middle
										// Save values currently shown in screen to  ini file and initialize game again
										iniWrite("Display", "Width", to_string(resWidth[resPos]));
										iniWrite("Display", "Height", to_string(resHeight[resPos]));
										iniWrite("Display", "FPS", to_string(tempFPS));
										destroy();
										initialize();
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
										// Save values currently shown in screen to ini file and initialize game again
										iniWrite("Audio", "Volume", to_string(tempVolume));
										iniWrite("Audio", "Pan", round(tempPan));
										destroy();
										initialize();
										break;
									}
									case(2):{ // middle
										// Save values currently shown in screen to ini file and initialize game again
										iniWrite("Audio", "Volume", to_string(tempVolume));
										iniWrite("Audio", "Pan", round(tempPan));
										destroy();
										initialize();
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
									if(tempFPS != 5) // if not 5
										tempFPS -= 5; // then minus 5
									break;
								}
							}
							break;
						}
						case(4):{ // Audio
							switch(menuSelect){
								case(1):{ // top
									if(tempVolume != 0)  // if not 0
										tempVolume -= 1; // then minus 1
									break;
								}
								case(2):{ // middle
									if(tempPan > -1)	// if bigger -1
										tempPan -= 0.1; // then minus 0.1
									else
										tempPan = -1;   // else set to -1
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
									tempFPS += 5; // add 5
									break;
								}
							}
							break;
						}
						case(4):{ // Audio
							switch(menuSelect){
								case(1):{
									if(tempVolume != 100) // if not 100
										tempVolume += 1;  // add 1
									break;
								}
								case(2):{
									if(tempPan < 1)		// if smaller than 1
										tempPan += 0.1; // then add 0.1
									else
										tempPan = 1;	// else set to 1
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

bool mouseEvent(ALLEGRO_EVENT ev){
	bool mouseTemp = false; // Temprary bool to return if player wants to quit

		if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){ // if event is mouse button is pressed
			if(gamePos == 1){ // menu
				if(ev.mouse.x <= (WIDTH/2 + 150) && ev.mouse.x >= (WIDTH/2 - 150)){ // if mouse is in middle of screen
					if(ev.mouse.y <= (HEIGHT/8*3 + 50) && ev.mouse.y >= (HEIGHT/8*3 - 50)){ // if mouse is in top Y position
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
								iniWrite("Display", "Width", to_string(resWidth[resPos]));
								iniWrite("Display", "Height", to_string(resHeight[resPos]));
								iniWrite("Display", "FPS", to_string(tempFPS));
								destroy();
								initialize();
								break;
							}
							case(4):{ // audio menu
								// Save values to ini and reinitialize game
								iniWrite("Audio", "Volume", to_string(tempVolume));
								iniWrite("Audio", "Pan", round(tempPan));
								destroy();
								initialize();	
								break;
							}
						}
					}
					if(ev.mouse.y <= (HEIGHT/8*4 + 50) && ev.mouse.y >= (HEIGHT/8*4 - 50)){ // if mouse is in middle Y position
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
								iniWrite("Display", "Width", to_string(resWidth[resPos]));
								iniWrite("Display", "Height", to_string(resHeight[resPos]));
								iniWrite("Display", "FPS", to_string(tempFPS));
								destroy();
								initialize();
								break;
							}
							case(4):{ // audio menu
								// Save values to ini and reinitialize game
								iniWrite("Audio", "Volume", to_string(tempVolume));
								iniWrite("Audio", "Pan", round(tempPan));
								destroy();
								initialize();	
								break;
							}
						}
					}
					if(ev.mouse.y <= (HEIGHT/8*5 + 50) && ev.mouse.y >= (HEIGHT/8*5 - 50)){ // if mouse is in bottom Y position
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
				// if player in ground then jump and play jump sound
				if (player->getGround()){
					audio->jump(Volume, Pan);
					startTimer(1);
				}
			}
			else if(gamePos == 4){ // end screen
				// Go to menu and destroy ground vector
				gamePos = 1;
				menuText = 1;
				groundVectorDestroy();
			}
		} else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY){ // if mouse moves or enters display
			if(ev.mouse.x <= (WIDTH/2 + 150) && ev.mouse.x >= (WIDTH/2 - 150)){	// if mouse in middle
				if(ev.mouse.y <= (HEIGHT/8*3 + 50) && ev.mouse.y >= (HEIGHT/8*3 - 50)){ //if mouse in top y Position
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
								if(tempVolume != 100)	// if not 100
									tempVolume += 1;	// add 1
								else
									tempVolume = 100;	// set to 100
							else if(ev.mouse.dz < 0)	// mouse scroll backward
								if(resPos != 0)			// if not 0
									tempVolume -= 1;	// minus 1
								else
									tempVolume = 0;		// set to 0					
							break;
						}
					}
					menuSelect = 1; // set menuselect to top
				}
				if(ev.mouse.y <= (HEIGHT/8*4 + 50) && ev.mouse.y >= (HEIGHT/8*4 - 50)){
					switch(menuText){
						case(3):{
							if(ev.mouse.dz > 0)			// mouse scroll forward 
									tempFPS += 5;		// add 5
							else if(ev.mouse.dz < 0)	// mouse scroll backward
								if(tempFPS != 5)		// if not 5
									tempFPS -= 5;		// minus 5
								else
									tempFPS = 5;		// set to 5
							break;
						}
						case(4):{
							if(ev.mouse.dz > 0)			// mouse scroll forward 
								if(tempPan < 1)			// if smaller than 1
									tempPan += 0.1;		// add 0.1
								else
									tempPan = 1;		// set to 1
							else if(ev.mouse.dz < 0)	// mouse scroll backward
								if(tempPan > -1)		// if bigger than -1
									tempPan -= 0.1;		// minus 1
								else
									tempPan = -1;		// set to -1
							break;
						}
					}
					menuSelect = 2; // set menuselect to middle
				}
				if(ev.mouse.y <= (HEIGHT/8*5 + 50) && ev.mouse.y >= (HEIGHT/8*5 - 50)){
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

void drawEvent(){
	// Menu draw
	switch(gamePos){
		case(1):{ // menu

			// Menu music
			if(!audio->isMenuPlaying())
				audio->loopMenu(Volume, Pan);

			// draw menu screen
			draw->menu(menuText, menuSelect, resWidth[resPos], resHeight[resPos], tempFPS, tempVolume, tempPan);
			break;
		}
		case(2):{ // start
			gamePos = 3; //go to ingame

			player->start(startSpeed, WIDTH, HEIGHT); // set player start position
	
			ground = new Ground(HEIGHT); // create new ground class
			ground->start(WIDTH, HEIGHT, draw->playerHeight(), lastX, lastY); //set ground postion to start
			groundVector.push_back(*ground); // add ground to vector
			delete ground; // delete ground from memory (it is already copied to vector)

			for (int j = 0; j != int((WIDTH / 300) + 15); j++){ // loop as many times as diffrent ground are needed
				ground = new Ground(HEIGHT); // create new ground
				ground->create(lastX, lastY, player->getSpeed()); // set position from last ground
				groundVector.push_back(*ground); // add ground to vector
				delete ground; // delete ground from memory (it is already copied to vector)
			}

			startTimer(0); // start timers (0 = speed, score and down timers
			break;
		}
		case(3):{ // ingame

			// If menu song is playing then stop it
			if(audio->isMenuPlaying())
				audio->stopLoopMenu();

			// If ingame song is not playing then start it
			if(!audio->isInGamePlaying())
				audio->loopInGame(Volume, Pan);

			// draw backround image
			draw->bg();

			// check if player has dropped to bottom
			if (player->getY() + draw->playerHeight() >= HEIGHT) {
				// set gamepos to 4 (end) and stop ingame song and play  end sound
				gamePos = 4;
				audio->stopLoopInGame();
				audio->death(Volume, Pan);
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