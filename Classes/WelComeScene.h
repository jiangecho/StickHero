#pragma once

#include"cocos2d.h"

using namespace cocos2d;
using namespace std;

class WelComeScene : public Scene
{
public:
	WelComeScene();
	~WelComeScene();
	bool virtual init();
	CREATE_FUNC(WelComeScene);
};

