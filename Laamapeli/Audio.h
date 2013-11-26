#ifndef audioDEF
#define audioDEF
#include "Header.h"

ALLEGRO_SAMPLE *menuSong;
ALLEGRO_SAMPLE *inGameSong;
ALLEGRO_SAMPLE *njak;
ALLEGRO_SAMPLE *die;
ALLEGRO_SAMPLE_ID MenuMusic;
ALLEGRO_SAMPLE_ID InGameMusic;

class Audio{
	private:
		bool menuPlaying;
		bool InGamePlaying;

	public:
		Audio();
		~Audio(){	al_destroy_sample(menuSong);
					al_destroy_sample(inGameSong);
					al_destroy_sample(njak);
					al_destroy_sample(die);
				}

		void jump();
		void death();

		void loopMenu();
		void stopLoopMenu();
		bool isMenuPlaying();

		void loopInGame();		
		void stopLoopInGame();
		bool isInGamePlaying();
};

Audio::Audio(){
	al_install_audio();
	al_init_acodec_addon();

	menuSong = al_load_sample("Data\\Audio\\ambient.ogg");
	inGameSong = al_load_sample("Data\\Audio\\llama_song.ogg");
	njak = al_load_sample("Data\\Audio\\njak.ogg");
	die = al_load_sample("Data\\Audio\\llama_is_kill.ogg");
	al_reserve_samples(4);

	this->menuPlaying = false;
	this->InGamePlaying = false;
}

void Audio::jump(){al_play_sample(njak, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);}

void Audio::death(){al_play_sample(die, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);}

void Audio::loopMenu(){al_play_sample(menuSong, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &MenuMusic); this->menuPlaying = true;}
void Audio::stopLoopMenu(){al_stop_sample(&MenuMusic); this->menuPlaying = false;}
bool Audio::isMenuPlaying(){return this->menuPlaying;}

void Audio::loopInGame(){al_play_sample(inGameSong, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &InGameMusic); this->InGamePlaying = true;}
void Audio::stopLoopInGame(){al_stop_sample(&InGameMusic); this->InGamePlaying = false;}
bool Audio::isInGamePlaying(){return this->InGamePlaying;}

#endif