#include "ControlLayer.h"


ControlLayer::ControlLayer()
{

}


ControlLayer::~ControlLayer()
{

}

bool ControlLayer::init()
{
	if (Layer::init())
	{
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		auto listner = EventListenerTouchOneByOne::create();
		listner->onTouchBegan = CC_CALLBACK_2(ControlLayer::onTouchBegan, this);
		listner->onTouchMoved = CC_CALLBACK_2(ControlLayer::onTouchMoved, this);
		listner->onTouchEnded = CC_CALLBACK_2(ControlLayer::onTouchEnded, this);
		dispatcher->addEventListenerWithSceneGraphPriority(listner, this);
		return true;
	}


	return false;
}

bool ControlLayer::onTouchBegan(Touch* touch, Event  *event)
{
	delegate->onTouchBegan(touch, event);
	return true;
}

void ControlLayer::onTouchMoved(Touch* touch, Event* event)
{
	delegate->onTouchMoved(touch, event);
}

void ControlLayer::onTouchEnded(Touch* touch, Event* event)
{
	delegate->onTouchEnded(touch, event);
}
