#ifndef drawDEF
#define drawDEF
#include "Header.h"

ALLEGRO_FONT *font18 = NULL;
ALLEGRO_FONT *font42 = NULL;
ALLEGRO_BITMAP *lamapic = NULL;
ALLEGRO_BITMAP *groundpic = NULL;
ALLEGRO_BITMAP *bg1080 = NULL;
ALLEGRO_BITMAP *menubg1080 = NULL;
ALLEGRO_BITMAP *endbg1080 = NULL;
ALLEGRO_BITMAP *msel = NULL;

class Draw{
	private:
		int pW;
		int sW;
		int qW;

		int gW;
		int aW;
		int bW;

		int rW;
		int dW;

		int vW;
		int mW;

	public:
		Draw();
		~Draw();

		void player(int, int); 
		void ground(int, int);
		void bg();


		void endText(int);
		void gameText(int, int);

		void mainMenu(int, int, int, int, int, int);

		void selectorsMain(int);
		void selectorsSettings(int);
		void selectorsGraphics(int);
		void selectorsAudio(int);

		int picHeight(){return al_get_bitmap_height(lamapic);}
		int picWidth(){return al_get_bitmap_width(lamapic);}
};


Draw::Draw(){
	al_init_font_addon(); 
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_init_image_addon();
	
	font18 = al_load_font("blood.ttf", 24, 0);
	font42 = al_load_font("blood.ttf", 42, 0);

	//Initializing pictures
	lamapic = al_load_bitmap("Data/Pictures/lamapic.png");
	groundpic = al_load_bitmap("Data/Pictures/ground.png");
	bg1080 = al_load_bitmap("Data/Pictures/bg1080.png");
	menubg1080 = al_load_bitmap("Data/Pictures/menubg1080.png");
	endbg1080 = al_load_bitmap("Data/Pictures/endbg1080.png");
	msel = al_load_bitmap("Data/Pictures/selection.png");

	this->pW = al_get_text_width(font18,"Play Game");
	this->sW = al_get_text_width(font18,"Settings");
	this->qW = al_get_text_width(font18,"Quit");

	this->gW = al_get_text_width(font18,"Graphics");
	this->aW = al_get_text_width(font18,"Audio");
	this->bW = al_get_text_width(font18,"Back");

	string temp = "Resolution: ";
	temp += to_string(WIDTH) + " X " + to_string(HEIGHT);
	this->rW = al_get_text_width(font18, temp.c_str());

	temp = "Display: ";
	temp += "FullScreen";
	this->dW = al_get_text_width(font18,temp.c_str());

	temp = "Volume: ";
	temp += "100";
	this->vW = al_get_text_width(font18,temp.c_str());

	temp = "Mute: ";
	temp += "No";
	this->mW = al_get_text_width(font18,temp.c_str());
}

void Draw::player(int x, int y){
	al_draw_bitmap(lamapic, x, y, NULL);
}

void Draw::ground(int x, int y){
	int x1 = x - 100;
	int y1 = y;

	int x2 = x + 100;
	int y2 = y;

	al_draw_bitmap(groundpic, x, y, NULL);
}



void Draw::bg(){
	//bitmap, source x, source y, source width, source height, destination x, destination y, destination width, destination height, flags
	al_draw_scaled_bitmap(bg1080, 0, 0, 1920, 1080, 0, 0, WIDTH, HEIGHT, NULL);
}

void Draw::endText(int score){
	al_draw_scaled_bitmap(endbg1080, 0, 0, 1920, 1080, 0, 0, WIDTH, HEIGHT, NULL);

	al_draw_textf(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Game Over. Final Score: %i", score);
}

void Draw::gameText(int score, int speed){
	al_draw_textf(font18, al_map_rgb(255, 0, 0), 5, 10, 0, "Score: %i", score);
	al_draw_textf(font18, al_map_rgb(255, 0, 0), 5, 40, 0, "Speed: %i", speed);
}

void Draw::mainMenu(int playY, int settingsY, int quitY, int playX, int settingsX, int quitX){
	al_draw_scaled_bitmap(menubg1080, 0, 0, 1920, 1080, 0, 0, WIDTH, HEIGHT, NULL);

	al_draw_text(font18, al_map_rgb(255, 0, 0), playX, playY, ALLEGRO_ALIGN_CENTER, "Play game");
	al_draw_text(font18, al_map_rgb(255, 0, 0), settingsX, settingsY, ALLEGRO_ALIGN_CENTER, "Settings");
	al_draw_text(font18, al_map_rgb(255, 0, 0), quitX, quitY, ALLEGRO_ALIGN_CENTER, "Quit");

	al_draw_text(font18, al_map_rgb(255, 0, 0), playX, playY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Graphics");
	al_draw_text(font18, al_map_rgb(255, 0, 0), settingsX, settingsY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Audio");
	al_draw_text(font18, al_map_rgb(255, 0, 0), quitX, quitY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Back");

	al_draw_textf(font18, al_map_rgb(255, 0, 0), playX + WIDTH, playY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Resolution : %i X %i", WIDTH, HEIGHT);
	al_draw_textf(font18, al_map_rgb(255, 0, 0), settingsX + WIDTH, settingsY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Display: Fullscreen");
	al_draw_text(font18, al_map_rgb(255, 0, 0), quitX + WIDTH, quitY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Back");

	al_draw_textf(font18, al_map_rgb(255, 0, 0), playX - WIDTH, playY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Volume: %i", 100);
	al_draw_textf(font18, al_map_rgb(255, 0, 0), settingsX - WIDTH, settingsY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Mute: No");
	al_draw_text(font18, al_map_rgb(255, 0, 0), quitX - WIDTH, quitY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Back");
}

void Draw::selectorsMain(int selection){
	switch(selection){
		case(1):{
			al_draw_bitmap(msel, (WIDTH/2) + (this->pW/2), menuPlayGamePosY -14, NULL);
			al_draw_bitmap(msel, (WIDTH/2) - (this->pW/2) - (picWidth()/2.7), menuPlayGamePosY -14, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
		case(2):{
			al_draw_bitmap(msel, (WIDTH/2) + (this->sW/2), menuSettingsPosY -14, NULL);
			al_draw_bitmap(msel, (WIDTH/2) - (this->sW/2) - (picWidth()/2.7), menuSettingsPosY -14, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
		case(3):{
			al_draw_bitmap(msel, (WIDTH/2) + (this->qW/2), menuExitPosY -14, NULL);
			al_draw_bitmap(msel, (WIDTH/2) - (this->qW/2) - (picWidth()/2.7), menuExitPosY -14, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
	}
}
void Draw::selectorsSettings(int selection){
	switch(selection){
		case(1):{
			al_draw_bitmap(msel, (WIDTH/2) + (this->gW/2), menuPlayGamePosY -14, NULL);
			al_draw_bitmap(msel, (WIDTH/2) - (this->gW/2) - (picWidth()/2.7), menuPlayGamePosY -14, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
		case(2):{
			al_draw_bitmap(msel, (WIDTH/2) + (this->aW/2), menuSettingsPosY -14, NULL);
			al_draw_bitmap(msel, (WIDTH/2) - (this->aW/2) - (picWidth()/2.7), menuSettingsPosY -14, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
		case(3):{
			al_draw_bitmap(msel, (WIDTH/2) + (this->bW/2), menuExitPosY -14, NULL);
			al_draw_bitmap(msel, (WIDTH/2) - (this->bW/2) - (picWidth()/2.7), menuExitPosY -14, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
	}
}
void Draw::selectorsGraphics(int selection){
	switch(selection){
		case(1):{
			al_draw_bitmap(msel, (WIDTH/2) + (this->rW/2), menuPlayGamePosY-14, NULL);
			al_draw_bitmap(msel, (WIDTH/2) - (this->rW/2) - (picWidth()/2.7), menuPlayGamePosY -14, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
		case(2):{
			al_draw_bitmap(msel, (WIDTH/2) + (this->dW/2), menuSettingsPosY -14, NULL);
			al_draw_bitmap(msel, (WIDTH/2) - (this->dW/2) - (picWidth()/2.7), menuSettingsPosY -14, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
		case(3):{
			al_draw_bitmap(msel, (WIDTH/2) + (this->bW/2), menuExitPosY -14, NULL);
			al_draw_bitmap(msel, (WIDTH/2) - (this->bW/2) - (picWidth()/2.7), menuExitPosY -14, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
	}
}
void Draw::selectorsAudio(int selection){
switch(selection){
		case(1):{
			al_draw_bitmap(msel, (WIDTH/2) + (this->vW/2), menuPlayGamePosY -14, NULL);
			al_draw_bitmap(msel, (WIDTH/2) - (this->vW/2) - (picWidth()/2.7), menuPlayGamePosY -14, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
		case(2):{
			al_draw_bitmap(msel, (WIDTH/2) + (this->mW/2), menuSettingsPosY -14, NULL);
			al_draw_bitmap(msel, (WIDTH/2) - (this->mW/2) - (picWidth()/2.7), menuSettingsPosY -14, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
		case(3):{
			al_draw_bitmap(msel, (WIDTH/2) + (this->bW/2), menuExitPosY -14, NULL);
			al_draw_bitmap(msel, (WIDTH/2) - (this->bW/2) - (picWidth()/2.7), menuExitPosY -14, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
	}
}

Draw::~Draw(){
	al_destroy_font(font18);
	al_destroy_font(font42);
	al_destroy_bitmap(lamapic);
	al_destroy_bitmap(groundpic);
	al_destroy_bitmap(bg1080);
	al_destroy_bitmap(menubg1080);
	al_destroy_bitmap(endbg1080);
	al_destroy_bitmap(msel);
}


#endif