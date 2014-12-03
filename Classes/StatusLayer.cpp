#include "StatusLayer.h"


StatusLayer::StatusLayer() :scoreLabel(nullptr), promptLabel(nullptr)
{
}


StatusLayer::~StatusLayer()
{
	CC_SAFE_RELEASE(scoreLabel);
	CC_SAFE_RELEASE(promptLabel);
}

bool StatusLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
	scoreLabel->setAlignment(TextHAlignment::CENTER);
	scoreLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - scoreLabel->getContentSize().height));
	this->addChild(scoreLabel, 1);

	promptLabel = Label::createWithTTF("Touch the screen to longer the stick", "fonts/Marker Felt.ttf", 24);
	promptLabel->setAlignment(TextHAlignment::CENTER);
	promptLabel->setPosition(origin.x + visibleSize.width / 2, 
		origin.y + visibleSize.height - scoreLabel->getContentSize().height - promptLabel->getContentSize().height * 2);
	this->addChild(promptLabel, 1);

	return true;
}

void StatusLayer::updateScore(int score)
{
	Value value(score);
	scoreLabel->setString(value.asString());
}
void StatusLayer::showPrompt()
{
	promptLabel->setVisible(true);
}
void StatusLayer::hidePrompt()
{
	promptLabel->setVisible(false);
}
