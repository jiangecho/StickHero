#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class ResultLayer : public Layer
{
public:
	ResultLayer();
	~ResultLayer();
	virtual bool init();

private:
	void updateResultInfo();
	Label* modeLabel;
	Label* scoreLabel;
	Label* bestScoreLabel;

};

