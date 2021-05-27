#include"cGame.h"
int main()
{
	srand(time(NULL));
	cGame *g;
	g = new cGame;
	g->window_run();
	delete g;
} 