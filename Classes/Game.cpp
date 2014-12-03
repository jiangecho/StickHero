#include "Game.h"


Game::Game() :pGame(nullptr)
{
}


Game::~Game()
{
	delete(pGame);
}

Game* Game::getInstance()
{
	if (pGame == nullptr)
	{
		pGame = new Game();
	}

	return pGame;
}
