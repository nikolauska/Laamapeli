#include "Player.h"

// Player start values
void Player::start(int startSpeed, int W, int H) {
  this->onGround = true;
  this->speed = startSpeed;
  this->score = 0;
  this->x = W / 8;
  this->y = H / 2;
  this->previousY = this->y;
  this->verticalSpeed = 0;
}

// Set player ground value
void Player::setGround(bool onGround) { this->onGround = onGround; }

// Update vertical movement
bool Player::jump(float speed) {
  if (!this->onGround)
    return false;

  this->verticalSpeed = -speed;
  this->onGround = false;
  return true;
}

void Player::update(float gravity, float seconds) {
  this->previousY = this->y;
  if (!this->onGround) {
    this->verticalSpeed += gravity * seconds;
    this->y += this->verticalSpeed * seconds;
  }
}

bool Player::isFalling() { return this->verticalSpeed >= 0; }

void Player::land(int y) {
  this->y = y;
  this->previousY = y;
  this->verticalSpeed = 0;
  this->onGround = true;
}

// Get player position
int Player::getX() { return this->x; }
int Player::getY() { return this->y; }
int Player::getPreviousY() { return this->previousY; }

// Add\Get player speed
void Player::addSpeed() { this->speed += 1; }
int Player::getSpeed() { return this->speed; }

// Add\Get player score
void Player::addScore() { this->score += 1; }
void Player::resetScore() { this->score = 0; }
int Player::getScore() { return this->score; }
