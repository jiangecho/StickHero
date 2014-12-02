#include "GameLayer.h"
#include "Resource.h"


GameLayer::GameLayer() :currentScore(0), status(GAME_STATUS_READY), isHeroMoving(false)
{
}


// TODO release the sprites in the vector
GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
	if (Layer::init())
	{
		// TODO add two initial pillars and the first stick
		auto origin = Director::getInstance()->getVisibleOrigin();
		auto visibleSize = Director::getInstance()->getVisibleSize();
		hero = Sprite::createWithSpriteFrameName(s_scene_3_heros[0]);
		hero->retain();
		auto heroAnimation = Animation::create();
		for (int i = 0; i < 3; i++)
		{
			heroAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_scene_3_heros[i]));
		}
		heroAnimation->setDelayPerUnit(1.0f /3.0f);
		heroAnimation->setRestoreOriginalFrame(true);
		heroAnimate = Animate::create(heroAnimation);
		heroAnimate->retain();

		auto pillarSprite = Sprite::createWithSpriteFrameName(s_scene_3_pillars[0]);
		pillarSprite->retain();
		pillarSprite->setPosition(origin.x + pillarSprite->getContentSize().width / 2, origin.y + pillarSprite->getContentSize().height / 2);
		pillarSprites.pushBack(pillarSprite);

		hero->setPosition(pillarSprite->getPosition().x + pillarSprite->getContentSize().width /2 - hero->getContentSize().width / 2, 
							pillarSprite->getPosition().y + pillarSprite->getContentSize().height / 2 + hero->getContentSize().height / 2);

		// TODO modify the x location
		pillarSprite = Sprite::createWithSpriteFrameName(s_scene_3_pillars[2]);
		pillarSprite->setPosition(origin.x + 200 + pillarSprite->getContentSize().width, origin.y + pillarSprite->getContentSize().height / 2);
		pillarSprite->retain();
		pillarSprites.pushBack(pillarSprite);

		pillarSprite = obtainRandomLastPillar();
		pillarSprite->retain();
		pillarSprites.pushBack(pillarSprite);

		auto stickSprite = Sprite::createWithSpriteFrameName(s_stick);
		auto spite = pillarSprites.at(0);
		
		// attention how to set anchor point
		stickSprite->setAnchorPoint(Vec2(0.5, 0));
		stickSprite->retain();

		// at the initial state, the first stick is not visible
		stickSprite->setPosition(-100, 
									spite->getPosition().y + spite->getContentSize().height / 2);
		stickSprites.pushBack(stickSprite);

		stickSprite = Sprite::createWithSpriteFrameName(s_stick);
		stickSprite->setAnchorPoint(Vec2(0.5, 0));
		stickSprite->retain();
		stickSprite->setPosition(spite->getPosition().x + spite->getContentSize().width / 2, 
									spite->getPosition().y + spite->getContentSize().height / 2);
		stickSprites.pushBack(stickSprite);

		currentStick = stickSprite;

		spritesNode = Node::create();
		spritesNode->addChild(hero);
		for each (Sprite* sprite in pillarSprites)
		{
			spritesNode->addChild(sprite);
		}

		for each (Sprite* sprite in stickSprites)
		{
			spritesNode->addChild(sprite);
		}
		this->addChild(spritesNode);

		return true;
	}
	return false;
}

bool GameLayer::onTouchBegan(Touch* touch, Event  *event)
{
	if (isHeroMoving)
	{
		return false;
	}
	CCLOG("ontouchbegan");
	schedule(schedule_selector(GameLayer::longerStick), 0.1f, kRepeatForever, 0);
	status = GAME_STATUS_ON_GOING;
	return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event* event)
{
	CCLOG("ontouchmove");
	
}

void GameLayer::onTouchEnded(Touch* touch, Event* event)
{
	if (isHeroMoving)
	{
		return;
	}
	isHeroMoving = true;

	CCLOG("ontouchend");
	unschedule(schedule_selector(GameLayer::longerStick));
	//currentStick->stopActionByTag(longerActionTag);
	currentStick->stopAllActions();

	rotateStickRight();

}

void GameLayer::updateScore(int score)
{

}

void GameLayer::gameOver()
{

}

void GameLayer::longerStick(float dt)
{
	CCLOG("longerStick");
	auto scaleTo = ScaleTo::create(1, 1, currentStick->getContentSize().height + 100);
	currentStick->runAction(scaleTo);
}

// TODO remove it
void GameLayer::rotateStick(float degree)
{
	auto rotateBy = RotateBy::create(1, degree);
	currentStick->runAction(rotateBy);
}

void GameLayer::rotateStickRight()
{
	auto rotateBy = RotateBy::create(1, 90);
	auto callF = CallFuncN::create(CC_CALLBACK_0(GameLayer::onRotateStickRigtEnd, this));
	// attention how to construct a sequence action
	auto squence = Sequence::create(rotateBy, callF, nullptr);
	currentStick->runAction(squence);

}
void GameLayer::onRotateStickRigtEnd()
{
	CCLOG("onRotateStickRight");
	moveHeroRight();
}

// TODO the hero shold move to the most right of the pillar if possible
void GameLayer::moveHeroRight()
{
	MoveTo* moveTo;
	float stickHeight = currentStick->getContentSize().height * currentStick->getScaleY();
	auto sprite0 = pillarSprites.at(0);
	auto sprite1 = pillarSprites.at(1);
	float distanceBetweenPillars = sprite1->getPosition().x - sprite1->getContentSize().width / 2 
									- (sprite0->getPosition().x + sprite0->getContentSize().width / 2);
	if (stickHeight < abs(distanceBetweenPillars) || stickHeight > distanceBetweenPillars + sprite1->getContentSize().width)
	{
		status = GAME_STATUS_DYING;

		// move to the end of the stick
		moveTo = MoveTo::create(1, Vec2(hero->getPosition().x + stickHeight + hero->getContentSize().width / 2, hero->getPosition().y));
	}
	else
	{
		currentScore += SCORE_PER_PILLAR;
		statusDelegate->updateScore(currentScore);
		backgroundDelegate->moveLeft();
		// move the the next pillar right edge
		moveTo = MoveTo::create(1, Vec2(sprite1->getPosition().x + sprite1->getContentSize().width / 2 - hero->getContentSize().width / 2, hero->getPosition().y));
	}

	auto spawn = Spawn::createWithTwoActions(heroAnimate, moveTo);
	auto actionDone = CallFuncN::create(CC_CALLBACK_0(GameLayer::onMoveHeroRightEnd, this));
	auto sequence = Sequence::create(spawn, actionDone, nullptr);
	hero->runAction(sequence);

}
void GameLayer::onMoveHeroRightEnd()
{
	if (status == GAME_STATUS_DYING)
	{
		// TODO notify gameover
		auto moveTo = MoveTo::create(1, Vec2(hero->getPosition().x, - (hero->getContentSize().height / 2)));
		auto rotate = RotateBy::create(1, 90);
		hero->runAction(moveTo);
		currentStick->runAction(rotate);
	}
	else
	{
		status = GAME_STATUS_READY;
		moveLeft();
	}

}

void GameLayer::moveLeft()
{
	// MOVE the pillar and so on left
	float leftDistance = hero->getPosition().x - hero->getContentSize().width / 2;
	auto moveBy = MoveBy::create(1, Vec2(-leftDistance, 0));
	auto actionDone = CallFuncN::create(CC_CALLBACK_0(GameLayer::onMoveLeftEnd, this));
	auto seqence = Sequence::create(moveBy, actionDone, nullptr);
	spritesNode->runAction(seqence);

}
void GameLayer::onMoveLeftEnd()
{
	isHeroMoving = false;
	// adjust the coordinate
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto children = spritesNode->getChildren();
	Vec2 worldPosition;
	for each (Sprite* sprite in children)
	{
		worldPosition = spritesNode->convertToWorldSpace(sprite->getPosition());
		sprite->setPosition(worldPosition);
	}
	spritesNode->setPosition(origin);

	// "add" new pillar and stick sprite
	
	// remove the unvisible pillar
	auto pillarSprite = pillarSprites.at(0);
	spritesNode->removeChild(pillarSprite, true);
	pillarSprites.eraseObject(pillarSprite, false);
	pillarSprite->release();

	pillarSprite = pillarSprites.at(1);
	pillarSprite = obtainRandomLastPillar();
	pillarSprite->retain();
	pillarSprites.pushBack(pillarSprite);
	spritesNode->addChild(pillarSprite);

	// remove the unvisible stick
	auto stickSprite = stickSprites.at(0);
	spritesNode->removeChild(stickSprite, true);
	stickSprites.eraseObject(stickSprite, false);
	stickSprite->release();

	// add a new stick
	// TODO refactor to a function?
	stickSprite = Sprite::createWithSpriteFrameName(s_stick);
	pillarSprite = pillarSprites.at(0);
	stickSprite->setAnchorPoint(Vec2(0.5, 0));
	stickSprite->retain();
	stickSprite->setPosition(pillarSprite->getPosition().x + pillarSprite->getContentSize().width / 2, 
								pillarSprite->getPosition().y + pillarSprite->getContentSize().height / 2);
	stickSprites.pushBack(stickSprite);
	currentStick = stickSprite;
	spritesNode->addChild(currentStick);


}


Sprite* GameLayer::obtainRandomLastPillar()
{
	srand((unsigned)time(NULL));
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int pillarIndex = rand() % (sizeof(s_scene_3_pillars) / sizeof(s_scene_3_pillars[0]));

	auto pillarSprite = Sprite::createWithSpriteFrameName(s_scene_3_pillars[pillarIndex]);
	float pillarSpritePositionX = 0;
	pillarSpritePositionX = (rand() % (int)(pillarSprites.at(1)->getPosition().x + pillarSprites.at(1)->getContentSize().width / 2 
												- hero->getContentSize().width - pillarSprites.at(0)->getPosition().x)) 
									+ visibleSize.width + pillarSprite->getContentSize().width / 2;

	pillarSprite->setPosition(pillarSpritePositionX, origin.y + pillarSprite->getContentSize().height / 2);

	return pillarSprite;
}

