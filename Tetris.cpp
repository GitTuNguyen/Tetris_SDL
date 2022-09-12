#include "ConstValue.h"
#include "Game.h"

void main()
{
	Game* game = new Game();

	game->Update();

	delete game;

	getchar();
}