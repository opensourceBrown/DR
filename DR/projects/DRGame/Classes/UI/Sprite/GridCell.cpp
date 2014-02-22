#include "GridCell.h"

GridCell::GridCell()
{
    /**
     *  TODO：CCSprite用继承的方式定义会出现执行问题
     *  初始化Texture保证创建ShaderProgram，不用继承后可以删除该初始化
     */
    //initWithTexture(NULL, CCRectZero);
}

GridCell::~GridCell()
{

}

GridCell* GridCell::createWithFrameName(const char *pszFileName)
{
    GridCell *cell = new GridCell();
    if (cell && cell->initWith(pszFileName))
    {
        cell->autorelease();
        
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}

bool GridCell::initWith(const char *pszFileName)
{
    bool tRet=false;
    
    do {
        CC_BREAK_IF(!pszFileName);
        CCSprite *gridImg=CCSprite::createWithSpriteFrameName(pszFileName);
        CC_BREAK_IF(!gridImg);
        addChild(gridImg);
        
        tRet=true;
    } while (0);
    
    return tRet;
}

void GridCell::setCellProperty(GridElementProperty pElement)
{
    
}

/*
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
 */

