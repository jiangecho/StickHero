#pragma once
#include "cocos2d.h"
#include "GameLayer.h"

using namespace cocos2d;

class StatusLayer : public Layer, public StatusDelegate
{
public:
	StatusLayer();
	~StatusLayer();

	virtual bool init();

	CREATE_FUNC(StatusLayer);

	void updateScore(int score);
	void onGameStatus(GameStatus status);


private:
	Label* scoreLabel;
	Label* promptLabel;
};

