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
    void exchangeGridCell(unsigned int rIndex,unsigned int vIndex);
    void removeGridCell(unsigned int rIndex,unsigned int vIndex);
    void updateGrid();
    
    GridCell *getGridCell(unsigned int rIndex,unsigned int vIndex);
    
    void addConnectLine(GridCell *fCell,GridCell *sCell);
    void removeConnectLine();
    void clearConnectLine();
private:
    void constructUI();
    void addGridCellToLayer(GridElementProperty *gProperty);
    void refreshGrid(float pDelta);
    
    void removeGridCellCompleteCallback(CCObject *pSender);
	void moveGridCellAnimation(unsigned int rIndex,unsigned int vIndex);				//ÏÂÒÆcell¶¯»­
    bool rectContainPoint(CCRect pRect,CCPoint pPoint);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

private:
	CCLayerColor			*m_containerLayer;
	CCArray					*m_GridCellArray;
    CCArray                 *m_gridCellConnLineArray;

    GridCell                *m_currentSelCell;
};

#endif
