#include "ResultLayer.h"


ResultLayer::ResultLayer()
{
}


ResultLayer::~ResultLayer()
{
	CC_SAFE_RELEASE(scoreLabel);
	CC_SAFE_RELEASE(bestScoreLabel);
	CC_SAFE_RELEASE(modeLabel);
}

bool ResultLayer::init()
{
	if (Layer::init())
	{
		// TODO 
		modeLabel = Label::createWithTTF("mode", "fonts/Marker Felt.ttf", 34);
		modeLabel->setAlignment(TextHAlignment::CENTER);

		this->addChild(modeLabel);

		scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
		scoreLabel->setAlignment(TextHAlignment::CENTER);

		this->addChild(scoreLabel);

		bestScoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);

		return true;
	}

	return false;
}

void ResultLayer::updateResultInfo()
{
	// TODO read the info from the game instance

}
