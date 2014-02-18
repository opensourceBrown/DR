#ifndef __GRID_CELL_H__
#define __GRID_CELL_H__

#include "cocos2d.h"
#include "GameConstant.h"
#include "Functions.h"
#include "GeneralDataModel.h"

USING_NS_CC;

typedef struct{
	unsigned int		rIndex;			//行索引：起始值为1
	unsigned int		vIndex;			//列索引：起始值为1
}GIRDCELL_INDEX;

class GridCell : public CCSprite
{
public:
	GridCell();
	virtual ~GridCell();

	void setCellIndex(GIRDCELL_INDEX pIndex,GRIDINDEX_TYPE pType=kGRIDINDEX_TYPE_DEFAULT);

	GIRDCELL_INDEX getCellIndex(GRIDINDEX_TYPE pType);
    void setCellElementType(ElementType pType=kElementType_Posion);

private:
	GIRDCELL_INDEX		m_index;					//自身的索引：默认为（0，0）
	GIRDCELL_INDEX		m_nextIndex;				//连接下一个cell的索引：默认为（0，0）
	GIRDCELL_INDEX		m_preIndex;				//连接上一个cell的索引：默认为（0，0）
    
    ElementType         m_type;

};

#endif
