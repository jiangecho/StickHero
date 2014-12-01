#include "GameLayer.h"
#include "Resource.h"


GameLayer::GameLayer() :currentScore(0), status(GAME_STATUS_READY)
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

		currentPillar = pillarSprite;
		hero->setPosition(pillarSprite->getPosition().x + pillarSprite->getContentSize().width /2 - hero->getContentSize().width / 2, 
							pillarSprite->getPosition().y + pillarSprite->getContentSize().height / 2 + hero->getContentSize().height / 2);

		// TODO modify the x location
		pillarSprite = Sprite::createWithSpriteFrameName(s_scene_3_pillars[1]);
		pillarSprite->retain();
		pillarSprite->setPosition(origin.x + 200 + pillarSprite->getContentSize().width / 2, origin.y + pillarSprite->getContentSize().height / 2);
		pillarSprites.pushBack(pillarSprite);

		pillarSprite = Sprite::createWithSpriteFrameName(s_scene_3_pillars[2]);
		pillarSprite->retain();
		pillarSprite->setPosition(origin.x + visibleSize.width + 100 + pillarSprite->getContentSize().width / 2, origin.y + pillarSprite->getContentSize().height / 2);
		pillarSprites.pushBack(pillarSprite);

		auto stickSprite = Sprite::createWithSpriteFrameName(s_stick);
		auto spite = pillarSprites.at(0);
		
		// attention how to set anchor point
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
	if (status != GAME_STATUS_READY)
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
	if (status != GAME_STATUS_ON_GOING)
	{
		return;
	}
	CCLOG("ontouchend");
	unschedule(schedule_selector(GameLayer::longerStick));
	//currentStick->stopActionByTag(longerActionTag);
	currentStick->stopAllActions();

	float stickHeight = currentStick->getContentSize().height * currentStick->getScaleY();

	auto sprite1 = pillarSprites.at(1);
	float distanceBetweenPillars = sprite1->getPosition().x - sprite1->getContentSize().width / 2 
									- (currentPillar->getPosition().x + currentPillar->getContentSize().width / 2);
	if (stickHeight >= distanceBetweenPillars && stickHeight < distanceBetweenPillars + sprite1->getContentSize().width)
	{
	}
	else
	{
		status = GAME_STATUS_DYING;
	}
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
	auto sprite1 = pillarSprites.at(1);

	float stickHeight = currentStick->getContentSize().height * currentStick->getScaleY();
	auto moveBy = MoveBy::create(1, Vec2(stickHeight, 0));
	auto spawn = Spawn::createWithTwoActions(heroAnimate, moveBy);
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
	
	auto pillarSprite = pillarSprites.at(0);
	spritesNode->removeChild(pillarSprite, true);
	pillarSprites.eraseObject(pillarSprite, false);
	pillarSprite->release();

	// TODO random
	pillarSprite = Sprite::createWithSpriteFrameName(s_scene_3_pillars[0]);
	pillarSprite->retain();
	pillarSprite->setPosition(origin.x + visibleSize.width + 100, origin.y + pillarSprite->getContentSize().height / 2);
	pillarSprites.pushBack(pillarSprite);
	spritesNode->addChild(pillarSprite);
	currentPillar = pillarSprite;

	auto stickSprite = Sprite::createWithSpriteFrameName(s_stick);
	pillarSprite = pillarSprites.at(0);
	stickSprite->setAnchorPoint(Vec2(0.5, 0));
	stickSprite->retain();
	stickSprite->setPosition(pillarSprite->getPosition().x + pillarSprite->getContentSize().width / 2, 
								pillarSprite->getPosition().y + pillarSprite->getContentSize().height / 2);
	stickSprites.pushBack(stickSprite);
	currentStick = stickSprite;
	spritesNode->addChild(currentStick);

	for each (Sprite* sprite in stickSprites)
	{
		if (!sprite->isVisible())
		{
			spritesNode->removeChild(sprite, true);
			stickSprites.eraseObject(sprite, false);
			sprite->release();
		}
	}

}

