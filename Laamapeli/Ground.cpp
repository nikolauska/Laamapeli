class Ground{
	private:
		int ID;
		int x;
		int y;
		int Lenght;
	public:
		Ground(){}
		~Ground(){}
		
		void create();

		int getX();
		int getY();
		int getLenght();
};

void Ground::create(){

}

int Ground::getX(){return this->x;}
int Ground::getY(){return this->y;}
int Ground::getLenght(){return this->Lenght;}