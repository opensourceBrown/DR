#ifndef __MAINGAME_TOOL_BAR_H__
#define __MAINGAME_TOOL_BAR_H__

#include "BaseLayer.h"

class MainGameToolBar: public BaseLayer
{
public:
	MainGameToolBar();
	virtual ~MainGameToolBar();
    
    static MainGameToolBar *create();

    virtual void onEnter();
	virtual void onExit();
    
    void    addMagic(int pID);
    void    resetMagicSkill();
    
    void    magicItemClicked(CCObject *pSender);

private:
	void constructUI();
    
    void menuItemClicked(CCObject *pSender);
    void statusItemClicked(CCObject *pSender);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

private:
	CCLayerColor			*m_containerLayer;
    CCArray                 *m_magicArray;
};

#endif
