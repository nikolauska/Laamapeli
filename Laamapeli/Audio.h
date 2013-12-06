#ifndef audioDEF
#define audioDEF


class Audio{
	private:
		bool menuPlaying;
		bool InGamePlaying;

	public:
		Audio(string);
		~Audio(){	al_destroy_sample(menuSong);
					al_destroy_sample(inGameSong);
					al_destroy_sample(jumpSound);
					al_destroy_sample(endSound);
				}

		void jump(float, float);
		void death(float, float);

		void loopMenu(float, float);
		void stopLoopMenu();
		bool isMenuPlaying();

		void loopInGame(float, float);		
		void stopLoopInGame();
		bool isInGamePlaying();

		ALLEGRO_SAMPLE *menuSong, *inGameSong, *jumpSound, *endSound;
		ALLEGRO_SAMPLE_ID MenuMusic, InGameMusic;
};

inline Audio::Audio(string folder){
	al_install_audio();
	al_init_acodec_addon();

	string temp = folder + "/Audio/menu.ogg";
	if(!(menuSong = al_load_sample(temp.c_str())))
		throw "Menusong not found! \nWe suggest to check if filename is correct in 'Audio' folder. \nFilename for this file is 'menu.ogg'";

	temp = folder + "/Audio/ingame.ogg";
	if(!(inGameSong = al_load_sample(temp.c_str())))
		throw "Ingamesong not found! \nWe suggest to check if filename is correct in 'Audio' folder. \nFilename for this file is 'ingame.ogg'";

	temp = folder + "/Audio/jump.ogg";
	if(!(jumpSound = al_load_sample(temp.c_str())))
		throw "Jumpsound not found! \nWe suggest to check if filename is correct in 'Audio' folder. \nFilename for this file is 'jump.ogg'";

	temp = folder + "/Audio/end.ogg";
	if(!(endSound = al_load_sample(temp.c_str())))
		throw "Endsound not found! \nWe suggest to check if filename is correct in 'Audio' folder. \nFilename for this file is 'end.ogg'";

	al_reserve_samples(4);

	this->menuPlaying = false;
	this->InGamePlaying = false;
}

inline void Audio::jump(float Volume, float Pan){al_play_sample(jumpSound, (Volume/100) +  0.2, Pan, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);}

inline void Audio::death(float Volume, float Pan){al_play_sample(endSound, (Volume/100) + 0.2, Pan, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);}

inline void Audio::loopMenu(float Volume, float Pan){al_play_sample(menuSong, Volume/100, Pan, 1.0, ALLEGRO_PLAYMODE_LOOP, &MenuMusic); this->menuPlaying = true;}
inline void Audio::stopLoopMenu(){al_stop_sample(&MenuMusic); this->menuPlaying = false;}
inline bool Audio::isMenuPlaying(){return this->menuPlaying;}

inline void Audio::loopInGame(float Volume, float Pan){al_play_sample(inGameSong, (Volume/100) - 0.1, Pan, 1.0, ALLEGRO_PLAYMODE_LOOP, &InGameMusic); this->InGamePlaying = true;}
inline void Audio::stopLoopInGame(){al_stop_sample(&InGameMusic); this->InGamePlaying = false;}
inline bool Audio::isInGamePlaying(){return this->InGamePlaying;}

#endif