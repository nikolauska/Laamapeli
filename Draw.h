#ifndef drawDEF
#define drawDEF
#include "Header.h"

ALLEGRO_FONT *font18 = NULL;
ALLEGRO_FONT *font42 = NULL;
ALLEGRO_BITMAP *lamapic = NULL;
ALLEGRO_BITMAP *groundpic = NULL;

ALLEGRO_BITMAP *bg5760 = NULL;
ALLEGRO_BITMAP *bg1080 = NULL;
ALLEGRO_BITMAP *bg720 = NULL;
ALLEGRO_BITMAP *bg480 = NULL;
ALLEGRO_BITMAP *bg360 = NULL;

ALLEGRO_BITMAP *menubg5760 = NULL;
ALLEGRO_BITMAP *menubg1080 = NULL;
ALLEGRO_BITMAP *menubg720 = NULL;
ALLEGRO_BITMAP *menubg480 = NULL;
ALLEGRO_BITMAP *menubg360 = NULL;

ALLEGRO_BITMAP *endbg5760 = NULL;
ALLEGRO_BITMAP *endbg1080 = NULL;
ALLEGRO_BITMAP *endbg720 = NULL;
ALLEGRO_BITMAP *endbg480 = NULL;
ALLEGRO_BITMAP *endbg360 = NULL;

class Draw{
	public:
		Draw();
		~Draw();

		void player(int, int); 
		void ground(int, int);
		void bg();
		
		void endText(int);
		void gameText(int, int);

		void mainMenu(int, int, int, int);

		int picHeight(){return al_get_bitmap_height(lamapic);}
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

	//Ingame Background pictures
	bg5760 = al_load_bitmap("Data/Pictures/bg5760.png");
	bg1080 = al_load_bitmap("Data/Pictures/bg1080.png");
	bg720 = al_load_bitmap("Data/Pictures/bg720.png");
	bg480 = al_load_bitmap("Data/Pictures/bg480.png");
	bg360 = al_load_bitmap("Data/Pictures/bg360.png");

	//Menu Background pictures
	menubg5760 = al_load_bitmap("Data/Pictures/menubg5760.png");
	menubg1080 = al_load_bitmap("Data/Pictures/menubg1080.png");
	menubg720 = al_load_bitmap("Data/Pictures/menubg720.png");
	menubg480 = al_load_bitmap("Data/Pictures/menubg480.png");
	menubg360 = al_load_bitmap("Data/Pictures/menubg360.png");


	//End Background pictures
	endbg5760 = al_load_bitmap("Data/Pictures/endbg5760.png");
	endbg1080 = al_load_bitmap("Data/Pictures/endbg1080.png");
	endbg720 = al_load_bitmap("Data/Pictures/endbg720.png");
	endbg480 = al_load_bitmap("Data/Pictures/endbg480.png");
	endbg360 = al_load_bitmap("Data/Pictures/endbg360.png");
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
	if(WIDTH == 5760)
		al_draw_bitmap(bg5760, 0, 0, NULL);

	else if(WIDTH == 1920)
		al_draw_bitmap(bg1080, 0, 0, NULL);

	else if(WIDTH == 1280)
		al_draw_bitmap(bg720, 0, 0, NULL);

	else if(WIDTH == 853)
		al_draw_bitmap(bg480, 0, 0, NULL);

	else if(WIDTH == 639)
		al_draw_bitmap(bg360, 0, 0, NULL);
}

void Draw::endText(int score){
	if(WIDTH == 5760)
		al_draw_bitmap(endbg5760, 0, 0, NULL);

	else if(WIDTH == 1920)
		al_draw_bitmap(endbg1080, 0, 0, NULL);

	else if(WIDTH == 1280)
		al_draw_bitmap(endbg720, 0, 0, NULL);

	else if(WIDTH == 853)
		al_draw_bitmap(endbg480, 0, 0, NULL);

	else if(WIDTH == 639)
		al_draw_bitmap(endbg360, 0, 0, NULL);

	al_draw_textf(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Game Over. Final Score: %i", score);
}

void Draw::gameText(int score, int speed){
	al_draw_textf(font18, al_map_rgb(255, 0, 0), 5, 10, 0, "Score: %i             Speed: %i", score, speed);
}

void Draw::mainMenu(int selection, int playY, int settingsY, int quitY){
	if(WIDTH == 5760)
		al_draw_bitmap(menubg5760, 0, 0, NULL);

	else if(WIDTH == 1920)
		al_draw_bitmap(menubg1080, 0, 0, NULL);

	else if(WIDTH == 1280)
		al_draw_bitmap(menubg720, 0, 0, NULL);

	else if(WIDTH == 853)
		al_draw_bitmap(menubg480, 0, 0, NULL);

	else if(WIDTH == 639)
		al_draw_bitmap(menubg360, 0, 0, NULL);

	al_draw_text(font18, al_map_rgb(255, 0, 0), menuPlayGamePosX, playY, ALLEGRO_ALIGN_CENTER, "Play game");
	al_draw_text(font18, al_map_rgb(255, 0, 0), menuSettingsPosX, settingsY, ALLEGRO_ALIGN_CENTER, "Settings");
	al_draw_text(font18, al_map_rgb(255, 0, 0), menuExitPosX, quitY, ALLEGRO_ALIGN_CENTER, "Quit");
	al_draw_text(font18, al_map_rgb(255, 0, 0), menuPlayGamePosX, playY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Graphics");
	al_draw_text(font18, al_map_rgb(255, 0, 0), menuSettingsPosX, settingsY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Audio");
	al_draw_text(font18, al_map_rgb(255, 0, 0), menuExitPosX, quitY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Back");

	if(selection == 1) {
		int x1 = menuPlayGamePosX - 50;
		int y1 = menuPlayGamePosY + 25;

		int x2 = menuPlayGamePosX + 50;
		int y2 = menuPlayGamePosY + 25;

		al_draw_line(x1, y1, x2, y2, al_map_rgb(255, 0, 0), 5);
	} 
	else if(selection == 2) {	
		int x1 = menuSettingsPosX - 50;
		int y1 = menuSettingsPosY + 25;

		int x2 = menuSettingsPosX + 50;
		int y2 = menuSettingsPosY + 25;

		al_draw_line(x1, y1, x2, y2, al_map_rgb(255, 0, 0), 5);
	}
	else if(selection == 3) {
		int x1 = menuExitPosX - 50;
		int y1 = menuExitPosY + 25;

		int x2 = menuExitPosX + 50;
		int y2 = menuExitPosY + 25;

		al_draw_line(x1, y1, x2, y2, al_map_rgb(255, 0, 0), 5);
	}

}

	Draw::~Draw(){
	al_destroy_font(font18);
	al_destroy_font(font42);
	al_destroy_bitmap(lamapic);
	al_destroy_bitmap(groundpic);
	al_destroy_bitmap(bg5760);
	al_destroy_bitmap(bg1080);
	al_destroy_bitmap(bg720);
	al_destroy_bitmap(bg480);
	al_destroy_bitmap(bg360);
	al_destroy_bitmap(menubg5760);
	al_destroy_bitmap(menubg1080);
	al_destroy_bitmap(menubg720);
	al_destroy_bitmap(menubg480);
	al_destroy_bitmap(menubg360);
	}


#endif