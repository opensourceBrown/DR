#include "BaseLayer.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool BaseLayer::init()
{
	bool tRet=false;
    do{
		CC_BREAK_IF(!CCLayer::init());

		tRet=true;
	}while(0);
    
    return tRet;
}

bool BaseLayer::initWithDelegate(BaseController *pDelegate)
{
	bool tRet=init();
	do{
		CC_BREAK_IF(!pDelegate);
		m_delegate=pDelegate;

	}while(0);

	return tRet;
}

void BaseLayer::setDelegate(BaseController *pDelegate)
{
	m_delegate=pDelegate;
}

void BaseLayer::onEnter()
{
	CCLayer::onEnter();

}

void BaseLayer::onExit()
{

	CCLayer::onExit();
}

bool BaseLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void BaseLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void BaseLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void BaseLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}
