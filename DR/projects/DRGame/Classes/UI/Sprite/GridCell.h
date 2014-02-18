#ifndef __GRID_CELL_H__
#define __GRID_CELL_H__

#include "cocos2d.h"
#include "GameConstant.h"
#include "Functions.h"

USING_NS_CC;

class GridCell : public CCSprite
{
public:
	GridCell();
	virtual ~GridCell();

	//设置cell的索引，rIdx:行索引，vIdx:列索引
	void setCellIndex(GIRDCELL_INDEX pIndex,GRIDINDEX_TYPE pType);
	GIRDCELL_INDEX getCellIndex(GRIDINDEX_TYPE pType);

private:
	GIRDCELL_INDEX		m_index;					//自身的索引：默认为（0，0）
	GIRDCELL_INDEX		m_nextIndex;				//连接下一个cell的索引：默认为（0，0）
	GIRDCELL_INDEX		m_preIndex;                 //连接上一个cell的索引：默认为（0，0）

};

#endif
