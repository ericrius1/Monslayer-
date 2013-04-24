#ifndef _INTRO_SCENE_H_
#define _INTRO_SCENE_H_

#include "cocos2d.h"

class IntroLayer : public cocos2d::CCLayerColor
{
public:
	IntroLayer() : _label(NULL)	{};
	virtual ~IntroLayer();
	bool init();
	CREATE_FUNC(IntroLayer);
	
	void introDone();

	CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label );
};

class IntroScene : public cocos2d::CCScene
{
public:
	IntroScene() : _layer(NULL)	{};
	virtual ~IntroScene();
	bool init();
	CREATE_FUNC(IntroScene);

	CC_SYNTHESIZE_READONLY( IntroLayer*, _layer, Layer );
};

#endif	// _INTRO_SCENE_H_
