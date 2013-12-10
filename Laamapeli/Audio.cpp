#include "Include.h"

Audio::Audio(string folder){

	// Load menusong and return error if not found
	string temp = folder + "/Audio/menu.ogg";
	if(!(menuSong = al_load_sample(temp.c_str())))
		throw "Menusong not found! \nWe suggest to check if filename is correct in 'Audio' folder. \nFilename for this file is 'menu.ogg'";

	// Load inGamesong and return error if not found
	temp = folder + "/Audio/ingame.ogg";
	if(!(inGameSong = al_load_sample(temp.c_str())))
		throw "Ingamesong not found! \nWe suggest to check if filename is correct in 'Audio' folder. \nFilename for this file is 'ingame.ogg'";

	// Load jumpSound and return error if not found
	temp = folder + "/Audio/jump.ogg";
	if(!(jumpSound = al_load_sample(temp.c_str())))
		throw "Jumpsound not found! \nWe suggest to check if filename is correct in 'Audio' folder. \nFilename for this file is 'jump.ogg'";

	// Load endSound and return error if not found
	temp = folder + "/Audio/end.ogg";
	if(!(endSound = al_load_sample(temp.c_str())))
		throw "Endsound not found! \nWe suggest to check if filename is correct in 'Audio' folder. \nFilename for this file is 'end.ogg'";

	// Reserve sample to allegro
	al_reserve_samples(4);

	// Set loop song playing values to false
	this->menuPlaying = false;
	this->InGamePlaying = false;
}

// Play jump sound
void Audio::jump(float Volume, float Pan){al_play_sample(jumpSound, (Volume/100) +  0.2, Pan, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);}

// Play end sound
void Audio::death(float Volume, float Pan){al_play_sample(endSound, (Volume/100) + 0.2, Pan, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);}

// Start menu Song loop, stop it and return value to check if menu song is playing
void Audio::loopMenu(float Volume, float Pan){al_play_sample(menuSong, Volume/100, Pan, 1.0, ALLEGRO_PLAYMODE_LOOP, &MenuMusic); this->menuPlaying = true;}
void Audio::stopLoopMenu(){al_stop_sample(&MenuMusic); this->menuPlaying = false;}
bool Audio::isMenuPlaying(){return this->menuPlaying;}

// Start inGame Song loop, stop it and return value to check if inGame song is playing
void Audio::loopInGame(float Volume, float Pan){al_play_sample(inGameSong, (Volume/100) - 0.1, Pan, 1.0, ALLEGRO_PLAYMODE_LOOP, &InGameMusic); this->InGamePlaying = true;}
void Audio::stopLoopInGame(){al_stop_sample(&InGameMusic); this->InGamePlaying = false;}
bool Audio::isInGamePlaying(){return this->InGamePlaying;}
