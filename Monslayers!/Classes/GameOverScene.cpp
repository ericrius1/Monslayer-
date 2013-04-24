#include "GameOverScene.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

bool GameOverScene::init()
{
	if( CCScene::init() )
	{
		this->_layer = GameOverLayer::create();
		this->_layer->retain();
		this->addChild( _layer );
		return true;
	}
	else
		return false;
}


GameOverScene::~GameOverScene()
{
	if( _layer )
	{
		_layer->release();
		_layer = NULL;
	}
}


bool GameOverLayer::init()
{
	if( CCLayerColor::initWithColor( ccc4( 255, 255, 255, 255 ) ) )
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		this->_label = CCLabelTTF::create( "Start", "fonts/Marker Felt.ttf", 32 );
		_label->retain();
		_label->setColor( ccc3( 0, 0, 0) );
		_label->setPosition( ccp( winSize.width/2, winSize.height/2 ) );
		this->addChild( _label );

		this->runAction( CCSequence::create(
			CCDelayTime::create( 3.0 ),
			CCCallFunc::create( this, callfunc_selector(GameOverLayer::gameOverDone)),
			NULL));

		return true;
	}
	else
		return false;
}


GameOverLayer::~GameOverLayer()
{
	if( _label )
	{
		_label->release();
		_label = NULL;
	}
}


void GameOverLayer::gameOverDone()
{
	CCDirector::sharedDirector()->replaceScene( HelloWorld::scene() );
}