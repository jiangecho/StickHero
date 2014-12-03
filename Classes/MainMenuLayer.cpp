#include "MainMenuLayer.h"
#include "HelloWorldScene.h"


MainMenuLayer::MainMenuLayer()
{
}


MainMenuLayer::~MainMenuLayer()
{
}

bool MainMenuLayer :: init()
{
	if (!Layer::init())
	{
		return false;
	}
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto normalItem = MenuItemImage::create("normal_cn.png", 
											"normal_cn_pressed.png", 
											CC_CALLBACK_1(MainMenuLayer::menuModeNormalCallback, this));

	normalItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 4 / 5));

	auto feelingItem = MenuItemImage::create("feeling_cn.png",
											"feeling_cn_pressed.png",
											CC_CALLBACK_1(MainMenuLayer::menuModeFeelingCallback, this));
	feelingItem->setPosition(Vec2(origin.x + visibleSize.width /2, visibleSize.height * 3 / 5));

	auto menu = Menu::create(normalItem, feelingItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void MainMenuLayer::menuModeNormalCallback(Ref* pSender)
{
	this->delegate->onMenuModeNormalCallBack();
}

void MainMenuLayer::menuModeFeelingCallback(Ref* pSender)
{
	this->delegate->onMenuModeFeelingCallback();
}
