#include "Include.h"

// Player start values
void Player::start(int startSpeed, int W, int H){
	this->onGround = true;
	this->jump = false;
	this->speed = startSpeed; 
	this->score = 0;
	this->move = 6;
	this->x = W/8;
	this->y = H/2;
}

// Get/Set player ground value
void Player::setGround(bool onGround){ this->onGround = onGround; }
bool Player::getGround(){ return this->onGround; }

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
