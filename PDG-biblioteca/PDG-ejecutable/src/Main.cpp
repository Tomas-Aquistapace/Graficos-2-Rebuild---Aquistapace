#include "Game.h"

void main()
{
	Game* game = new Game();
	
	game->play();

	if (game != NULL)
	{
		delete game;
	}
}