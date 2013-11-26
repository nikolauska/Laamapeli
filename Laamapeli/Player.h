#ifndef playerDEF
#define playerDEF
#include "Header.h"

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
		Player(int WIDTH, int HEIGHT): x(WIDTH / 8), y(HEIGHT / 2){}
		~Player(){}

		void start(int);

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
void Player::start(int startSpeed){
	this->onGround = true;
	this->jump = false;
	this->speed = startSpeed; 
	this->score = 0;
	this->move = 6;
}

// Get/Set player ground value
void Player::setGround(bool onGround){ this->onGround = onGround; }
bool Player::getGround(){ return this->onGround; }

// Get/Set player jump value
void Player::setJump(bool onJump){ this->jump = onJump; }
bool Player::getJump(){ return this->jump; }

// Move player up and down for jumping
void Player::moveUp(){this->y -= this->move;}
void Player::moveDown(){this->y += this->move;}

// Get player position
int Player::getX(){ return this->x; }
int Player::getY(){ return this->y; }

// Add\Get player speed
void Player::addSpeed(){this->speed += 1;}
int Player::getSpeed(){return this->speed;}

// Add\Get player score
void Player::addScore(){this->score += 1;}
void Player::resetScore(){ this->score = 0; }
int Player::getScore(){return this->score;}

#endif