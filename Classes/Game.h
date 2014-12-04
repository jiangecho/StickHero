#pragma once
class Game
{
public:
	Game* getInstance();
private:
	Game();
	~Game();

	Game* pGame;
	int skinType;
	int currentScore;
	int bestScore;
	int status;
	int mode;
};

