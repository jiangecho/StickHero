#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "StatusLayer.h"
#include "GameLayer.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void menuModeNormalCallback(cocos2d::Ref* pSender);

	void menuSpeakerCallBack(cocos2d::Ref* pSender);
	void HelloWorld::menuModeFeelingCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	// TODO just for test
	CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);

private:
	const int BACKGROUND_LAYER_TAG = 0;

	Menu* menu;
};

#endif // __HELLOWORLD_SCENE_H__
