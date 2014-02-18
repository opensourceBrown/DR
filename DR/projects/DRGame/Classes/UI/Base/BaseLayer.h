#ifndef __BASE_LAYER_H__
#define __BASE_LAYER_H__

#include "cocos2d.h"
#include "BaseController.h"
#include "GameConstant.h"
#include "Functions.h"

USING_NS_CC;

class BaseLayer : public cocos2d::CCLayer
{
public:
	BaseLayer(){}
	virtual ~BaseLayer(){}

    virtual void onEnter();
	virtual void onExit();

	bool initWithDelegate(BaseController *pDelegate);
	void setDelegate(BaseController *pDelegate);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

private:
	bool init();

public:
	BaseController		*m_delegate;

};

#endif
