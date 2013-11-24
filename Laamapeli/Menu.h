#include "Header.h"

class Menu{
	private: 
		bool animating;

		int playY;
		int settingsY;
		int quitY;

		int playX;
		int settingsX;
		int quitX;
	public:
		Menu();
		~Menu(){}

		void animateUp();
		void animateDown();
		void animateGraphics();
		void animateAudio();
		bool animateBack();
		void setAnimState(bool anim){this->animating = anim;}

		int getPlayY(){return this->playY;}
		int getSettingsY(){return this->settingsY;}
		int getQuitY(){return this->quitY;}

		int getPlayX(){return this->playX;}
		int getSettingsX(){return this->settingsX;}
		int getQuitX(){return this->quitX;}
};

Menu::Menu(){
	this->animating = false; 
	this->playY = menuPlayGamePosY; 
	this->settingsY = menuSettingsPosY; 
	this->quitY = menuExitPosY;

	this->playX = menuPlayGamePosX; 
	this->settingsX = menuSettingsPosX; 
	this->quitX = menuExitPosX;
}

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
			this->playY += menuSpeed; 
			this->settingsY += menuSpeed; 
			this->quitY += menuSpeed;		
		}
	}
}

void Menu::animateAudio(){
	if(this->animating == true){
		if((this->playX - WIDTH) >= menuPlayGamePosX ){
			this->playX = menuPlayGamePosX - WIDTH;
			this->settingsX = menuSettingsPosX - WIDTH;
			this->quitX = menuExitPosX - WIDTH;

			this->animating = false;
		} else {
			this->playX += menuSpeed;
			this->settingsX += menuSpeed;
			this->quitX += menuSpeed;
		}
	}
}

void Menu::animateGraphics(){
	if(this->animating == true){
		if((this->playX + WIDTH) <= menuPlayGamePosX ){
			this->playX = menuPlayGamePosX + WIDTH;
			this->settingsX = menuSettingsPosX + WIDTH;
			this->quitX = menuExitPosX + WIDTH;

			this->animating = false;
		} else {
			this->playX -= menuSpeed;
			this->settingsX -= menuSpeed;
			this->quitX -= menuSpeed;
		}
	}
}

bool Menu::animateBack(){
	if(this->animating == true && this->playX != menuPlayGamePosX){
		if(this->playX >= menuPlayGamePosX){
			this->playX -= menuSpeed;
			this->settingsX -= menuSpeed;
			this->quitX -= menuSpeed;
			
			if(this->playX <= menuPlayGamePosX){
				this->playX = menuPlayGamePosX;
				this->settingsX = menuSettingsPosX;
				this->quitX = menuExitPosX;

				this->animating = false;				
			}
			return false;
			
		} else if(this->playX <= menuPlayGamePosX){
			this->playX += menuSpeed;
			this->settingsX += menuSpeed;
			this->quitX += menuSpeed;

			if(this->playX >= menuPlayGamePosX){
				this->playX = menuPlayGamePosX;
				this->settingsX = menuSettingsPosX;
				this->quitX = menuExitPosX;

				this->animating = false;				
			}
			return false;
		}
	}
	return true;
}