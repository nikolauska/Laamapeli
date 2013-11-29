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

		void start(int, int, int, int&, int&); 
		void create(int&, int&, int);		
		void move(int);

		int getX();
		int getY();
		int getLenght();	

};


// Create ground for starting position
inline void Ground::start(int WIDTH, int HEIGHT, int pic, int &lastX, int &lastY){
	this->x = (WIDTH / 8) + pic;
	this->y = (HEIGHT / 2) + pic;

	lastX = this->x;
	lastY = this->y;
}

// Create ground on the run
inline void Ground::create(int &lastX, int &lastY, int speed){
	srand(time(NULL));
	
	int gPosY1 = (this->Height / 12) * 2; // Ground Y position 1
	int gPosY2 = (this->Height / 12) * 4; // Ground Y position 2
	int gPosY3 = (this->Height / 12) * 6; // Ground Y position 3
	int gPosY4 = (this->Height / 12) * 8; // Ground Y position 4


	if (lastY == gPosY1)
		this->y = gPosY2;
	else if (lastY == gPosY4)
		this->y = gPosY3;
	else
		if (int((rand() % 2 + 1 )) == 1)
			if (lastY == gPosY2)
				this->y = gPosY1;
			else 
				this->y = gPosY2;
		else
			if (lastY == gPosY2)
				this->y = gPosY3;
			else
				this->y = gPosY4;

	this->x = lastX + int((rand() % 100 + 1)) - speed;

	lastX = this->x;
	lastY = this->y;
}

// Move ground to left
inline void Ground::move(int speed){
	this->x -= speed;
}


// Get variables
inline int Ground::getX(){return this->x;}
inline int Ground::getY(){return this->y;}

#endif