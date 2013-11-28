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

		void setJump(bool);
		bool getJump();

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


// Player start values
inline void Player::start(int startSpeed, int W, int H){
	this->onGround = true;
	this->jump = false;
	this->speed = startSpeed; 
	this->score = 0;
	this->move = 6;
	this->x = W/8;
	this->y = H/2;
}

// Get/Set player ground value
inline void Player::setGround(bool onGround){ this->onGround = onGround; }
inline bool Player::getGround(){ return this->onGround; }

// Get/Set player jump value
inline void Player::setJump(bool onJump){ this->jump = onJump; }
inline bool Player::getJump(){ return this->jump; }

// Move player up and down for jumping
inline void Player::moveUp(){this->y -= this->move;}
inline void Player::moveDown(){this->y += this->move;}

// Get player position
inline int Player::getX(){ return this->x; }
inline int Player::getY(){ return this->y; }

// Add\Get player speed
inline void Player::addSpeed(){this->speed += 1;}
inline int Player::getSpeed(){return this->speed;}

// Add\Get player score
inline void Player::addScore(){this->score += 1;}
inline void Player::resetScore(){ this->score = 0; }
inline int Player::getScore(){return this->score;}

#endif