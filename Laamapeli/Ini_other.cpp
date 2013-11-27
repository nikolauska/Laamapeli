#include "Variables.h"
#include "SimpleIni.h"

CSimpleIniA* ini;

void iniWrite(string section, string key, string newValue){	
	ini->SetValue(section.c_str(), key.c_str(), newValue.c_str());
	ini->SaveFile("Data/Config/Settings.ini");
}

string iniRead(string section, string key, string defaultValue){
	const char *pVal = ini->GetValue(section.c_str(), key.c_str(), defaultValue.c_str());
	string cppstr(pVal);
	return cppstr;
}


void iniInitialize(){
	ini = new CSimpleIniA();
	ini->SetUnicode();
	ini->LoadFile("Data/Config/Settings.ini");
	
	WIDTH = atoi(iniRead("Display","Width","1280").c_str());
	HEIGHT = atoi(iniRead("Display","Height","720").c_str());
	FPS = atoi(iniRead("Display","FPS","60").c_str());
	tempFPS = FPS;

	Volume = atoi(iniRead("Audio","Volume","100").c_str());
	tempVolume = Volume;
	Pan = atof(iniRead("Audio","Pan","0").c_str());
	tempPan = Pan;

	upTime = atof(iniRead("Game","upTime","1").c_str());
	upSpeed = atof(iniRead("Game","upSpeed","0.01").c_str());
	downSpeed = atof(iniRead("Game","downSpeed","0.01").c_str());
	scoreTime = atof(iniRead("Game","scoreTime","0.2").c_str());
	speedScore = atof(iniRead("Game","speedScore","100").c_str());
	startSpeed = atof(iniRead("Game","startSpeed","2").c_str());
}

void getResPos(){
	resPos = 0;
	for(int i = 0; i != resolutions; i++) {
		if(resWidth[i] == WIDTH && resHeight[i] == HEIGHT){
			resPos = i;
			break;
		}
			
	}
}

void loadingScreen(){
	al_init_image_addon();
	ALLEGRO_BITMAP *loading = al_load_bitmap("Data/Pictures/loading.png");
	al_draw_scaled_bitmap(loading, 0, 0, 1920, 1080, 0, 0, WIDTH, HEIGHT, NULL);
	// Flip backbuffer to screen
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
}