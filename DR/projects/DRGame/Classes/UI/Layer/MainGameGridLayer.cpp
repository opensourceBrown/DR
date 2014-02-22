#include "MainGameGridLayer.h"
#include "GridCell.h"
#include "MainGameController.h"
#include "DataConstant.h"


MainGameGridLayer::MainGameGridLayer():m_containerLayer(NULL)
{
    do {
        m_GridCellArray=CCArray::create();
        CC_BREAK_IF(!m_GridCellArray);
    } while (0);
    
}

MainGameGridLayer::~MainGameGridLayer()
{
    
}

void MainGameGridLayer::onEnter()
{
	BaseLayer::onEnter();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0-TOUCH_EVENT_PRIORITY_DEFAULT, true);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("MainGame.plist");
    
    this->constructUI();
}

void MainGameGridLayer::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("MainGame.plist");

	BaseLayer::onExit();
}

bool MainGameGridLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location=pTouch->getLocationInView();
    do{
//        CC_BREAK_IF(!m_GridCellArray || m_GridCellArray->count()<=0);
//        
//        for(int i=0;i<m_GridCellArray->count();i++){
//			GridCell *cell=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(i));
//			CC_BREAK_IF(!cell);
//			if(rectContainPoint(CCRectMake(cell->getPosition().x, cell->getPosition().y, cell->getContentSize().width, cell->getContentSize().height),location))
//			{
//                //notify controller to judge whether the cell can be connected
//                
//			}
//		}
    }while(0);
	
    
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
		m_containerLayer->setContentSize(CCSizeMake(WIN_SIZE.width,WIN_SIZE.height-200));
		m_containerLayer->setPosition(ccp(0,(WIN_SIZE.height-m_containerLayer->getContentSize().height)/2));
		addChild(m_containerLayer);
        
        CC_BREAK_IF(!m_delegate);
        
		for(int i=0;i<GRID_ROW;i++){
			for(int j=0;j<GRID_VOLUME;j++){
                CC_BREAK_IF(!((MainGameController *)m_delegate)->generateGridCell(i,j));        //generate cell property success
                GridElementProperty blockProperty=((MainGameController *)m_delegate)->getGridElementProperty(i, j);
                CCString *typeStr=NULL;
                switch (blockProperty.mType) {
                    case kElementType_Monster:
                    {
                        //select monster image according to the type
                        typeStr=CCString::create("Grid_cell_monster.png");              //暂时写成固定
                    }
                        break;
                    case kElementType_Sword:
                        typeStr=CCString::create("Grid_cell_sword.png");
                        break;
                    case kElementType_Bow:
                        typeStr=CCString::create("Grid_cell_sword.png");                //暂时都写成剑
                        break;
                    case kElementType_Coin:
                        typeStr=CCString::create("Grid_cell_coin.png");
                        break;
                    case kElementType_Potion:
                        typeStr=CCString::create("Grid_cell_potion.png");
                        break;
                    case kElementType_Shield:
                        typeStr=CCString::create("Grid_cell_shield.png");
                        break;
                }
				GridCell *item=GridCell::createWithFrameName(typeStr->getCString());
				CC_BREAK_IF(!item);
                item->setCellProperty(blockProperty);
                item->setAnchorPoint(ccp(0.5,0.5));
                item->setContentSize(CCSizeMake(m_containerLayer->getContentSize().width/GRID_VOLUME, m_containerLayer->getContentSize().height/GRID_ROW));
				//item->setPosition(ccp(j*m_containerLayer->getContentSize().width/GRID_VOLUME+(m_containerLayer->getContentSize().width/GRID_VOLUME-item->getContentSize().width)/2,i*m_containerLayer->getContentSize().height/GRID_ROW+(m_containerLayer->getContentSize().height/GRID_ROW-item->getContentSize().height)/2));
                item->setPosition(ccp((j+1)*m_containerLayer->getContentSize().width/GRID_VOLUME,(i+1)*m_containerLayer->getContentSize().height/GRID_ROW));
				m_containerLayer->addChild(item);

                m_GridCellArray->addObject(item);
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
