#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

	/*
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	*/



    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
	/*
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
	
	*/

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("elements.plist");
	auto normalItem = MenuItemImage::create("normal_cn.png", 
											"normal_cn_pressed.png", 
											CC_CALLBACK_1(HelloWorld::menuModeNormalCallback, this));

	normalItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 4 / 5));

	auto feelingItem = MenuItemImage::create("feeling_cn.png",
											"feeling_cn_pressed.png",
											CC_CALLBACK_1(HelloWorld::menuModeFeelingCallback, this));
	feelingItem->setPosition(Vec2(origin.x + visibleSize.width /2, visibleSize.height * 3 / 5));

	auto menu = Menu::create(normalItem, feelingItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("scene_3_ground.png");

    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	sprite->setPosition(Vec2::ZERO);

	// TODO how to scale to fill the screen
	//sprite->setScaleX(visibleSize.width / sprite->getContentSize().width);
	sprite->setScaleX(3);

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	auto backgroundLayer = BackgroundLayer::create();
	this->addChild(backgroundLayer, 0);

	auto gameLayer = GameLayer::create();
	this->addChild(gameLayer, 1);


	auto statusLayer = StatusLayer::create();
	this->addChild(statusLayer, 2);
	this->setDelegator(statusLayer);

	auto controlLayer = ControlLayer::create();
	controlLayer->setDelegator(gameLayer);
	this->addChild(controlLayer, 3);


    return true;
}


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

void HelloWorld::menuModeNormalCallback(Ref* pSender){
	this->delegator->updateScore(50);
}

void HelloWorld::menuModeFeelingCallback(Ref* pSender){
}
