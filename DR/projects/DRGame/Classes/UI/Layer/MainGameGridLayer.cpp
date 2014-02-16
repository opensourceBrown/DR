#include "MainGameGridLayer.h"

void MainGameGridLayer::onEnter()
{
	BaseLayer::onEnter();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0-TOUCH_EVENT_PRIORITY_DEFAULT, true);
}

void MainGameGridLayer::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

	BaseLayer::onExit();
}

bool MainGameGridLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void MainGameGridLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void MainGameGridLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void MainGameGridLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}

void  MainGameGridLayer::constructUI()
{

}

void MainGameGridLayer::updateGridCell()
{

}

void MainGameGridLayer::moveGridCellAnimation(unsigned int pIdx)
{

}
