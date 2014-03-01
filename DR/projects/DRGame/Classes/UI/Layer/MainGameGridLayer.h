#ifndef __MAINGAME_GRID_LAYER_H__
#define __MAINGAME_GRID_LAYER_H__

#include "BaseLayer.h"
#include "GeneralDataModel.h"
#include "GridElementProperty.h"

class GridCell;
class MainGameGridLayer : public BaseLayer
{
public:
	MainGameGridLayer();
	virtual ~MainGameGridLayer();
    
    static MainGameGridLayer *create();

    virtual void onEnter();
	virtual void onExit();

    void addGridCell(unsigned int rIndex,unsigned int vIndex);
    void removeGridCell(unsigned int rIndex,unsigned int vIndex);
    void updateGrid();
    
    GridCell *getGridCell(unsigned int rIndex,unsigned int vIndex);
private:
    void constructUI();
    void addGridCellToLayer(GridElementProperty *gProperty);
    
    void removeGridCellCompleteCallback(CCObject *pSender);
	void moveGridCellAnimation(unsigned int rIndex,unsigned int vIndex);				//����cell����
    bool rectContainPoint(CCRect pRect,CCPoint pPoint);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

private:
	CCLayerColor			*m_containerLayer;
	CCArray					*m_GridCellArray;

    GridCell                *m_currentSelCell;
};

#endif
