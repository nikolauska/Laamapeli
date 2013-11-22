#ifndef groundDEF
#define groundDEF
#include "Header.h"

class Ground{
	private:
		int x;
		int y;
	public:
		Ground(){ this->x = -1; this->y = -1;}
		~Ground(){}

		void start(); 
		void create(int, int);		
		void move(int);
		bool groundCheck(int, int);

		int getX();
		int getY();
		int getLenght();		
};

// Create ground for starting position
void Ground::start(){
	this->x = pStartX - pSize;
	this->y = pStartY + pSize;
}

// Create ground on the run
void Ground::create(int lastX, int lastY){
	srand(time(NULL));
		
	if (lastY == gPosY1)
		this->y = gPosY2;
	else if (lastY == gPosY4)
		this->y = gPosY3;
	else
		if (((int)rand() % 1 ) == 1)
			if (lastY == gPosY2)
				this->y = gPosY1;
			else 
				this->y = gPosY2;
		else
			if (lastY == gPosY2)
				this->y = gPosY3;
			else
				this->y = gPosY4;

	this->x = lastX + 600 + (rand() % 200 + 100);
}

// Move ground to left
void Ground::move(int speed){
	this->x -= speed;
}


// Check if player is on ground
bool Ground::groundCheck(int pX, int pY){
	bool levelY = false;
	bool levelX = false;

	if (pY + pSize == this->y) // check if player is in same level to ground
		levelY = true; 
	if (pX + pSize <= this->x && pX - pSize >= this->x) // Check if player is in line
		levelX = true;

	if (levelY && levelX)
		return true;

	return false;
}

// Get variables
int Ground::getX(){return this->x;}
int Ground::getY(){return this->y;}

#endif