#include "Game.h"


Game::Game() :bestScore(0), skinType(SKIN_TYPE_0), status(STATUS_READY),
currentScore(0), mode(MODE_NORMAL)
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

SkinType Game::getSkinType()
{
	return this->skinType;
}

void Game::setSkinType(SkinType skinType)
{
	this->skinType = skinType;
}

int Game::getBestScore()
{
	return this->bestScore;
}

void Game::addScore(int score)
{
	this->currentScore += score;
}

Mode Game::getMode()
{
	return this->mode;
}

void Game::setMode(Mode mode)
{
	this->mode = mode;
}
