#include "Variables.h"
#include "SimpleIni.h"

CSimpleIniA* ini;
string folder;

void iniWrite(string section, string key, string newValue){	
	ini->SetValue(section.c_str(), key.c_str(), newValue.c_str());
	ini->SaveFile("Settings.ini");
}

string iniRead(string section, string key, string defaultValue){
	const char *pVal = ini->GetValue(section.c_str(), key.c_str(), defaultValue.c_str());
	string cppstr(pVal);
	return cppstr;
}


void iniInitialize(){
	ini = new CSimpleIniA();
	ini->SetUnicode();
	ini->LoadFile("Settings.ini");
	
	WIDTH = atoi(iniRead("Display","Width","1280").c_str());
	HEIGHT = atoi(iniRead("Display","Height","720").c_str());
	FPS = atoi(iniRead("Display","FPS","60").c_str());
	tempFPS = FPS;

	Volume = atoi(iniRead("Audio","Volume","100").c_str());
	tempVolume = Volume;
	Pan = atof(iniRead("Audio","Pan","0").c_str());
	tempPan = Pan;

	upTime = atof(iniRead("Game","upTime","36").c_str());
	upSpeed = atof(iniRead("Game","upSpeed","0.04").c_str());
	downSpeed = atof(iniRead("Game","downSpeed","0.05").c_str());
	scoreTime = atof(iniRead("Game","scoreTime","0.2").c_str());
	speedScore = atof(iniRead("Game","speedScore","100").c_str());
	startSpeed = atof(iniRead("Game","startSpeed","2").c_str());

	folder = iniRead("Folder","Folder","Default");
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


string round(float x) {
    stringstream ss;
    ss << fixed;
    ss.precision(1); // set # places after decimal
    ss << x;
    return ss.str();
}