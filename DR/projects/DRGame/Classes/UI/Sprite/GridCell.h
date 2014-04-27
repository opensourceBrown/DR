#ifndef __GRID_CELL_H__
#define __GRID_CELL_H__

#include "cocos2d.h"
#include "GameConstant.h"
#include "DataConstant.h"
#include "GeneralDataModel.h"
#include "GridElementProperty.h"

USING_NS_CC;

class GridCell : public CCNode
{
public:
	GridCell();
	virtual ~GridCell();
    
    static GridCell* createWithFrameName(const char *pszFileName);

    void refreshCell(const char *pszFileName);
    void refreshMonsterPropertyLabel();         //refresh Monster`s attack,defence or life
    void refreshCountLabel();
    
    void setCellProperty(GridElementProperty *pElement);
    GridElementProperty *getCellProperty(){return m_property;}
    
    void setStatus(bool pStatus){m_status=pStatus;}
    bool getStatus(){return m_status;}
    
    float getGridNodeWidth(){return m_elementGridImg->getContentSize().width;}
    float getGridNodeHeight(){return m_elementGridImg->getContentSize().height;}

private:
    bool initWith(const char *pszFileName);
    void constructMonsterCellEX();
    void setCountLabelStatus(bool pValue);
private:
    CCSprite            *m_elementGridImg;
    GridElementProperty *m_property;             //cell对应的结构属性
    
    bool                m_status;                   //true:added    false:unadded
    
    CCLabelTTF          *m_AttackValueTTF;
    CCLabelTTF          *m_DefenceValueTTF;
    CCLabelTTF          *m_LifeValueTTF;
    CCLabelTTF          *m_countValueTTF;
};

#endif
