#include "MainGameGridLayer.h"
#include "GridCell.h"

#define GRID_ROW			6
#define GRID_VOLUME         6


MainGameGridLayer::MainGameGridLayer()
{
    
}

MainGameGridLayer::~MainGameGridLayer()
{
    
}

void MainGameGridLayer::onEnter()
{
	BaseLayer::onEnter();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0-TOUCH_EVENT_PRIORITY_DEFAULT, true);
}

void MainGameGridLayer::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

	BaseLayer::onExit();
}

bool MainGameGridLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location;
	if(m_GridCellArray && m_GridCellArray->count()){
		for(int i=0;i<m_GridCellArray->count();i++){
			GridCell *cell=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(i));
			CC_BREAK_IF(!cell);
			if(rectContainPoint(CCRectMake(cell->getPosition().x, cell->getPosition().y, cell->getContentSize().width, cell->getContentSize().height),location))
			{
                //notify controller to judge whether the cell can be connected
                
			}
		}
	}
    
	return true;
}

void MainGameGridLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void MainGameGridLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void MainGameGridLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}

void  MainGameGridLayer::constructUI()
{
    do{
		m_containerLayer=CCLayerColor::create(ccc4(0,0,255,255));
		CC_BREAK_IF(!m_containerLayer);
		CCLOG("win size(%f,%f)",WIN_SIZE.width,WIN_SIZE.height);
		m_containerLayer->setContentSize(CCSizeMake(WIN_SIZE.width,WIN_SIZE.height-50));
		m_containerLayer->setPosition(ccp(0,(WIN_SIZE.height-m_containerLayer->getContentSize().height)/2));
		addChild(m_containerLayer);
        
		for(int i=0;i<GRID_ROW;i++){
			for(int j=0;j<GRID_VOLUME;j++){
                GIRDCELL_INDEX itemIndex;
//                itemIndex.rIndex=i+1;
//                itemIndex.vIndex=j+1;
//				GridCell *item=new GridCell();
//				CC_BREAK_IF(!item);
//				item->setCellIndex(itemIndex);
//				item->setCellElementType();
//				item->setPosition(ccp(0+j*100,0+i*100));
//				m_containerLayer->addChild(item);
//                
//                m_GridCellArray->addObject(item);
			}
		}
	}while(0);
}

void MainGameGridLayer::updateGridCell()
{

}

void MainGameGridLayer::moveGridCellAnimation(unsigned int pIdx)
{

}

bool MainGameGridLayer::rectContainPoint(CCRect pRect,CCPoint pPoint)
{
    
}
