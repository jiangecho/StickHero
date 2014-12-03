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
	int status;
};

