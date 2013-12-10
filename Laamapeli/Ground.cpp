#include "Include.h"

// Create ground for starting position
void Ground::start(int WIDTH, int HEIGHT, int pic, int &lastX, int &lastY){
	// Set starting ground to player position
	this->x = (WIDTH / 8) + pic;	
	this->y = (HEIGHT / 2) + pic;	

	// Save position to lastY and lastX
	lastX = this->x;
	lastY = this->y;
}

// Create ground on the run
void Ground::create(int &lastX, int &lastY, int speed){	
	int gPosY1 = (this->Height / 12) * 2;					// Ground Y position 1
	int gPosY2 = (this->Height / 12) * 4;					// Ground Y position 2
	int gPosY3 = (this->Height / 12) * 6;					// Ground Y position 3
	int gPosY4 = (this->Height / 12) * 8;					// Ground Y position 4


	// this next confusing function will make sure player will not have impossible jump

	if (lastY == gPosY1)									// Check if lastY equals gound positon 1
		this->y = gPosY2;									// Then Y will be position 2
	else if (lastY == gPosY4)								// Check if lastY equals gound positon 4
		this->y = gPosY3;									// Then Y will be positon 3
	else													// Else we will randomize
		if (int((rand() % 2 + 1 )) == 1)					// if rand 1-2 equals to 1
			if (lastY == gPosY2)							// If last position is position 2 
				this->y = gPosY1;							// Then Y will be position 1 
			else 
				this->y = gPosY2;							// Else Y will be position 2
		else												// If rand is not 1
			if (lastY == gPosY2)							// If lastY was position 2 
				this->y = gPosY3;							// Then Y will be postion 3
			else
				this->y = gPosY4;							// Else Y will be position 4

	this->x = lastX + int((rand() % 100 + 1)) - speed;		// Set random X postion

	lastX = this->x;										// Save newly given X value to lastX
	lastY = this->y;										// Save newly given Y value to lastY
}

// Move ground to left
void Ground::move(int speed){
	this->x -= speed;
}

// Get variables
int Ground::getX(){return this->x;}
int Ground::getY(){return this->y;}
