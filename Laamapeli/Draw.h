#ifndef drawDEF
#define drawDEF
#include "Header.h"

ALLEGRO_FONT *font18 = NULL;
ALLEGRO_BITMAP *lamapic = NULL;

class Draw{
	public:
		Draw();
		~Draw(){al_destroy_font(font18); al_destroy_bitmap(lamapic);}

		void player(int, int); 
		void ground(int, int);		
		
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
	
	font18 = al_load_font("arial.ttf", 18, 0);
	lamapic = al_load_bitmap("Data/Pictures/lamapic.png");
}

void Draw::player(int x, int y){
	al_draw_bitmap(lamapic, x, y, NULL);
}

void Draw::ground(int x, int y){
	int x1 = x - 100;
	int y1 = y;

	int x2 = x + 100;
	int y2 = y;

	al_draw_line(x1, y1, x2, y2, al_map_rgb(255, 0, 0), 10);
}

void Draw::endText(int score){
	al_draw_textf(font18, al_map_rgb(0, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Game Over. Final Score: %i ! Press Enter to restart!", score);
}

void Draw::gameText(int score, int speed){
	al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Score: %i	Speed: %i", score, speed);
}

void Draw::mainMenu(int selection, int playY, int settingsY, int quitY){
	al_draw_text(font18, al_map_rgb(255, 0, 255), menuPlayGamePosX, playY, ALLEGRO_ALIGN_CENTER, "Play game");
	al_draw_text(font18, al_map_rgb(255, 0, 255), menuSettingsPosX, settingsY, ALLEGRO_ALIGN_CENTER, "Settings");
	al_draw_text(font18, al_map_rgb(255, 0, 255), menuExitPosX, quitY, ALLEGRO_ALIGN_CENTER, "Quit");
	al_draw_text(font18, al_map_rgb(255, 0, 255), menuPlayGamePosX, playY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Graphics");
	al_draw_text(font18, al_map_rgb(255, 0, 255), menuSettingsPosX, settingsY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Audio");
	al_draw_text(font18, al_map_rgb(255, 0, 255), menuExitPosX, quitY + HEIGHT, ALLEGRO_ALIGN_CENTER, "Back");

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

#endif