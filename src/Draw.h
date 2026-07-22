#ifndef drawDEF
#define drawDEF

class Draw{
	private:
		int WIDTH;
		int HEIGHT;
		int groundW;
		int groundH;
		int playerW;
		int playerH;
		int menubgW;
		int menubgH;
		int ingamebgW;
		int ingamebgH;
		int endbgW;
		int endbgH;
		int selectorW;
		int selectorH;

	public:
		Draw(int, int, string);
		~Draw();

		void player(int, int); 
		void ground(int, int);
		void bg();

		void endText(int);
		void gameText(int, int);

		void menu(int, int, int, int, int, int, float);

		int playerHeight(){return this->playerH;}
		int playerWidth(){return this->playerW;}

		ALLEGRO_FONT *font18, *font42;
		ALLEGRO_BITMAP *playerpic, *groundpic, *ingamebg, *menubg, *endbg, *msel;
};

#endif