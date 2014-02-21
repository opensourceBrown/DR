#ifndef __MAINGAME_GRID_LAYER_H__
#define __MAINGAME_GRID_LAYER_H__

#include "BaseLayer.h"
#include "GeneralDataModel.h"

class MainGameGridLayer : public BaseLayer
{
public:
	MainGameGridLayer();
	virtual ~MainGameGridLayer();

    virtual void onEnter();
	virtual void onExit();

	void constructUI();
	void updateGridCell();

private:
	void moveGridCellAnimation(unsigned int pIdx);				//ÏÂÒÆcell¶¯»­
    bool rectContainPoint(CCRect pRect,CCPoint pPoint);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

private:
	CCLayerColor				*m_containerLayer;
	CCArray					*m_GridCellArray;

};

#endif
