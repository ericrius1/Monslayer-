#include "IntroScene.h";
#include "HelloWorldScene.h";

using namespace cocos2d;

bool IntroScene::init()
{
	if( CCScene::init() )
	{
		this->_layer = IntroLayer::create();
		this->_layer->retain();
		this->addChild( _layer );
		return true;
	}
	else
		return false;
}


IntroScene::~IntroScene()
{
	if( _layer )
	{
		_layer->release();
		_layer = NULL;
	}
}


bool IntroLayer::init()
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
			CCCallFunc::create( this, callfunc_selector(IntroLayer::gameOverDone)),
			NULL));

		return true;
	}
	else
		return false;
}


IntroLayer::~IntroLayer()
{
	if( _label )
	{
		_label->release();
		_label = NULL;
	}
}


void IntroLayer::introDone()
{
	CCDirector::sharedDirector()->replaceScene( HelloWorld::scene() );
}