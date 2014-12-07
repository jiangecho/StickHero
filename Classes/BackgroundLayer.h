#pragma once

#include "cocos2d.h"
#include "GameLayer.h"
#include "Game.h"

using namespace cocos2d;
using namespace std;

class BackgroundLayer : public Layer
{
public:
	BackgroundLayer();
	~BackgroundLayer();
	virtual bool init();
	CREATE_FUNC(BackgroundLayer);

	void moveLeft(float duration, float deltaX);
	void onMoveOver();
	void setSkinType(int mode);
	void moveLeft();

private:

	// TODO the SkinType should be maintain by the scene
	// TODO should retain the members
	Vector<Sprite* > sprites;
	Sprite* groundSprite;
	Node* spriteNodes;
	LayerColor* layerColor;
};

