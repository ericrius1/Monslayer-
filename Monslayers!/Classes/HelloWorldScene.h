#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

//class CCSet;

class HelloWorld : public cocos2d::CCLayerColor
{
public:
	HelloWorld();
	virtual ~HelloWorld();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
	void addMonster();
    
    // a selector callback
    void menuCloseCallback( CCObject* pSender);
	void spriteMoveFinished( CCNode* sender );
    void playerDownFinished(CCNode* sender);
    void playerUpFinished(CCNode* sender);
	void gameLogic( float deltaTime );
	void ccTouchesEnded( cocos2d::CCSet* touches, cocos2d::CCEvent* event );
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
protected:
	cocos2d::CCArray *_monsters;
	cocos2d::CCArray *_projectiles;
    cocos2d::CCSprite *player;
	int _monstersDestroyed;
	void updateGame( float dt );
    cocos2d::CCSize winSize;
        cocos2d::CCFiniteTimeAction *downAction;
    cocos2d::CCFiniteTimeAction *upActionDone;
    cocos2d::CCFiniteTimeAction *downActionDone;
    
    int playerMinDuration;
	int playerMaxDuration;
	int playerRangeDuration;
    int playerActualDuration;

    
    
};

#endif // __HELLOWORLD_SCENE_H__
