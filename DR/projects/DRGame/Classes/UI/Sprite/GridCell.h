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

//	void setCellIndex(GIRDCELL_INDEX pIndex,GRIDINDEX_TYPE pType=kGRIDINDEX_TYPE_DEFAULT);
//
//	GIRDCELL_INDEX getCellIndex(GRIDINDEX_TYPE pType);
//    void setCellElementType(ElementType pType=kElementType_Medicine);
    void setCellProperty(GridElementProperty *pElement);
    GridElementProperty *getCellProperty(){return m_property;}
    
    void setStatus(bool pStatus){m_status=pStatus;}
    bool getStatus(){return m_status;}

private:
    bool initWith(const char *pszFileName);
private:
//	GIRDCELL_INDEX		m_index;					//◊‘…ÌµƒÀ˜“˝£∫ƒ¨»œŒ™£®0£¨0£©
//	GIRDCELL_INDEX		m_nextIndex;				//¡¨Ω”œ¬“ª∏ˆcellµƒÀ˜“˝£∫ƒ¨»œŒ™£®0£¨0£©
//	GIRDCELL_INDEX		m_preIndex;				//¡¨Ω”…œ“ª∏ˆcellµƒÀ˜“˝£∫ƒ¨»œŒ™£®0£¨0£©
    
    GridElementProperty *m_property;             //cell对应的结构属性
    
    bool                m_status;                   //true:added    false:unadded

};

#endif
