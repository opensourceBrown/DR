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

	//����cell��������rIdx:��������vIdx:������
	void setCellIndex(GIRDCELL_INDEX pIndex,GRIDINDEX_TYPE pType);
	GIRDCELL_INDEX getCellIndex(GRIDINDEX_TYPE pType);

private:
	GIRDCELL_INDEX		m_index;					//�����������Ĭ��Ϊ��0��0��
	GIRDCELL_INDEX		m_nextIndex;				//������һ��cell��������Ĭ��Ϊ��0��0��
	GIRDCELL_INDEX		m_preIndex;				//������һ��cell��������Ĭ��Ϊ��0��0��

};

#endif
