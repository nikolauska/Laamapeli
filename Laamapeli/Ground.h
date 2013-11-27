#ifndef groundDEF
#define groundDEF

class Ground{
	private:
		int x;
		int y;
		int Height;

	public:
		Ground(int HEIGHT):Height(HEIGHT){ this->x = -1; this->y = -1;}
		~Ground(){}

		void start(int, int, int); 
		void create(int, int);		
		void move(int);
		bool groundCheck(int, int);

		int getX();
		int getY();
		int getLenght();		
};


// Create ground for starting position
inline void Ground::start(int WIDTH, int HEIGHT, int pic){
	this->x = (WIDTH / 8) - pic;
	this->y = (HEIGHT / 2) + pic;
}

// Create ground on the run
inline void Ground::create(int lastX, int lastY){
	srand(time(NULL));
	
	int gPosY1 = (this->Height / 10) * 2; // Ground Y position 1
	int gPosY2 = (this->Height / 10) * 4; // Ground Y position 2
	int gPosY3 = (this->Height / 10) * 6; // Ground Y position 3
	int gPosY4 = (this->Height / 10) * 8; // Ground Y position 4


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
inline void Ground::move(int speed){
	this->x -= speed;
}


// Check if player is on ground
inline bool Ground::groundCheck(int pX, int pY){
//	bool levelY = false;
//	bool levelX = false;
//
//	if (pY + pSize == this->y) // check if player is in same level to ground
//		levelY = true; 
//	if (pX + pSize <= this->x && pX - pSize >= this->x) // Check if player is in line
//		levelX = true;
//
//	if (levelY && levelX)
//		return true;
//
	return true;
}

// Get variables
inline int Ground::getX(){return this->x;}
inline int Ground::getY(){return this->y;}

#endif