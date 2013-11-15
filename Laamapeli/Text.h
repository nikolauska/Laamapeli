#ifndef menuDEF
#define menuDEF
#include "Header.h"




class Text{
	private:
		int size1;
		int size2;
		int size3;

	public:
		Text();
		~Text(){}

		void animateUp(int);
		void animateDown(int);

		int getSize1(){return this->size1;}
		int getSize2(){return this->size2;}
		int getSize3(){return this->size3;}
};

Text::Text(){
	this->size1 = 0; 
	this->size2 = 0; 
	this->size3 = 0;
}


void Text::animateUp(int menuNum) {	
	if(menuNum == 1) {
		if(this->size1 != 3)
			this->size1 += 1;
	} else if (menuNum == 2){
		if(this->size2 != 3)
			this->size2 += 1;
	} else if (menuNum == 3){
		if(this->size3 != 3)
			this->size3 += 1;
	}
}

void Text::animateDown(int menuNum) {
	if(menuNum == 1) {
		if(this->size1 != 0)
			this->size1 -= 1;
	} else if (menuNum == 2){
		if(this->size2 != 0)
			this->size2 -= 1;
	} else if (menuNum == 3){
		if(this->size3 != 0)
			this->size3 -= 1;
	}
}

#endif