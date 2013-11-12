#include "Header.h"

class Player{
	private:
		int ID;
		int x;
		int y;
		int speed;
		int score;
	public:
		Player(){this->ID = playerID; this->x = startX; this->y = startY; this->speed = startSpeed; this->score = startScore;}
		~Player(){}

		void setSpeed(int);
		int getSpeed();
		void setScore(int);
		int getScore();
		
		void drawPlayer();
};

void Player::drawPlayer(){
	int x1 = this->x - 5;
	int y1 = this->y + 5;

	int x2 = this->x + 5;
	int y2 = this->y - 5;

	al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(255, 0, 0));
	//al_draw_filled_rectangle(ship.x, ship.y + 9, ship.x + 10, ship.y + 7, al_map_rgb(255, 0, 0));

	//al_draw_filled_triangle(ship.x - 12, ship.y - 17, ship.x +12, ship.y, ship.x - 12, ship.y + 17, al_map_rgb(0, 255, 0));
	//al_draw_filled_rectangle(ship.x - 12, ship.y - 2, ship.x +15, ship.y + 2, al_map_rgb(0, 0, 255));
}

void Player::setSpeed(int speed){this->speed = speed;}
int Player::getSpeed(){return this->speed;}

void Player::setScore(int score){this->score = score;}
int Player::getScore(){return this->score;}