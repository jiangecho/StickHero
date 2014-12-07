#pragma once
typedef enum _Mode
{
	MODE_NORMAL = 0,
	MODE_FEELING

}Mode;

typedef enum _Status
{
	STATUS_READY = 0,
	STATUS_DYING,
	STATUS_OVER

}Status;

typedef enum _SkinType
{
	SKIN_TYPE_0 = 0,
	SKIN_TYPE_1
}SkinType;

class Game
{
public:
	static Game* getInstance();
	void setSkinType(SkinType skinType);
	SkinType getSkinType();

	int getBestScore();
	int getScore();
	void addScore(int score);

	Mode getMode();
	void setMode(Mode mode);

	const int SCORE_PER_PILLAR = 5;

private:
	Game();
	~Game();

	static Game* pGame;
	SkinType skinType;
	int currentScore;
	int bestScore;
	Status status;
	Mode mode;
};

