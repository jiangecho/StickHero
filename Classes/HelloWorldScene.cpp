#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld::HelloWorld()
{

}

HelloWorld::~HelloWorld()
{
	CC_SAFE_RELEASE(backgroundLayer);
	CC_SAFE_RELEASE(mainMenuLayer);
	CC_SAFE_RELEASE(gameLayer);
	CC_SAFE_RELEASE(statusLayer);
	CC_SAFE_RELEASE(controlLayer);

}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// TODO just load the plist here?
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("elements.plist");

	mainMenuLayer = MainMenuLayer::create();
	mainMenuLayer->retain();
	mainMenuLayer->setDelegator(this);

	gameLayer = GameLayer::create();
	gameLayer->retain();
	gameLayer->setDelegator(this);

	controlLayer = ControlLayer::create();
	controlLayer->retain();
	controlLayer->setDelegator(gameLayer);

	backgroundLayer = BackgroundLayer::create();
	backgroundLayer->retain();
	statusLayer = StatusLayer::create();
	statusLayer->retain();

	auto initialBackgroundLayer = BackgroundLayer::create();
	this->addChild(initialBackgroundLayer, 0, BACKGROUND_LAYER_TAG);
	this->addChild(mainMenuLayer, 100);

	game = Game::getInstance();
    return true;
}

/*
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
*/

void HelloWorld::onGetScore()
{
	statusLayer->updateScore(game->getScore());
	statusLayer->hidePrompt();
}

void HelloWorld::onGameStatus(GameStatus status)
{
	if (status == GAME_STATUS_DEAD)
	{
		mainMenuLayer->setVisible(true);
	}
}
void HelloWorld::onMoveHeroRight()
{
	backgroundLayer->moveLeft();
}

// TODO bug: only need to add the layers one time
void HelloWorld::onMenuModeNormalCallBack()
{
	game->setMode(MODE_NORMAL);

	this->removeChildByTag(BACKGROUND_LAYER_TAG);
	this->mainMenuLayer->setVisible(false);

	this->addChild(backgroundLayer, 0);

	this->addChild(gameLayer, 1);

	this->addChild(statusLayer, 2);

	this->addChild(controlLayer, 3);

}

void HelloWorld::onMenuModeFeelingCallback()
{

}

void HelloWorld::restart()
{

}
