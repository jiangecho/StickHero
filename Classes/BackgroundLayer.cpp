#include "BackgroundLayer.h"
#include "Resource.h"


BackgroundLayer::BackgroundLayer() : groundSprite(nullptr), spriteNodes(nullptr), layerColor(nullptr)
{
}


BackgroundLayer::~BackgroundLayer()
{
	CC_SAFE_RELEASE(groundSprite);
	CC_SAFE_RELEASE(layerColor);
	CC_SAFE_RELEASE(spriteNodes);
	sprites.clear();
}

bool BackgroundLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	if (sprites.size() == 0) // do not call setMode
	{
		setSkinType(Game::getInstance()->getSkinType());
	}

	this->addChild(groundSprite);
	this->addChild(spriteNodes);

	// just for test
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	return true;
}

void BackgroundLayer::moveLeft(float duration, float deltaX)
{
	auto moveBy = MoveBy::create(duration, Vec2(-deltaX, 0));
	//auto callF = CallFunc::create(bind(&BackgroundLayer::onMoveOver, this));
	auto callF = CallFunc::create(CC_CALLBACK_0(BackgroundLayer::onMoveOver, this));
	auto squence = Sequence::createWithTwoActions(moveBy, callF);
	spriteNodes->runAction(squence);
}

void BackgroundLayer::onMoveOver()
{
	auto sprite = sprites.at(0);
	if (sprintf == nullptr)
	{
		return;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto leftSpriteWorldPosition = spriteNodes->convertToWorldSpace(sprite->getPosition());
	if (leftSpriteWorldPosition.x + (sprite->getContentSize().width * sprite->getScaleX() / 2) < 0)
	{
		sprites.eraseObject(sprite, false);
		for each (Sprite* sprite in sprites)
		{
			auto position = spriteNodes->convertToWorldSpace(sprite->getPosition());
			sprite->setPosition(position);
		}
		spriteNodes->setPosition(origin);
		sprite->setPosition(origin.x + visibleSize.width + sprite->getContentSize().width / 2, sprite->getPosition().y);
		sprites.pushBack(sprite);
	}


}

void BackgroundLayer::setSkinType(int type)
{
	CC_SAFE_RELEASE(groundSprite);
	CC_SAFE_RELEASE(layerColor);
	// do not release spriteNodes here
	sprites.clear();

	if (spriteNodes != nullptr)
	{
		spriteNodes->removeAllChildren();
	}
	else
	{
		spriteNodes = Node::create();
		spriteNodes->retain();
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// TODO do not use swith case to find the right resource
	switch (type)
	{
		case SKIN_TYPE_0:
		groundSprite = Sprite::create(s_scene_grounds[2]);
		groundSprite->retain();
		groundSprite->setPosition(Vec2(origin.x + visibleSize.width /2, origin.y + groundSprite->getContentSize().height / 2));
		groundSprite->setScaleX(visibleSize.width / groundSprite->getContentSize().width);

		// add a color back ground
		layerColor = LayerColor::create(ccc4(5, 31, 67, 200));
		layerColor->retain();
		this->addChild(layerColor);

		auto sprite = Sprite::create(s_scene_3_stars[0]);
		sprite->setPosition(Vec2(origin.x + sprite->getContentSize().width / 2, origin.y + visibleSize.height * 3 / 4));
		sprite->setScale(0.5);
		spriteNodes->addChild(sprite);
		sprites.pushBack(sprite);

		sprite = Sprite::create(s_scene_3_stars[1]);
		sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 3 / 5));
		spriteNodes->addChild(sprite);
		sprites.pushBack(sprite);

		sprite = Sprite::create(s_scene_3_stars[2]);
		sprite->setPosition(Vec2(origin.x + visibleSize.width / 2 + sprite->getContentSize().width / 2, origin.y + visibleSize.height * 4 / 5));
		sprite->setScale(0.5);
		spriteNodes->addChild(sprite);
		sprites.pushBack(sprite);

		sprite = Sprite::create(s_scene_3_stars[3]);
		sprite->setPosition(Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height * 2 / 3));
		sprite->setScale(0.5);
		spriteNodes->addChild(sprite);
		sprites.pushBack(sprite);


		// TODO downSprites

		break;
	//case SKIN_TYPE_1:

	//	break;
	}
}

void BackgroundLayer::moveLeft()
{
	moveLeft(1, 100);
}


