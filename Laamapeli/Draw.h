#ifndef drawDEF
#define drawDEF
#include "Header.h"

ALLEGRO_FONT *font18;
ALLEGRO_FONT *font42;
ALLEGRO_BITMAP *lamapic;
ALLEGRO_BITMAP *groundpic;
ALLEGRO_BITMAP *bg1080;
ALLEGRO_BITMAP *menubg1080;
ALLEGRO_BITMAP *endbg1080;
ALLEGRO_BITMAP *msel;

const char* text1C;
const char* text2C;
const char* text3C;
string text1 = "";
string text2 = "";
string text3 = "";

class Draw{
	public:
		Draw();
		~Draw();

		void player(int, int); 
		void ground(int, int);
		void bg();

		void endText(int);
		void gameText(int, int);

		void menu(int, int);

		int picHeight(){return al_get_bitmap_height(lamapic);}
		int picWidth(){return al_get_bitmap_width(lamapic);}
};


Draw::Draw(){
	al_init_font_addon(); 
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_init_image_addon();
	
	font18 = al_load_font("Data/Font/blood.ttf", 24, 0);
	font42 = al_load_font("Data/Font/blood.ttf", 42, 0);

	//Initializing pictures
	lamapic = al_load_bitmap("Data/Pictures/lamapic.png");
	groundpic = al_load_bitmap("Data/Pictures/ground.png");
	bg1080 = al_load_bitmap("Data/Pictures/bg1080.png");
	menubg1080 = al_load_bitmap("Data/Pictures/menubg1080.png");
	endbg1080 = al_load_bitmap("Data/Pictures/endbg1080.png");
	msel = al_load_bitmap("Data/Pictures/selection.png");
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

void Draw::menu(int menu, int selection){
	al_draw_scaled_bitmap(menubg1080, 0, 0, 1920, 1080, 0, 0, WIDTH, HEIGHT, NULL);

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
			text1 = "Resolution :" + to_string(WIDTH) + "X" + to_string(HEIGHT);
			text2 = "Display: Fullscreen";
			text3 = "Back";
			break;
		}
		case(4):{
			text1 = "Volume: " + to_string(volume);
			text2 = "Mute: No";
			text3 = "Back";
			break;
		}
	}

	text1C = text1.c_str();
	text2C = text2.c_str();
	text3C = text3.c_str();

	al_draw_text(font18, al_map_rgb(255, 0, 0), menuPos1X, menuPos1Y, ALLEGRO_ALIGN_CENTER, text1C);
	al_draw_text(font18, al_map_rgb(255, 0, 0), menuPos2X, menuPos2Y, ALLEGRO_ALIGN_CENTER, text2C);
	al_draw_text(font18, al_map_rgb(255, 0, 0), menuPos3X, menuPos3Y, ALLEGRO_ALIGN_CENTER, text3C);

	switch(selection){
		case(1):{
			al_draw_bitmap(msel, menuPos1X + (al_get_text_width(font18,text1C)/2), menuPos1Y -14, NULL);
			al_draw_bitmap(msel, menuPos1X - (al_get_text_width(font18,text1C)/2) - (picWidth()/2.7), menuPos1Y -14, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
		case(2):{
			al_draw_bitmap(msel, menuPos2X + (al_get_text_width(font18,text2C)/2), menuPos2Y -14, NULL);
			al_draw_bitmap(msel, menuPos2X - (al_get_text_width(font18,text2C)/2) - (picWidth()/2.7), menuPos2Y -14, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
		case(3):{
			al_draw_bitmap(msel, menuPos3X + (al_get_text_width(font18,text3C)/2), menuPos3Y -14, NULL);
			al_draw_bitmap(msel, menuPos3X - (al_get_text_width(font18,text3C)/2) - (picWidth()/2.7), menuPos3Y -14, ALLEGRO_FLIP_HORIZONTAL);
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