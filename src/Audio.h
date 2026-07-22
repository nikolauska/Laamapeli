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
#endif