#ifndef audioDEF
#define audioDEF



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

		void jump(float, float);
		void death(float, float);

		void loopMenu(float, float);
		void stopLoopMenu();
		bool isMenuPlaying();

		void loopInGame(float, float);		
		void stopLoopInGame();
		bool isInGamePlaying();

		ALLEGRO_SAMPLE *menuSong;
		ALLEGRO_SAMPLE *inGameSong;
		ALLEGRO_SAMPLE *njak;
		ALLEGRO_SAMPLE *die;
		ALLEGRO_SAMPLE_ID MenuMusic;
		ALLEGRO_SAMPLE_ID InGameMusic;
};

inline Audio::Audio(){
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

inline void Audio::jump(float Volume, float Pan){al_play_sample(njak, (Volume/100) +  0.2, Pan, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);}

inline void Audio::death(float Volume, float Pan){al_play_sample(die, (Volume/100) + 0.2, Pan, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);}

inline void Audio::loopMenu(float Volume, float Pan){al_play_sample(menuSong, Volume/100, Pan, 1.0, ALLEGRO_PLAYMODE_LOOP, &MenuMusic); this->menuPlaying = true;}
inline void Audio::stopLoopMenu(){al_stop_sample(&MenuMusic); this->menuPlaying = false;}
inline bool Audio::isMenuPlaying(){return this->menuPlaying;}

inline void Audio::loopInGame(float Volume, float Pan){al_play_sample(inGameSong, (Volume/100) - 0.1, Pan, 1.0, ALLEGRO_PLAYMODE_LOOP, &InGameMusic); this->InGamePlaying = true;}
inline void Audio::stopLoopInGame(){al_stop_sample(&InGameMusic); this->InGamePlaying = false;}
inline bool Audio::isInGamePlaying(){return this->InGamePlaying;}

#endif