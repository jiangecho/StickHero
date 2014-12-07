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
		// TODO add the background of the score label
		// TODO set the postions of these labels
		modeLabel = Label::createWithTTF("mode", "fonts/Marker Felt.ttf", 34);
		modeLabel->retain();
		modeLabel->setAlignment(TextHAlignment::CENTER);

		this->addChild(modeLabel);

		scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
		scoreLabel->retain();
		scoreLabel->setAlignment(TextHAlignment::CENTER);

		this->addChild(scoreLabel);

		bestScoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
		bestScoreLabel->retain();

		return true;
	}

	return false;
}

void ResultLayer::updateResultInfo()
{
	int bestScore, score;
	Mode mode;
	auto game = Game::getInstance();
	bestScore = game->getBestScore();
	score = game->getScore();
	mode = game->getMode();

	bestScoreLabel->setString(Value(bestScore).asString());
	scoreLabel->setString(Value(score).asString());
	modeLabel->setString(Value(mode).asString());
}
