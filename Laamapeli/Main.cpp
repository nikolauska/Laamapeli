// Object variables
void groundInitialize();
int initialize();
bool Events();
void timerEvent();
void upTimerEvent();
void scoreTimerEvent();
void speedTimerEvent();
bool displayCloseEvent();
bool keyPressEvent();
void drawEvent();
void destroy();
bool done = false;

/*
*	Beginninng of main object!
*	Here is the famous main loop which will keep our game running
*	if this is ended the whole program will end
*	
*/

int main(int argc, char **argv)
{	
	if(initialize() == -1)
		return -1;
	
	groundInitialize();

	while(true) {	
		if(Events())
			break;
	}	

	destroy();

	return 0;
}
