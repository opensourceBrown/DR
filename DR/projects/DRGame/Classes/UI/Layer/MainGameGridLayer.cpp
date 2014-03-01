#include "MainGameGridLayer.h"
#include "GridCell.h"
#include "MainGameController.h"
#include "DataConstant.h"
#include "DataMangager.h"

MainGameGridLayer::MainGameGridLayer():
    m_containerLayer(NULL),
    m_GridCellArray(NULL)
{
    do {
        m_GridCellArray=CCArray::createWithCapacity(GRID_ROW*GRID_VOLUME);
        CC_BREAK_IF(!m_GridCellArray);
        m_GridCellArray->retain();
    } while (0);
    
}

MainGameGridLayer::~MainGameGridLayer()
{
    do{
        CC_BREAK_IF(!m_GridCellArray);
        CC_SAFE_RELEASE(m_GridCellArray);
    }while(0);
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
    CCPoint location=pTouch->getLocation();
    //CCLog("screen size:(%f,%f)",WIN_SIZE.width,WIN_SIZE.height);
    //CCLog("touch location:(%f,%f)",location.x,location.y);
    do{
        
        CC_BREAK_IF(!m_delegate);
        CC_BREAK_IF(!m_GridCellArray);
        
        for(int i=0;i<m_GridCellArray->count();i++){
			GridCell *cell=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(i));
			CC_BREAK_IF(!cell);
            //CCLog("cell rect:(%f,%f,%f,%f)",cell->getPosition().x-m_containerLayer->getContentSize().width/GRID_VOLUME,cell->getPosition().y+cell->getContentSize().height/2,cell->getContentSize().width,cell->getContentSize().height);
			if(rectContainPoint(CCRectMake(cell->getPosition().x-m_containerLayer->getContentSize().width/GRID_VOLUME, cell->getPosition().y+cell->getContentSize().height/2, cell->getContentSize().width, cell->getContentSize().height),location))
			{
                GridElementProperty *blockProperty=cell->getCellProperty();
                //CCLog("------------------------------");
                //notify controller to insert the cell into connected array if the cell can be connected
                if (((MainGameController *)m_delegate)->judgeElementsCanConnected(blockProperty->mIndex.rIndex,blockProperty->mIndex.vIndex)) {
                    //CCLog("+++++++++++++++++++++++++++++++");
                    ((MainGameController *)m_delegate)->insertCellIntoConnectedArray(blockProperty->mIndex.rIndex,blockProperty->mIndex.vIndex);
                }
                break;
			}
		}
    }while(0);
	
    
	return true;
}

void MainGameGridLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location=pTouch->getLocation();
    do{
        
        CC_BREAK_IF(!m_delegate);
        CC_BREAK_IF(!m_GridCellArray);
        
        for(int i=0;i<m_GridCellArray->count();i++){
			GridCell *cell=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(i));
			CC_BREAK_IF(!cell);
			if(rectContainPoint(CCRectMake(cell->getPosition().x-m_containerLayer->getContentSize().width/GRID_VOLUME, cell->getPosition().y+cell->getContentSize().height/2, cell->getContentSize().width, cell->getContentSize().height),location))
			{
                GridElementProperty *blockProperty=cell->getCellProperty();
                //notify controller to insert the cell into connected array if the cell can be connected
                if (((MainGameController *)m_delegate)->judgeElementsCanConnected(blockProperty->mIndex.rIndex,blockProperty->mIndex.vIndex)) {
                    ((MainGameController *)m_delegate)->insertCellIntoConnectedArray(blockProperty->mIndex.rIndex,blockProperty->mIndex.vIndex);
                }
                break;
			}
		}
    }while(0);
}

void MainGameGridLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    do{
        CC_BREAK_IF(!m_delegate);
        
        if (((MainGameController *)m_delegate)->judgeConnectedElementsCanClear()) {
            ((MainGameController *)m_delegate)->clearConnectedElements();
        }
    }while(0);
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
                GridElementProperty *blockProperty=((MainGameController *)m_delegate)->getGridElementProperty(i, j);
                addGridCellToLayer(blockProperty);
			}
		}
        DataManager::sharedInstance()->saveGridElements();  //save as plist
	}while(0);
}

void MainGameGridLayer::addGridCellToLayer(GridElementProperty *gProperty)
{
    CCString *typeStr=NULL;
    switch (gProperty->mType) {
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
    item->setCellProperty(gProperty);
    item->setAnchorPoint(ccp(0.5,0.5));
    item->setTag(gProperty->mIndex.rIndex*GRID_VOLUME+gProperty->mIndex.vIndex+1);
    item->setContentSize(CCSizeMake(m_containerLayer->getContentSize().width/GRID_VOLUME, m_containerLayer->getContentSize().height/GRID_ROW));
    
    int row = gProperty->mIndex.rIndex;
    int col = gProperty->mIndex.vIndex;
    item->setPosition(ccp((col+1)*m_containerLayer->getContentSize().width/GRID_VOLUME,m_containerLayer->getContentSize().height-row*m_containerLayer->getContentSize().height/GRID_ROW));
    m_containerLayer->addChild(item);
    
    m_GridCellArray->addObject(item);
}

//update the grid layer:add the new cell to the grid layer and trigger the move action
void MainGameGridLayer::updateGrid()
{
    do{
        CC_BREAK_IF(!m_GridCellArray);
        
        //update the cell to special position
        for (int i=0; i<m_GridCellArray->count(); i++) {
            GridCell *cell = dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(i));
            CC_BREAK_IF(!cell);
            GridElementProperty *blockProperty=cell->getCellProperty();
            CC_BREAK_IF(!blockProperty);
            this->moveGridCellAnimation(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
        }
    }while(0);
}

//void MainGameGridLayer::updateGridCell(unsigned int uIndex,unsigned int vIndex,unsigned int pStep)
//{
//    do{
//        
//    }while(0);
//}

void MainGameGridLayer::addGridCell(unsigned int rIndex,unsigned int vIndex)
{
    do{
        CC_BREAK_IF(!m_GridCellArray);
        
        //judge whether the cell is cleared
        GridCell *cell = dynamic_cast<GridCell *>(m_containerLayer->getChildByTag(rIndex*GRID_VOLUME+vIndex));
        CC_BREAK_IF(cell);
        
        GridElementProperty *blockProperty=((MainGameController *)m_delegate)->getGridElementProperty(rIndex, vIndex);
        CC_BREAK_IF(!blockProperty);
        
        CCString *typeStr=NULL;
        switch (blockProperty->mType) {
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
        item->setCellProperty(blockProperty);
        item->setAnchorPoint(ccp(0.5,0.5));
        item->setTag(blockProperty->mIndex.rIndex*GRID_VOLUME+blockProperty->mIndex.vIndex+1);
        item->setContentSize(CCSizeMake(m_containerLayer->getContentSize().width/GRID_VOLUME, m_containerLayer->getContentSize().height/GRID_ROW));

		int row = blockProperty->mIndex.rIndex;
		int col = blockProperty->mIndex.vIndex;
		item->setPosition(ccp((col+1)*m_containerLayer->getContentSize().width/GRID_VOLUME,m_containerLayer->getContentSize().height+row*m_containerLayer->getContentSize().height/GRID_ROW));
		m_containerLayer->addChild(item);
        m_GridCellArray->insertObject(item,rIndex*GRID_VOLUME+vIndex);
    }while(0);
}

void MainGameGridLayer::removeGridCell(unsigned int rIndex,unsigned int vIndex)
{
    do{
        CC_BREAK_IF(!m_GridCellArray);
        
        m_GridCellArray->removeObjectAtIndex(rIndex*GRID_VOLUME+vIndex);
        
        GridCell *cell=dynamic_cast<GridCell *>(m_containerLayer->getChildByTag(rIndex*GRID_VOLUME+vIndex));
        CC_BREAK_IF(!cell);
        
        //remove action
        cell->removeFromParentAndCleanup(true);
    }while(0);
}

//move action
void MainGameGridLayer::moveGridCellAnimation(unsigned int rIndex,unsigned int vIndex)
{
    do{
        CC_BREAK_IF(!m_GridCellArray);
        
        GridCell *cell=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(rIndex*GRID_VOLUME+vIndex));
        CC_BREAK_IF(!cell);
        
        //move action
        
    }while(0);
}

bool MainGameGridLayer::rectContainPoint(CCRect pRect,CCPoint pPoint)
{
    bool tRet=false;
    
    if (pPoint.x>=pRect.origin.x && pPoint.x<=pRect.origin.x+pRect.size.width && pPoint.y<=pRect.origin.y && pPoint.y>=pRect.origin.y-pRect.size.height) {
        tRet=true;
    }
    
    return tRet;
}

GridCell *MainGameGridLayer::getGridCell(unsigned int rIndex,unsigned int vIndex)
{
    LOG_TRACE
    GridCell *cell=NULL;
    do{
        CC_BREAK_IF(!m_GridCellArray);
        cell=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(rIndex*GRID_VOLUME+vIndex));
    }while(0);
    
    return  cell;
}
