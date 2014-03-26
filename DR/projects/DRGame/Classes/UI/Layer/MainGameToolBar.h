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
    
    void    addMagic(MagicType pID);
    void    resetMagicSkill();
    void    magicItemClicked(CCObject *pSender);
    void    refreshMagicCD(int pValue);                 //test
    
    //test
    void    weaponItemClicked(CCObject *pSender);
    void    refreshWeapon();

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
    
    CCLabelTTF              *m_magicCDTTF;
};

#endif
