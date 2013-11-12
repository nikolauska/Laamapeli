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
	public:
		Player(){}
		~Player(){}

		void start();

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

		void drawPlayer();
		void moveUp();
		void moveDown();
};

// Player start values
void Player::start(){
	this->onGround = true;
	this->jump = false;
	this->x = pStartX; 
	this->y = pStartY; 
	this->speed = startSpeed; 
	this->score = 0;
}

// Draw player function
void Player::drawPlayer(){
	int x1 = this->x - pSize;
	int y1 = this->y - pSize;

	int x2 = this->x + pSize;
	int y2 = this->y + pSize;

	ALLEGRO_BITMAP *lamapic = al_load_bitmap("lamapic.png");

	al_draw_bitmap(lamapic, this->x, this->y, NULL);
	//al_draw_filled_rectangle(ship.x, ship.y + 9, ship.x + 10, ship.y + 7, al_map_rgb(255, 0, 0));

	//al_draw_filled_triangle(ship.x - 12, ship.y - 17, ship.x +12, ship.y, ship.x - 12, ship.y + 17, al_map_rgb(0, 255, 0));
	//al_draw_filled_rectangle(ship.x - 12, ship.y - 2, ship.x +15, ship.y + 2, al_map_rgb(0, 0, 255));

	al_destroy_bitmap(lamapic);
}

// Get/Set player ground value
void Player::setGround(bool onGround){ this->onGround = onGround; }
bool Player::getGround(){ return this->onGround; }

// Get/Set player jump value
void Player::setJump(bool onJump){ this->jump = onJump; }
bool Player::getJump(){ return this->jump; }

// Move player up and down for jumping
void Player::moveUp(){this->y -= pMove;}
void Player::moveDown(){this->y += pMove;}

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