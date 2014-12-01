#pragma once

#include "cocos2d.h"

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

	const static int SKIN_TYPE_0 = 0;
	const static int SKIN_TYPE_1 = 1;

	// just for test
	void testMenuCallBack(Ref* pSender);

private:
	Vector<Sprite* > upSprites;
	Vector<Sprite* > downSprites;
	Sprite* pGroundSprite;
	Sprite* backGroundSprite;
	Node* spriteNodes;
	LayerColor* layerColor;

	// TODO the skin should be control be the scene
	int skinType;
};

