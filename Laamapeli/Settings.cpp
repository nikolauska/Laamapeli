#include "Settings.h"

Settings::Settings(){
	ini.SetUnicode();
}

void Settings::load(){
	ini.Reset();
	ini.SetUnicode();
	ini.LoadFile("Settings.ini");

	width = static_cast<int>(ini.GetLongValue("Display", "Width", 1280));
	height = static_cast<int>(ini.GetLongValue("Display", "Height", 720));
	fps = static_cast<int>(ini.GetLongValue("Display", "FPS", 60));
	pendingFPS = fps;

	volume = static_cast<int>(ini.GetLongValue("Audio", "Volume", 100));
	pendingVolume = volume;
	pan = static_cast<float>(ini.GetDoubleValue("Audio", "Pan", 0));
	pendingPan = pan;

	jumpSpeed = static_cast<float>(ini.GetDoubleValue("Game", "jumpSpeed", 600));
	gravity = static_cast<float>(ini.GetDoubleValue("Game", "gravity", 900));
	scoreTime = static_cast<float>(ini.GetDoubleValue("Game", "scoreTime", 0.2));
	speedScore = static_cast<int>(ini.GetLongValue("Game", "speedScore", 100));
	startSpeed = static_cast<int>(ini.GetLongValue("Game", "startSpeed", 2));

	folder = ini.GetValue("Folder", "Folder", "Default");
}

void Settings::saveDisplay(int newWidth, int newHeight, int newFPS){
	width = newWidth;
	height = newHeight;
	fps = newFPS;
	ini.SetLongValue("Display", "Width", width);
	ini.SetLongValue("Display", "Height", height);
	ini.SetLongValue("Display", "FPS", fps);
	ini.SaveFile("Settings.ini");
}

void Settings::saveAudio(int newVolume, float newPan){
	volume = newVolume;
	pan = newPan;
	ini.SetLongValue("Audio", "Volume", volume);
	ini.SetDoubleValue("Audio", "Pan", pan);
	ini.SaveFile("Settings.ini");
}
