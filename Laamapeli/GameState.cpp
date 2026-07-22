#include "GameState.h"



void GameState::findResolution(){
	const Settings& settings = settings_;
	resolutionPosition_ = 0;
	for(std::size_t i = 0; i != resolutionWidths_.size(); i++)
		if(resolutionWidths_[i] == settings.width && resolutionHeights_[i] == settings.height){
			resolutionPosition_ = i;
			break;
		}
}

void GameState::startGame(){
	const Settings& settings = settings_;
	player_.start(settings.startSpeed, settings.width, settings.height);

	grounds_.emplace_back(settings.height);
	grounds_.back().start(settings.width, settings.height, draw_->playerHeight(), lastX_, lastY_);

	for (int j = 0; j != int((settings.width / 300) + 15); j++){
		grounds_.emplace_back(settings.height);
		recycleGround(grounds_.back(), player_.getSpeed());
	}

	startScoreTimer();
}

void GameState::drawGrounds(){
	for (auto& ground : grounds_)
		draw_->ground(ground.getX(), ground.getY());
}

void GameState::moveGrounds(){
	int tempX = player_.getX();
	int tempY = player_.getY();
	int previousY = player_.getPreviousY();
	int tempH = draw_->playerHeight();
	int tempW = draw_->playerWidth();
	int speed = player_.getSpeed();

	player_.setGround(false);
	for (auto& ground : grounds_){
		ground.move(speed);

		if (ground.getX() + 300 <= 0)
			recycleGround(ground, speed);

		if(ground.getX() - 300 <= (tempX - tempW*1.5) && ground.getX() + 300 - tempW/2 >= tempX)
			if(player_.isFalling() && previousY + tempH <= ground.getY() && tempY + tempH >= ground.getY())
				player_.land(ground.getY() - tempH);
	}
}

void GameState::scoreTimerEvent(ALLEGRO_EVENT event){
	if(isScoreTimerEvent(event)){
		player_.addScore();
		if(scoreTimerCount() % settings_.speedScore == 0)
			player_.addSpeed();
	}
}

bool GameState::timerEvent(ALLEGRO_EVENT event){
	bool redraw = false;
	if(event.type == ALLEGRO_EVENT_TIMER){
		if(isFpsTimerEvent(event)){
			redraw = true;
			if(gamePosition_ == 3){
				player_.update(settings_.gravity, 1.0f / settings_.fps);
				moveGrounds();
			}
		}

		if(gamePosition_ == 3)
			scoreTimerEvent(event);
	}
	return redraw;
}


void loadingScreen(const string& text, const Settings& settings, const std::shared_ptr<ALLEGRO_BITMAP>& loading, const std::shared_ptr<ALLEGRO_FONT>& fontLoading){
	al_draw_scaled_bitmap(loading.get(), 0, 0, al_get_bitmap_width(loading.get()), al_get_bitmap_height(loading.get()), 0, 0, settings.width, settings.height, 0); // draw loading image
	al_draw_text(fontLoading.get(), al_map_rgb(255, 0, 0), settings.width/2, settings.height/8*7, ALLEGRO_ALIGN_CENTER, text.c_str()); // draw text

	// Flip backbuffer to screen and clear backbuffer
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
}

int GameState::initialize(){
	Settings& settings = settings_;

	//Test allegro object
	if(!al_init())
		return -1;

	// load varaibles from ini file
	settings.load();

	//create and test display object
	auto* display = al_create_display(settings.width, settings.height);
	if(!display)
		return -1;
	display_ = std::shared_ptr<ALLEGRO_DISPLAY>(display, al_destroy_display);

	// Load allegro addons
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_install_keyboard();
	al_install_mouse();
	al_init_acodec_addon();

	// load loading image and show error if not found
	string temp = settings.folder + "/Pictures/loading.png";
	auto* loadingBitmap = al_load_bitmap(temp.c_str());
	if(!loadingBitmap){
		al_show_native_message_box(display_.get(), "ERROR", "IMAGES", "Backround for loadingscreen not found! \nWe suggest to check if filename is correct in 'Pictures' folder. \nFilename for this file is 'loading.png'", NULL, 0);
		display_.reset();
		return -1;
	}
	auto loading = std::shared_ptr<ALLEGRO_BITMAP>(loadingBitmap, al_destroy_bitmap);

	// load font for text and show error if not found
	temp = settings.folder + "/Font/font.ttf";
	auto* loadingFont = al_load_font(temp.c_str(), 24, 0);
	if(!loadingFont){
		al_show_native_message_box(display_.get(), "ERROR", "FONT", "Font not found! \nWe suggest to check if filename is correct in 'Font' folder. \nFilename for this file is 'font.ttf'", NULL, 0);
		display_.reset();
		return -1;
	}
	auto fontLoading = std::shared_ptr<ALLEGRO_FONT>(loadingFont, al_destroy_font);

	// searching resolution postion in list
	loadingScreen("Loading Resolutions...", settings, loading, fontLoading);
	findResolution();

	// load player class
	loadingScreen("Loading Player...", settings, loading, fontLoading);
	player_ = Player{};

	// load draw class and catch error if it is thrown
	loadingScreen("Loading Draw functions...", settings, loading, fontLoading);
	try{
		draw_.emplace(settings.height, settings.width, settings.folder);
	} catch(const char* message) {
		al_show_native_message_box(display_.get(), "ERROR", "IMAGES", message, NULL, 0);
		display_.reset();
		player_ = Player{};
		return -1;
	}

	// load audio class and catch error if it is thrown
	loadingScreen("Loading Audio...", settings, loading, fontLoading);
	try{
		audio_.emplace(settings.folder);
	} catch(const char* message) {
		al_show_native_message_box(display_.get(), "ERROR", "AUDIO", message, NULL, 0);
		display_.reset();
		player_ = Player{};
		draw_.reset();
		return -1;
	}

	loadingScreen("Loading Timers...", settings, loading, fontLoading);
	// Create timers
	auto* fpsTimer = al_create_timer(1.0 / settings.fps);
	auto* scoreTimer = al_create_timer(settings.scoreTime);
	auto* eventQueue = al_create_event_queue();
	if(!fpsTimer || !scoreTimer || !eventQueue) {
		if(fpsTimer) al_destroy_timer(fpsTimer);
		if(scoreTimer) al_destroy_timer(scoreTimer);
		if(eventQueue) al_destroy_event_queue(eventQueue);
		return -1;
	}
	fpsTimer_ = std::shared_ptr<ALLEGRO_TIMER>(fpsTimer, al_destroy_timer);
	scoreTimer_ = std::shared_ptr<ALLEGRO_TIMER>(scoreTimer, al_destroy_timer);
	eventQueue_ = std::shared_ptr<ALLEGRO_EVENT_QUEUE>(eventQueue, al_destroy_event_queue);

	loadingScreen("Loading Events...", settings, loading, fontLoading);
	// Register events
	al_register_event_source(eventQueue_.get(), al_get_keyboard_event_source());
	al_register_event_source(eventQueue_.get(), al_get_display_event_source(display_.get()));
	al_register_event_source(eventQueue_.get(), al_get_timer_event_source(fpsTimer_.get()));
	al_register_event_source(eventQueue_.get(), al_get_timer_event_source(scoreTimer_.get()));
	al_register_event_source(eventQueue_.get(), al_get_mouse_event_source());

	// Start FPStimer
	al_start_timer(fpsTimer_.get());

	// initialize rand
	srand(time(NULL));
	return 0;
}

/*
*	Beginninng of destroy object!
*	Here we destroy everything from memory
*	This prevents memory leaks (we don't want your PC to run slow)
*
*/


void GameState::destroy(){
	clearGrounds();

	// destroy allegro stuff
	eventQueue_.reset();
	fpsTimer_.reset();
	scoreTimer_.reset();
	display_.reset();

	draw_.reset();
	audio_.reset();
}