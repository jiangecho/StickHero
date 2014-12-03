#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class MainMenuDelegate
{
public:
	virtual void onMenuModeNormalCallBack() = 0;
	virtual void onMenuModeFeelingCallback() = 0;
};
class MainMenuLayer : public Layer
{
public:
	MainMenuLayer();
	~MainMenuLayer();
	virtual bool init();
	CREATE_FUNC(MainMenuLayer);

	void menuModeNormalCallback(Ref* pSender);
	void menuModeFeelingCallback(Ref* pSender);

	CC_SYNTHESIZE(MainMenuDelegate*, delegate, Delegator);
};

