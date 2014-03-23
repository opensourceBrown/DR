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
    void moveGridCellWithIndex(unsigned int index, float duration);
    void refreshGrid(float pDelta);
    
    void removeGridCellCompleteCallback(CCObject *pSender);
    void exchangePositionOfGridCell(unsigned int rIndex, unsigned int vIndex);          //交换GridCell的位置
    void moveGridCellAnimation(unsigned int rIndex,unsigned int vIndex, float duration);
    bool rectContainPoint(CCRect pRect,CCPoint pPoint);
    void triggerBossSkill();                                            //触发boss技能

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    void                    refreshMonsterPropertyLabelOfAllGridCell();
    void                    recoverMonsterLifeFull();                  //恢复所有怪物生命到最大
private:
	CCLayerColor			*m_containerLayer;
	CCArray					*m_GridCellArray;
    CCArray                 *m_gridCellConnLineArray;

    GridCell                *m_currentSelCell;
};

#endif
