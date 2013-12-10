#include "Variables.h"
#include "SimpleIni.h"

CSimpleIniA* ini;
string folder;

// write new values to ini
void iniWrite(string section, string key, string newValue){	
	ini->SetValue(section.c_str(), key.c_str(), newValue.c_str());
	ini->SaveFile("Settings.ini");
}

// read ini values from file
string iniRead(string section, string key, string defaultValue){
	const char *pVal = ini->GetValue(section.c_str(), key.c_str(), defaultValue.c_str());
	string cppstr(pVal);
	return cppstr;
}

// initilize variables from ini file
void iniInitialize(){
	ini = new CSimpleIniA();
	ini->SetUnicode();
	ini->LoadFile("Settings.ini"); // filename
	
	// display values
	WIDTH = atoi(iniRead("Display","Width","1280").c_str());
	HEIGHT = atoi(iniRead("Display","Height","720").c_str());
	FPS = atoi(iniRead("Display","FPS","60").c_str());
	tempFPS = FPS;

	// Audio values
	Volume = atoi(iniRead("Audio","Volume","100").c_str());
	tempVolume = Volume;
	Pan = atof(iniRead("Audio","Pan","0").c_str());
	tempPan = Pan;

	// timer values
	upTime = atof(iniRead("Game","upTime","36").c_str());
	upSpeed = atof(iniRead("Game","upSpeed","0.04").c_str());
	downSpeed = atof(iniRead("Game","downSpeed","0.05").c_str());
	scoreTime = atof(iniRead("Game","scoreTime","0.2").c_str());
	speedScore = atof(iniRead("Game","speedScore","100").c_str());
	startSpeed = atof(iniRead("Game","startSpeed","2").c_str());

	// folder value (used for modding)
	folder = iniRead("Folder","Folder","Default");
}

// function to find resoltuiion postion in list
void getResPos(){
	resPos = 0;
	for(int i = 0; i != resolutions; i++) {
		if(resWidth[i] == WIDTH && resHeight[i] == HEIGHT){
			resPos = i;
			break;
		}
			
	}
}

// return rounded float as a string (example 0,100000 to 0,1)
string round(float x) {
    stringstream ss;
    ss << fixed;
    ss.precision(1); // set # places after decimal
    ss << x;
    return ss.str();
}