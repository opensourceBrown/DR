#include "GridCell.h"

GridCell::GridCell()
{

}

GridCell::~GridCell()
{

}

void GridCell::setCellIndex(GIRDCELL_INDEX pIndex,GRIDINDEX_TYPE pType)
{
	switch(pType){
	case kGRIDINDEX_TYPE_DEFAULT:
		{
			m_index.rIndex=pIndex.rIndex;
			m_index.vIndex=pIndex.vIndex;
		}
		break;
	case kGRIDINDEX_TYPE_NEXT:
		{
			m_nextIndex.rIndex=pIndex.rIndex;
			m_nextIndex.vIndex=pIndex.vIndex;
		}
		break;
	case kGRIDINDEX_TYPE_PRE:
		{
			m_preIndex.rIndex=pIndex.rIndex;
			m_preIndex.vIndex=pIndex.vIndex;
		}
		break;
	}
}

GIRDCELL_INDEX GridCell::getCellIndex(GRIDINDEX_TYPE pType)
{
    switch(pType){
        case kGRIDINDEX_TYPE_DEFAULT:
		{
			return m_index;
		}
            break;
        case kGRIDINDEX_TYPE_NEXT:
		{
			return m_nextIndex;
		}
            break;
        case kGRIDINDEX_TYPE_PRE:
		{
			return m_preIndex;
		}
            break;
	}
}

void GridCell::setCellElementType(ElementType pType)
{
	m_type=pType;
}

