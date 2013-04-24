#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "IntroScene.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
/*
Assignment 1.4 Requirements:
Provide a means for the "player" sprite to move.
Remember: This is a mobile game... no keyboard.
Add another type of "monster" sprite, with a different movement pattern.
Create another "Scene" (with it's own CCLayer).
Ideas:  A "start" screen, main menu, options, or highscores
 */

HelloWorld::HelloWorld()
: _monsters( NULL )
, _projectiles( NULL )
, _monstersDestroyed( 0 )
{
}


HelloWorld::~HelloWorld()
{
	if( _monsters )
	{
		_monsters->release();
		_monsters = NULL;
	}
	
	if( _projectiles )
	{
		_projectiles->release();
		_projectiles = NULL;
	}
}


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
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
    if ( !CCLayerColor::initWithColor( ccc4( 255, 255, 255, 255 ) ) )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
	
	 winSize = CCDirector::sharedDirector()->getWinSize();
    projectileVelocity =1580; //pixels per second
    
    //**** PLAY HERE TO FIGURE OUT CLIPPING ******
    player = CCSprite::create( "player.png", CCRectMake( 0, 0, 54, 80 ) );
	player->setPosition( ccp( player->getContentSize().width/2, winSize.height/2 ) );
	this->addChild( player );
    
    // ***MOVE PLAYER***
    playerMinDuration = 2;
    playerMaxDuration = 4;
    playerRangeDuration = playerMaxDuration - playerMinDuration;
    playerActualDuration = ( rand() % playerRangeDuration ) + playerMinDuration;
    
    CCFiniteTimeAction *upAction = CCMoveTo::create( playerActualDuration, ccp(player->getContentSize().width/2, winSize.height-player->getContentSize().height));
    
    CCFiniteTimeAction* upActionDone = CCCallFuncN::create( this,  callfuncN_selector(HelloWorld::playerUpFinished));
	
    player->runAction(CCSequence::create( upAction, upActionDone, NULL ));
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	srand( time( NULL ) );
#else
	// Other platforms
#endif
    
	_monsters = new CCArray;
	_projectiles = new CCArray;
    
	this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );
	this->schedule( schedule_selector(HelloWorld::updateGame) );
    
	this->setTouchEnabled( true );
    
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic( "Sounds/background-music-aac.mp3", true );
    
    return true;
}


void HelloWorld::gameLogic( float deltaTime )
{
	this->addMonster();
}


void HelloWorld::addMonster()
{
    if(rand()%10  >2 )
    {
        addCrazyMonster();
        return;
    }
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	CCSprite *monster = CCSprite::create( "monster.png", CCRectMake( 0, 0, 54, 80 ) );
	int minY = monster->getContentSize().height/2;
	int maxY = winSize.height - monster->getContentSize().height/2;
	int rangeY = maxY - minY;
	int actualY = ( rand() % rangeY ) + minY;
	monster->setPosition( ccp( winSize.width + monster->getContentSize().width/2, actualY ) );
	this->addChild( monster );
    
	// Determine speed of the monster
	int minDuration = 2;
	int maxDuration = 4;
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = ( rand() % rangeDuration ) + minDuration;
    
	CCFiniteTimeAction *action = CCMoveTo::create( actualDuration, ccp( 0 - monster->getContentSize().width/2, actualY ) );
	CCFiniteTimeAction *actionDone = CCCallFuncN::create( this, callfuncN_selector(HelloWorld::spriteMoveFinished) );
	monster->runAction( CCSequence::create( action, actionDone, NULL ) );
    
	monster->setTag( 1 );
	_monsters->addObject( monster );
}

void HelloWorld::addCrazyMonster()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	CCSprite *monster = CCSprite::create( "crazy_monster.png", CCRectMake( 0, 0, 54, 80 ) );
	int minY = monster->getContentSize().height/2;
	int maxY = winSize.height - monster->getContentSize().height/2;
	int rangeY = maxY - minY;
	int actualY = ( rand() % rangeY ) + minY;
	monster->setPosition( ccp( winSize.width + monster->getContentSize().width/2, actualY ) );
	this->addChild( monster );
    
	// Determine speed of the monster
	int minDuration = 2;
	int maxDuration = 4;
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = ( rand() % rangeDuration ) + minDuration;
    
	CCFiniteTimeAction *action = CCMoveTo::create( actualDuration, ccp( 0 - monster->getContentSize().width/2, ( rand() % rangeY ) + minY));
	CCFiniteTimeAction *actionDone = CCCallFuncN::create( this, callfuncN_selector(HelloWorld::spriteMoveFinished) );
	monster->runAction( CCSequence::create( action, actionDone, NULL ) );
    
	monster->setTag( 1 );
	_monsters->addObject( monster );

    
}


void HelloWorld::spriteMoveFinished( CCNode* sender )
{
	CCSprite *sprite = (CCSprite *)sender;
	this->removeChild( sprite, true );
    
	if( sprite->getTag() == 1 )
	{
		_monsters->removeObject( sprite );
        
		GameOverScene* gameOverScene = GameOverScene::create();
		gameOverScene->getLayer()->getLabel()->setString( "You Lose!" );
		CCDirector::sharedDirector()->replaceScene( gameOverScene );
	}
	else if( sprite->getTag() == 2 )
	{
		_projectiles->removeObject( sprite );
	}
}


void HelloWorld::playerUpFinished( CCNode* sender )
{
    playerActualDuration = ( rand() % playerRangeDuration ) + playerMinDuration;
    CCSprite *player = (CCSprite *)sender;
    CCFiniteTimeAction *downAction = CCMoveTo::create( playerActualDuration, ccp(player->getContentSize().width/2, 0) );
    CCFiniteTimeAction* downActionDone = CCCallFuncN::create( this,  callfuncN_selector(HelloWorld::playerDownFinished));
    player->runAction( CCSequence::create( downAction, downActionDone, NULL ));

}

void HelloWorld::playerDownFinished( CCNode* sender )
{
    playerActualDuration = ( rand() % playerRangeDuration ) + playerMinDuration;
    CCSprite *player = (CCSprite *)sender;
    CCFiniteTimeAction *upAction = CCMoveTo::create( playerActualDuration, ccp(player->getContentSize().width/2, winSize.height - player->getContentSize().height/2) );
    CCFiniteTimeAction* upActionDone = CCCallFuncN::create( this,  callfuncN_selector(HelloWorld::playerUpFinished));
    player->runAction( CCSequence::create( upAction, upActionDone, NULL ));
	
}

void HelloWorld::ccTouchesEnded( CCSet* touches, CCEvent* event )
{
	CCTouch* touch = (CCTouch*)( touches->anyObject() );
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL( location );
    
	// Set up initial position of projectile
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *projectile = CCSprite::create( "projectile.png", CCRectMake( 0, 0, 40, 40 ) );
	projectile->setPosition( ccp( 20, player->getPositionY()));
	
	// Determine offset of location to projectile
	int offX = location.x - projectile->getPositionX();
	int offY = location.y - projectile->getPositionY();
    
	// Bail out if we are shooting down or backwards
	if( offX <= 0 )
		return;
    
	// Ok to add now - we've double checked position
	this->addChild( projectile );
    
	// Determine where we wish to shoot the projectile to
	int realX = winSize.width + (projectile->getContentSize().width/2);
	float ratio = (float)offY / (float)offX;
	int realY = (realX * ratio) + projectile->getPosition().y;
	CCPoint realDest = ccp( realX, realY );
    
	// Determine the length of how far we're shooting
	int offRealX = realX - projectile->getPosition().x;
	int offRealY = realY - projectile->getPosition().y;
	float length = sqrtf( (offRealX*offRealX) + (offRealY*offRealY) );
	
	float realMoveDuration = length / projectileVelocity;
    
	// Move projectile to actual endpoint
	projectile->runAction( CCSequence::create(
                                              CCMoveTo::create( realMoveDuration, realDest ),
                                              CCCallFuncN::create( this, callfuncN_selector( HelloWorld::spriteMoveFinished ) ),
                                              NULL ) );
    
	projectile->setTag( 2 );
	_projectiles->addObject( projectile );
    
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect( "Sounds/pew-pew-lei.mp3" );
}


void HelloWorld::updateGame( float dt )
{
	CCArray *projectilesToDelete = new CCArray;
	CCObject* iterProj = NULL;
	CCObject* iterMonster = NULL;
    
    
	CCARRAY_FOREACH( _projectiles, iterProj )
	{
		CCSprite *projectile = dynamic_cast<CCSprite*>(iterProj);
		CCRect projectileRect = CCRectMake(
                                           projectile->getPosition().x - (projectile->getContentSize().width/2),
                                           projectile->getPosition().y - (projectile->getContentSize().height/2),
                                           projectile->getContentSize().width,
                                           projectile->getContentSize().height );
        
		CCArray *monstersToDelete = new CCArray;
        
		CCARRAY_FOREACH( _monsters, iterMonster )
		{
			CCSprite *monster = dynamic_cast<CCSprite *>(iterMonster);
			CCRect monsterRect = CCRectMake(
                                            monster->getPosition().x - (monster->getContentSize().width/2),
                                            monster->getPosition().y - (monster->getContentSize().height/2),
                                            monster->getContentSize().width,
                                            monster->getContentSize().height );
            
			if( projectileRect.intersectsRect( monsterRect ) )
			{
				// TODO: Increase score.
				monstersToDelete->addObject( monster );
			}
		}
        
        
        
		CCARRAY_FOREACH( monstersToDelete, iterMonster )
		{
			CCSprite *monster = dynamic_cast<CCSprite *>(iterMonster);
			_monsters->removeObject( monster );
			this->removeChild( monster );
            
			_monstersDestroyed++;
			if( _monstersDestroyed >= 20 )
			{
				GameOverScene* gameOverScene = GameOverScene::create();
				gameOverScene->getLayer()->getLabel()->setString( "You Win!" );
				CCDirector::sharedDirector()->replaceScene( gameOverScene );
			}
		}
        
		if( monstersToDelete->count() > 0 )
		{
			projectilesToDelete->addObject( projectile );
		}
		monstersToDelete->release();
	}
    
	CCARRAY_FOREACH( projectilesToDelete, iterProj )
	{
		CCSprite *projectile = dynamic_cast<CCSprite *>(iterProj);
		_projectiles->removeObject( projectile );
		this->removeChild( projectile );
	}
	projectilesToDelete->release();
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
