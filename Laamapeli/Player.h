#ifndef playerDEF
#define playerDEF

class Player{
	private:
		bool onGround;
		bool jump;
		int x;
		int y;
		int speed;
		int score;
		int move;
	public:
		Player(){}
		~Player(){}

		void start(int, int, int);

		void setGround(bool);
		bool getGround();

		void addSpeed();
		int getSpeed();

		void addScore();
		void resetScore();
		int getScore();

		int getX();
		int getY();

		void moveUp();
		void moveDown();
};

#endif