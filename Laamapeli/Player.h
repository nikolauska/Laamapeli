#ifndef playerDEF
#define playerDEF

class Player{
	private:
		bool onGround;
		int x;
		float y;
		float previousY;
		float verticalSpeed;
		int speed;
		int score;
	public:
		Player(){}
		~Player(){}

		void start(int, int, int);

		void setGround(bool);
		bool jump(float);
		void update(float, float);
		bool isFalling();
		void land(int);

		void addSpeed();
		int getSpeed();

		void addScore();
		void resetScore();
		int getScore();

		int getX();
		int getY();
		int getPreviousY();
};

#endif