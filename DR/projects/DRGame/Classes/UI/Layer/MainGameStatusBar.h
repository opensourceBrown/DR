#ifndef __MAINGAME_STATUS_BAR_H__
#define __MAINGAME_STATUS_BAR_H__

#include "BaseLayer.h"

class MainGameStatusBar : public BaseLayer
{
public:
	MainGameStatusBar();
	virtual ~MainGameStatusBar();
    
    static MainGameStatusBar *create();

    virtual void onEnter();
	virtual void onExit();
private:
    void constructUI();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

private:
	CCLayerColor			*m_containerLayer;
};

#endif
