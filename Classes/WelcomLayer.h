#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "time.h"

using namespace cocos2d;
using namespace std;

class WelcomLayer : public Layer
{
public:
	WelcomLayer();
	~WelcomLayer();
	
	virtual bool init();
	CREATE_FUNC(WelcomLayer);
};

