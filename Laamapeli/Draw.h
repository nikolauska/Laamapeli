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

void Draw::mainMenu(int selection, int playY, int settingsY, int quitY){
	al_draw_scaled_bitmap(menubg1080, 0, 0, 1920, 1080, 0, 0, WIDTH, HEIGHT, NULL);

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

		//al_draw_line(x1, y1, x2, y2, al_map_rgb(255, 0, 0), 5);
		al_draw_bitmap(msel, (WIDTH/2)+75,((HEIGHT/8)*3)-14, NULL);
		al_draw_bitmap(msel, (WIDTH/2)-115,((HEIGHT/8)*3)-14, ALLEGRO_FLIP_HORIZONTAL);
	} 
	else if(selection == 2) {	
		int x1 = menuSettingsPosX - 50;
		int y1 = menuSettingsPosY + 25;

		int x2 = menuSettingsPosX + 50;
		int y2 = menuSettingsPosY + 25;

		//al_draw_line(x1, y1, x2, y2, al_map_rgb(255, 0, 0), 5);
		al_draw_bitmap(msel, (WIDTH/2)+55,((HEIGHT/8)*4)-14, NULL);
		al_draw_bitmap(msel, (WIDTH/2)-95,((HEIGHT/8)*4)-14, ALLEGRO_FLIP_HORIZONTAL);
	}
	else if(selection == 3) {
		int x1 = menuExitPosX - 50;
		int y1 = menuExitPosY + 25;

		int x2 = menuExitPosX + 50;
		int y2 = menuExitPosY + 25;

		//al_draw_line(x1, y1, x2, y2, al_map_rgb(255, 0, 0), 5);
		al_draw_bitmap(msel, (WIDTH/2)+20,((HEIGHT/8)*5)-14, NULL);
		al_draw_bitmap(msel, (WIDTH/2)-65,((HEIGHT/8)*5)-14, ALLEGRO_FLIP_HORIZONTAL);
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
	}


#endif