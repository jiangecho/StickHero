#pragma once
#include "cocos2d.h"
#include "Game.h"
using namespace cocos2d;

class ResultLayer : public Layer
{
public:
	ResultLayer();
	~ResultLayer();
	virtual bool init();
	void updateResultInfo();

private:
	Label* modeLabel;
	Label* scoreLabel;
	Label* bestScoreLabel;

};

