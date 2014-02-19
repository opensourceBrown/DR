#ifndef __GRID_CELL_H__
#define __GRID_CELL_H__

#include "cocos2d.h"
#include "GameConstant.h"
#include "DataConstant.h"
#include "Functions.h"
#include "GeneralDataModel.h"

USING_NS_CC;

typedef struct{
	unsigned int		rIndex;			//––À˜“˝£∫∆ º÷µŒ™1
	unsigned int		vIndex;			//¡–À˜“˝£∫∆ º÷µŒ™1
}GIRDCELL_INDEX;

class GridCell : public CCSprite
{
public:
	GridCell();
	virtual ~GridCell();

	void setCellIndex(GIRDCELL_INDEX pIndex,GRIDINDEX_TYPE pType=kGRIDINDEX_TYPE_DEFAULT);

	GIRDCELL_INDEX getCellIndex(GRIDINDEX_TYPE pType);
    void setCellElementType(ElementType pType=kElementType_Medicine);

private:
	GIRDCELL_INDEX		m_index;					//◊‘…ÌµƒÀ˜“˝£∫ƒ¨»œŒ™£®0£¨0£©
	GIRDCELL_INDEX		m_nextIndex;				//¡¨Ω”œ¬“ª∏ˆcellµƒÀ˜“˝£∫ƒ¨»œŒ™£®0£¨0£©
	GIRDCELL_INDEX		m_preIndex;				//¡¨Ω”…œ“ª∏ˆcellµƒÀ˜“˝£∫ƒ¨»œŒ™£®0£¨0£©
    
    ElementType         m_type;

};

#endif
