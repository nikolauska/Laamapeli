#include "Include.h"

Draw::Draw(int HEIGHT, int WIDTH, string folder){
	string temp = folder + "/Font/font.ttf";
	font18 = al_load_font(temp.c_str(), 24, 0);
	font42 = al_load_font(temp.c_str(), 42, 0);

	//Initializing pictures
	temp = folder + "/Pictures/player.png";
	if(!(playerpic = al_load_bitmap(temp.c_str())))
		throw "Picture for player not found! \nWe suggest to check if filename is correct in 'Pictures' folder. \nFilename for this file is 'player.png'";

	temp = folder + "/Pictures/ground.png";
	if(!(groundpic = al_load_bitmap(temp.c_str())))
		throw "Picture for ground not found! \nWe suggest to check if filename is correct in 'Pictures' folder. \nFilename for this file is 'ground.png'";

	temp = folder + "/Pictures/ingame.png";
	if(!(ingamebg = al_load_bitmap(temp.c_str())))
		throw "Backround for ingame not found! \nWe suggest to check if filename is correct in 'Pictures' folder. \nFilename for this file is 'ingame.png'";

	temp = folder + "/Pictures/menu.png";
	if(!(menubg = al_load_bitmap(temp.c_str())))
		throw "Backround for menu not found! \nWe suggest to check if filename is correct in 'Pictures' folder. \nFilename for this file is 'menu.png'";

	temp = folder + "/Pictures/end.png";
	if(!(endbg = al_load_bitmap(temp.c_str())))
		throw "Backround for endscreen not found! \nWe suggest to check if filename is correct in 'Pictures' folder. \nFilename for this file is 'end.png'";

	temp = folder + "/Pictures/selection.png";
	if(!(msel = al_load_bitmap(temp.c_str())))
		throw "Picture for menuselectors not found! \nWe suggest to check if filename is correct in 'Pictures' folder. \nFilename for this file is 'selection.png'";

	this->HEIGHT = HEIGHT;
	this->WIDTH = WIDTH;
	this->groundW = al_get_bitmap_width(groundpic);
	this->groundH = al_get_bitmap_height(groundpic);
	this->playerW = al_get_bitmap_width(playerpic);
	this->playerH = al_get_bitmap_height(playerpic);
	this->menubgW = al_get_bitmap_width(menubg);
	this->menubgH = al_get_bitmap_height(menubg);
	this->ingamebgW = al_get_bitmap_width(ingamebg);
	this->ingamebgH = al_get_bitmap_height(ingamebg);
	this->endbgW = al_get_bitmap_width(endbg);
	this->endbgH = al_get_bitmap_height(endbg);
	this->selectorW = al_get_bitmap_width(msel);
	this->selectorH = al_get_bitmap_height(msel);
}

void Draw::player(int x, int y){
	al_draw_scaled_bitmap(playerpic, 0, 0, this->playerW, this->playerH, x, y, 120, 120, NULL);
}

void Draw::ground(int x, int y){
	al_draw_scaled_bitmap(groundpic, 0, 0, this->groundW, this->groundH, x, y, 300, 30, NULL);
}



void Draw::bg(){
	//bitmap, source x, source y, source width, source height, destination x, destination y, destination width, destination height, flags
	al_draw_scaled_bitmap(ingamebg, 0, 0, this->ingamebgW, this->ingamebgH, 0, 0, this->WIDTH, this->HEIGHT, NULL);
}

void Draw::endText(int score){
	al_draw_scaled_bitmap(endbg, 0, 0, this->endbgW, this->endbgH, 0, 0, this->WIDTH, this->HEIGHT, NULL);

	al_draw_textf(font18, al_map_rgb(255, 0, 0), this->WIDTH / 2, this->HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Game Over. Final Score: %i", score);
}

void Draw::gameText(int score, int speed){
	al_draw_textf(font18, al_map_rgb(255, 0, 0), 5, 10, 0, "Score: %i", score);
	al_draw_textf(font18, al_map_rgb(255, 0, 0), 5, 40, 0, "Speed: %i", speed);
}

void Draw::menu(int menu, int selection, int WIDTH, int HEIGHT, int FPS, int Volume, float Pan){
	al_draw_scaled_bitmap(menubg, 0, 0, this->menubgW, this->menubgH, 0, 0, this->WIDTH, this->HEIGHT, NULL);

	string text1 = "";
	string text2 = "";
	string text3 = "";

	switch(menu){
		case(1):{
			text1 = "Play game";
			text2 = "Settings";
			text3 = "Quit";
			break;
		}
		case(2):{
			text1 = "Graphics";
			text2 = "Audio";
			text3 = "Back";
			break;
		}
		case(3):{
			text1 = "Resolution: " + to_string(WIDTH) + "X" + to_string(HEIGHT);
			text2 = "FPS: " + to_string(FPS);
			text3 = "Back";
			break;
		}
		case(4):{
			text1 = "Volume: " + to_string(Volume);
			text2 = "Pan: " + to_string(round(Pan));
			text3 = "Back";
			break;
		}
	}

	const char* text1C = text1.c_str();
	const char* text2C = text2.c_str();
	const char* text3C = text3.c_str();

	al_draw_text(font18, al_map_rgb(255, 0, 0), this->WIDTH/2, this->HEIGHT/8*3, ALLEGRO_ALIGN_CENTER, text1C);
	al_draw_text(font18, al_map_rgb(255, 0, 0), this->WIDTH/2, this->HEIGHT/8*4, ALLEGRO_ALIGN_CENTER, text2C);
	al_draw_text(font18, al_map_rgb(255, 0, 0), this->WIDTH/2, this->HEIGHT/8*5, ALLEGRO_ALIGN_CENTER, text3C);

	switch(selection){
		case(1):{
			al_draw_scaled_bitmap(msel, 0, 0, this->selectorW, this->selectorH, this->WIDTH/2 + (al_get_text_width(font18,text1C)/2), this->HEIGHT/8*3 -14, 40, 50, NULL);
			al_draw_scaled_bitmap(msel, 0, 0, this->selectorW, this->selectorH, this->WIDTH/2 - (al_get_text_width(font18,text1C)/2) - (playerWidth()/2.7), this->HEIGHT/8*3 -14, 40, 50, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
		case(2):{
			al_draw_scaled_bitmap(msel, 0, 0, this->selectorW, this->selectorH, this->WIDTH/2 + (al_get_text_width(font18,text2C)/2), this->HEIGHT/8*4 -14, 40, 50, NULL);
			al_draw_scaled_bitmap(msel, 0, 0, this->selectorW, this->selectorH, this->WIDTH/2 - (al_get_text_width(font18,text2C)/2) - (playerWidth()/2.7), this->HEIGHT/8*4 -14, 40, 50, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
		case(3):{
			al_draw_scaled_bitmap(msel, 0, 0, this->selectorW, this->selectorH, this->WIDTH/2 + (al_get_text_width(font18,text3C)/2), this->HEIGHT/8*5 -14, 40, 50, NULL);
			al_draw_scaled_bitmap(msel, 0, 0, this->selectorW, this->selectorH, this->WIDTH/2 - (al_get_text_width(font18,text3C)/2) - (playerWidth()/2.7), this->HEIGHT/8*5 -14, 40, 50, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
	}
}

Draw::~Draw(){
	al_destroy_font(font18);
	al_destroy_font(font42);
	al_destroy_bitmap(playerpic);
	al_destroy_bitmap(groundpic);
	al_destroy_bitmap(ingamebg);
	al_destroy_bitmap(menubg);
	al_destroy_bitmap(endbg);
	al_destroy_bitmap(msel);
}