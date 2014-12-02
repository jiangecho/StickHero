#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class MainMenuLayer : public Layer
{
public:
	MainMenuLayer();
	~MainMenuLayer();
	virtual bool init();
	CREATE_FUNC(MainMenuLayer);

	void menuModeNormalCallback(Ref* pSender);
	void menuModeFeelingCallback(Ref* pSender);
};

