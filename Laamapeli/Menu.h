#include "Header.h"

class Menu{
	private: 
		bool animating;

		int playY;
		int settingsY;
		int quitY;

		int graphicsY;
		int audioY;
		int backY;
	public:
		Menu(){this->animating = false; this->playY = menuPlayGamePosY; this->settingsY = menuSettingsPosY; this->quitY = menuExitPosY;}
		~Menu(){}

		void animateUp();
		void animateDown();
		void setAnimState(bool anim){this->animating = anim;}

		int getPlayY(){return this->playY;}
		int getSettingsY(){return this->settingsY;}
		int getQuitY(){return this->quitY;}
};

void Menu::animateUp(){
	if(this->animating == true){
		if((this->playY + HEIGHT) <= menuPlayGamePosY){
			this->playY = menuPlayGamePosY - HEIGHT;
			this->settingsY = menuSettingsPosY - HEIGHT;
			this->quitY = menuExitPosY - HEIGHT;

			this->animating = false;
		} else {
			this->playY -= menuSpeed;
			this->settingsY -= menuSpeed;
			this->quitY -= menuSpeed;
		}
	}
}

void Menu::animateDown(){
	if(this->animating == true){
		if(this->playY >= menuPlayGamePosY){
			this->playY = menuPlayGamePosY;
			this->settingsY = menuSettingsPosY;
			this->quitY = menuExitPosY;

			this->animating = false;
		} else {
			this->graphicsY += menuSpeed; 
			this->audioY += menuSpeed; 
			this->backY += menuSpeed;		
		}
	}
}