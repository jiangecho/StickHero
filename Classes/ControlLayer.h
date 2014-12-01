#pragma once
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class ControlDelegate
{
public:
	virtual bool onTouchBegan(Touch* touch, Event  *event) = 0;
	virtual void onTouchMoved(Touch* touch, Event* event) = 0;
	virtual void onTouchEnded(Touch* touch, Event* event) = 0;

private:

};

class ControlLayer : public Layer
{
public:
	ControlLayer();
	~ControlLayer();
	virtual bool init();
	CREATE_FUNC(ControlLayer);

	bool onTouchBegan(Touch* touch, Event  *event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	CC_SYNTHESIZE(ControlDelegate*, delegate, Delegator);

};

