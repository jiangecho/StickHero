#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "StatusLayer.h"
#include "GameLayer.h"
#include "MainMenuLayer.h"
#include "Game.h"

using namespace cocos2d;

class HelloWorld : public Scene, public GameEventDelegate, public MainMenuDelegate
{
public:
	HelloWorld();
	~HelloWorld();
	virtual bool init();
	void onGetScore();
	void onGameStatus(GameStatus status);
	void onMoveHeroRight();
	void onMenuModeNormalCallBack();
	void onMenuModeFeelingCallback();

    CREATE_FUNC(HelloWorld);


private:
	void restart();
	BackgroundLayer* backgroundLayer;
	GameLayer* gameLayer;
	MainMenuLayer* mainMenuLayer;
	StatusLayer* statusLayer;
	ControlLayer* controlLayer;
	Game* game;

	const int BACKGROUND_LAYER_TAG = 0;

};

#endif // __HELLOWORLD_SCENE_H__
