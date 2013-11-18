#ifndef groundDEF
#define groundDEF
#include "Header.h"

class Ground{
	private:
		int x;
		int y;
		int lenght;
	public:
		Ground(){ this->x = -1; this->y = -1; this->lenght = 0; }
		~Ground(){}

		void start(); 
		void create(int, int, int);		
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
	this->lenght = 300;
}

// Create ground on the run
void Ground::create(int lastX, int lastY, int lastLenght){
	srand(time(NULL));

	int tempY = 0;
	int tempX = 0;
	int tempLenght = 0;

		
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

	tempLenght = rand() % 300 + 100;
	tempX = lastX + lastLenght + tempLenght + (rand() % 50 + pSize);

	this->lenght = tempLenght;
	this->x = tempX;
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
	if (pX + pSize <= this->x - this->lenght && pX - pSize >= this->x + this->lenght) // Check if player is in line
		levelX = true;

	if (levelY && levelX)
		return true;

	return false;
}

// Get variables
int Ground::getX(){return this->x;}
int Ground::getY(){return this->y;}
int Ground::getLenght(){return this->lenght;}

#endif