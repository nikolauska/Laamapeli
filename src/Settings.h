#ifndef SettingsDEF
#define SettingsDEF

#include "SimpleIni.h"
#include <string>

class Settings {
public:
  int width = 1280;
  int height = 720;
  int fps = 60;
  int volume = 100;
  float pan = 0;
  float jumpSpeed = 600;
  float gravity = 900;
  float scoreTime = 0.2f;
  int speedScore = 100;
  int startSpeed = 2;
  std::string folder = "Default";

  int pendingFPS = fps;
  int pendingVolume = volume;
  float pendingPan = pan;

  Settings();
  void load();
  void saveDisplay(int newWidth, int newHeight, int newFPS);
  void saveAudio(int newVolume, float newPan);

private:
  CSimpleIniA ini;
};

#endif
