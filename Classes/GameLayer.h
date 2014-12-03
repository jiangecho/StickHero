#pragma once

#include "cocos2d.h"
#include "ControlLayer.h"

using namespace cocos2d;
using namespace std;


typedef enum _gameStatus{
	GAME_STATUS_READY = 0,
	GAME_STATUS_ON_GOING,
	GAME_STATUS_DYING,
	GAME_STATUS_DEAD
} GameStatus;

class StatusDelegate
{
public:
	virtual void updateScore(int score) = 0;
	virtual void onGameStatus(GameStatus status) = 0;
};

class BackgroundDelegate
{
public:
	virtual void moveLeft() = 0;

};

class GameLayer : public Layer, public ControlDelegate
{
public:
	GameLayer();
	~GameLayer();
	virtual bool init();
	CREATE_FUNC(GameLayer);

	bool onTouchBegan(Touch* touch, Event  *event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	CC_SYNTHESIZE(StatusDelegate*, statusDelegate, StatusDelegator);
	CC_SYNTHESIZE(BackgroundDelegate*, backgroundDelegate, backgroundDelegator);

private:
	void longerStick(float dt);
	void rotateStick(float degree);
	void rotateStickRight();
	void onRotateStickRigtEnd();
	void moveHeroRight();
	void onMoveHeroRightEnd();
	void moveLeft();
	void onMoveLeftEnd();
	Sprite* obtainRandomLastPillar();
	
	// TODO the following functions, maybe we do not need it
	void updateScore(int score);
	void gameOver();

	int currentScore;
	int longerActionTag = 1;

	Vector<Sprite*> stickSprites;
	Vector<Sprite*> pillarSprites;
	Sprite* hero;
	Node* spritesNode;

	Animate * heroAnimate;
	GameStatus status;
	bool isHeroMoving;

	const int SCORE_PER_PILLAR = 5;
};

