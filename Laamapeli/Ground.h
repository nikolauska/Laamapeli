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
#endif