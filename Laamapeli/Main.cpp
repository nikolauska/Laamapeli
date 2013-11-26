// Object variables
int initialize();
bool Events();
void destroy();

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

	while(true) {	
		if(Events())
			break;
	}	

	destroy();

	return 0;
}
