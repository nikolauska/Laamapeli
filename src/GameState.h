#ifndef GameStateDEF
#define GameStateDEF
#include "Audio.h"
#include "Draw.h"
#include "Ground.h"
#include "Player.h"
#include "Settings.h"

#include <allegro5/allegro.h>

#include <array>
#include <memory>
#include <optional>
#include <vector>

class GameState {
public:
  int initialize();
  void destroy();

  ALLEGRO_EVENT_QUEUE *eventQueue() const { return eventQueue_.get(); }
  bool timerEvent(ALLEGRO_EVENT);
  Settings &settings() { return settings_; }
  const Settings &settings() const { return settings_; }

  Player &player() { return player_; }
  Draw &draw() { return *draw_; }
  Audio &audio() { return *audio_; }

  void clearGrounds() { grounds_.clear(); }
  void startGame();
  void recycleGround(Ground &ground, int speed) {
    ground.create(lastX_, lastY_, speed);
  }
  void drawGrounds();
  void moveGrounds();

  std::size_t resolutionCount() const { return resolutionWidths_.size(); }
  std::size_t resolutionPosition() const { return resolutionPosition_; }
  void setResolutionPosition(std::size_t position) {
    resolutionPosition_ = position;
  }
  int resolutionWidth() const { return resolutionWidths_[resolutionPosition_]; }
  int resolutionHeight() const {
    return resolutionHeights_[resolutionPosition_];
  }

  int menuSelection() const { return menuSelection_; }
  void setMenuSelection(int selection) { menuSelection_ = selection; }
  int menuText() const { return menuText_; }
  void setMenuText(int text) { menuText_ = text; }
  int gamePosition() const { return gamePosition_; }
  void setGamePosition(int position) { gamePosition_ = position; }

private:
  void findResolution();
  void scoreTimerEvent(ALLEGRO_EVENT);
  bool isFpsTimerEvent(const ALLEGRO_EVENT &event) const {
    return event.timer.source == fpsTimer_.get();
  }
  bool isScoreTimerEvent(const ALLEGRO_EVENT &event) const {
    return event.timer.source == scoreTimer_.get();
  }
  long scoreTimerCount() const { return al_get_timer_count(scoreTimer_.get()); }
  void startScoreTimer() { al_start_timer(scoreTimer_.get()); }
  Settings settings_;

  std::shared_ptr<ALLEGRO_DISPLAY> display_;
  std::shared_ptr<ALLEGRO_EVENT_QUEUE> eventQueue_;
  std::shared_ptr<ALLEGRO_TIMER> fpsTimer_;
  std::shared_ptr<ALLEGRO_TIMER> scoreTimer_;
  Player player_;
  std::vector<Ground> grounds_;
  std::optional<Draw> draw_;
  std::optional<Audio> audio_;

  std::size_t resolutionPosition_ = 0;
  int lastX_ = 0;
  int lastY_ = 0;
  std::array<int, 10> resolutionWidths_{640,  800,  1024, 1280, 1280,
                                        1366, 1600, 1600, 1680, 1920};
  std::array<int, 10> resolutionHeights_{480, 600, 768,  720,  960,
                                         768, 900, 1200, 1050, 1080};

  int menuSelection_ = 1;
  int menuText_ = 1;
  int gamePosition_ = 1;
};
#endif