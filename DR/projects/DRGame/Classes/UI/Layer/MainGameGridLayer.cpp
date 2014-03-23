#include "MainGameGridLayer.h"
#include "GridCell.h"
#include "MainGameController.h"
#include "DataConstant.h"
#include "DataMangager.h"

#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "OCBridge.h"
#endif

#define MOVE_ANIMATION_DURATION         0.2f

MainGameGridLayer::MainGameGridLayer():
    m_containerLayer(NULL),
    m_GridCellArray(NULL),
    m_currentSelCell(NULL),
    m_gridCellConnLineArray(NULL)
{
    do {
        m_GridCellArray=CCArray::createWithCapacity(GRID_ROW*GRID_VOLUME);
        CC_BREAK_IF(!m_GridCellArray);
        m_GridCellArray->retain();
        
        m_gridCellConnLineArray=CCArray::create();
        CC_BREAK_IF(!m_gridCellConnLineArray);
        m_gridCellConnLineArray->retain();
    } while (0);
    
}

MainGameGridLayer::~MainGameGridLayer()
{
    do{
        CC_BREAK_IF(!m_GridCellArray);
        CC_SAFE_RELEASE(m_GridCellArray);
        
        CC_BREAK_IF(!m_gridCellConnLineArray);
        CC_SAFE_RELEASE(m_gridCellConnLineArray);
    }while(0);
}

MainGameGridLayer *MainGameGridLayer::create()
{
    MainGameGridLayer *layer=new MainGameGridLayer();
    do {
        CC_BREAK_IF(!layer);
        //layer->autorelease();
        return layer;
    } while (0);
    
    CC_SAFE_DELETE(layer);
    return NULL;
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
            //select monster image according to the type
            if (gProperty->mMonsterProperty.mType==kBustyType_Common) {
                typeStr=CCString::create("Grid_cell_monster.png");
            }else if (gProperty->mMonsterProperty.mType==kBustyType_Boss){
                CCLog("+++++++++++++++++++++++");
                typeStr=CCString::create("Grid_cell_boss_monster.jpg");
            }
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
        default:
            break;
    }
    GridCell *item=GridCell::createWithFrameName(typeStr->getCString());
    item->setAnchorPoint(ccp(0.5,0.5));
//    item->setContentSize(CCSizeMake(m_containerLayer->getContentSize().width/GRID_VOLUME, m_containerLayer->getContentSize().height/GRID_ROW));
    item->setCellProperty(gProperty);
    int row = gProperty->mIndex.rIndex;
    int col = gProperty->mIndex.vIndex;
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    IOS_PLATFORM_TYPE platform= OCBridge::getPlatformType();
    float offsetXCoe=0;
    float offsetYCoe=0;
    if (platform==kIOS_PLATFORM_TYPE_ipad) {
        offsetXCoe=1.5;
        offsetYCoe=2;
    }else{
//        offsetXCoe=0.5;
//        offsetYCoe=0.5;
        offsetXCoe=1.5;
        offsetYCoe=2;
    }
    item->setPosition(ccp((col+1)*m_containerLayer->getContentSize().width/GRID_VOLUME-offsetXCoe*item->getContentSize().width,m_containerLayer->getContentSize().height-row*m_containerLayer->getContentSize().height/GRID_ROW-offsetYCoe*item->getContentSize().height));
#endif
    item->setStatus(true);
    m_containerLayer->addChild(item);
    m_GridCellArray->addObject(item);
}

//update the grid layer:add the new cell to the grid layer and trigger the move action
void MainGameGridLayer::updateGrid()
{
    std::cout<<"updateGrid"<<std::endl;
    scheduleOnce(schedule_selector(MainGameGridLayer::refreshGrid), 0.5);
}

void MainGameGridLayer::refreshGrid(float pDelta)
{
    do{
        CC_BREAK_IF(!m_GridCellArray);
        
        //update the cell to special position
        for (int i=0; i<m_GridCellArray->count(); i++) {
            moveGridCellWithIndex(i,MOVE_ANIMATION_DURATION);
        }
        scheduleOnce(schedule_selector(MainGameGridLayer::triggerBossSkill), MOVE_ANIMATION_DURATION);
    }while(0);
}

void MainGameGridLayer::moveGridCellWithIndex(unsigned int index, float duration)
{
    do{
        CC_BREAK_IF(index>=m_GridCellArray->count());
        GridCell *cell = dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(index));
        CC_BREAK_IF(!cell);
        cell->setStatus(true);
        GridElementProperty *blockProperty=cell->getCellProperty();
        CC_BREAK_IF(!blockProperty);
        this->moveGridCellAnimation(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex,duration);
    }while(0);
}

/**
 *   触发boss技能
 */
void MainGameGridLayer::triggerBossSkill()
{
    do{
        CC_BREAK_IF(!m_GridCellArray);
        
        bool hasBossHealer = false;
        for(int i=0;i<m_GridCellArray->count();i++){
			GridCell *cell=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(i));
			CC_BREAK_IF(!cell);
            
            GridElementProperty *geProperty = cell->getCellProperty();
            if (geProperty->mType == kElementType_Monster
                && geProperty->mMonsterProperty.mType == kBustyType_Boss) {
                if (geProperty->mMonsterProperty.mSkillType == kBossBustyType_Chaotic) {
                    //TODO:Chaotic boss,随机移动自己的地方
                    int randomIndex = arc4random()%m_GridCellArray->count();
                    if (randomIndex != i) {
                        GridCell *randomCell=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(randomIndex));
                        
                        GridElementProperty *blockProperty=cell->getCellProperty();
                        GridElementProperty *randomBlockProperty=randomCell->getCellProperty();
                        int tRIndex = blockProperty->mIndex.rIndex;
                        int tVindex = blockProperty->mIndex.vIndex;
                        blockProperty->mIndex.rIndex=randomBlockProperty->mIndex.rIndex;
                        blockProperty->mIndex.vIndex=randomBlockProperty->mIndex.vIndex;
                        randomBlockProperty->mIndex.rIndex=tRIndex;
                        randomBlockProperty->mIndex.vIndex=tVindex;
                        
                        m_GridCellArray->exchangeObject(cell, randomCell);
                        moveGridCellWithIndex(i, 3);
                        moveGridCellWithIndex(randomIndex, 3);
                        
                        std::cout<<"i ="<<i<<"randomIndex="<<randomIndex<<std::endl;
                    }
                } else if (geProperty->mMonsterProperty.mSkillType == kBossBustyType_Healer) {
                    //TODO:让所有受到伤害的怪兽回复生命值到最大值。
                    hasBossHealer = true;
                }
            }
		}
        
        if (hasBossHealer) {
            recoverMonsterLifeFull();
        }
    }while(0);
}

void MainGameGridLayer::addGridCell(unsigned int rIndex,unsigned int vIndex)
{
    do{
        CC_BREAK_IF(!m_GridCellArray);
        
        GridElementProperty *blockProperty=((MainGameController *)m_delegate)->getGridElementProperty(rIndex, vIndex);
        CC_BREAK_IF(!blockProperty);
        
        CCString *typeStr=NULL;
        switch (blockProperty->mType) {
            case kElementType_Monster:
            {
                //select monster image according to the type
                if (blockProperty->mMonsterProperty.mType==kBustyType_Common) {
                    typeStr=CCString::create("Grid_cell_monster.png");
                }else if (blockProperty->mMonsterProperty.mType==kBustyType_Boss){
                    CCLog("---------------------------");
                    typeStr=CCString::create("Grid_cell_boss_monster.jpg");
                }
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
        item->setAnchorPoint(ccp(0.5,0.5));
//        item->setContentSize(CCSizeMake(m_containerLayer->getContentSize().width/GRID_VOLUME, m_containerLayer->getContentSize().height/GRID_ROW));
        item->setCellProperty(blockProperty);
		int row = blockProperty->mIndex.rIndex;
		int col = blockProperty->mIndex.vIndex;
        
        int step=0;
        for (int i=0; i<GRID_ROW; i++) {
            GridCell *cell = dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(i*GRID_VOLUME+vIndex));
            CC_BREAK_IF(!cell);
            if (false==cell->getStatus()) {
                step++;
            }
        }
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
        IOS_PLATFORM_TYPE platform= OCBridge::getPlatformType();
        float offsetXCoe=0;
        float offsetYCoe=0;
        if (platform==kIOS_PLATFORM_TYPE_ipad) {
            offsetXCoe=1.5;
            offsetYCoe=2;
        }else{
//            offsetXCoe=0.5;
//            offsetYCoe=0.5;
            offsetXCoe=1.5;
            offsetYCoe=2;
        }
        item->setPosition(ccp((col+1)*m_containerLayer->getContentSize().width/GRID_VOLUME-offsetXCoe*item->getContentSize().width,m_containerLayer->getContentSize().height+m_containerLayer->getContentSize().height/GRID_ROW-offsetYCoe*item->getContentSize().height));
#endif
        m_containerLayer->addChild(item);
        m_GridCellArray->replaceObjectAtIndex(rIndex*GRID_VOLUME+vIndex, item);
    }while(0);
}

void MainGameGridLayer::exchangeGridCell(unsigned int rIndex,unsigned int vIndex)
{
    do {
        CC_BREAK_IF(!m_GridCellArray || !(m_GridCellArray->objectAtIndex(rIndex)) || !(m_GridCellArray->objectAtIndex(vIndex)));
        GridCell *rCell=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(rIndex));
        GridCell *sCell=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(vIndex));
        //update the cell property index
        GridElementProperty *rBlockProperty=rCell->getCellProperty();
        GridElementProperty *sBlockProperty=sCell->getCellProperty();
        int tRIndex=rBlockProperty->mIndex.rIndex;
        rBlockProperty->mIndex.rIndex=sBlockProperty->mIndex.rIndex;
        sBlockProperty->mIndex.rIndex=tRIndex;
        
        m_GridCellArray->exchangeObject(rCell, sCell);
    } while (0);
}

void MainGameGridLayer::exchangePositionOfGridCell(unsigned int rIndex, unsigned int vIndex)
{
    
}

void MainGameGridLayer::removeGridCell(unsigned int rIndex,unsigned int vIndex)
{
    do{
        CC_BREAK_IF(!m_GridCellArray);
        GridCell *cell=NULL;
        for (int i=0; i<m_GridCellArray->count(); i++) {
            GridCell *item=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(i));
            CC_BREAK_IF(!item);
            
            GridElementProperty *blockProperty=item->getCellProperty();
            CC_BREAK_IF(!blockProperty);
            if (blockProperty->mIndex.rIndex==rIndex && blockProperty->mIndex.vIndex==vIndex) {
                cell=item;
                break;
            }
        }
        CC_BREAK_IF(!cell);
        cell->runAction(CCSequence::create(CCBlink::create(0.5, 2),CCCallFuncN::create(this,callfuncN_selector(MainGameGridLayer::removeGridCellCompleteCallback)),NULL));
    }while(0);
}

void MainGameGridLayer::removeGridCellCompleteCallback(CCObject *pSender)
{
    do{
        GridCell *cell=dynamic_cast<GridCell *>(pSender);
        CC_BREAK_IF(!cell);
        cell->removeFromParentAndCleanup(true);
    }while(0);
}

void MainGameGridLayer::moveGridCellAnimation(unsigned int rIndex,unsigned int vIndex, float duration)
{
    do{
        CC_BREAK_IF(!m_GridCellArray);
        
        GridCell *cell=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(rIndex*GRID_VOLUME+vIndex));
        CC_BREAK_IF(!cell);
        
        GridElementProperty *blockProperty=cell->getCellProperty();
        CC_BREAK_IF(!blockProperty);
        
        //move action
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
        IOS_PLATFORM_TYPE platform= OCBridge::getPlatformType();
        float offsetXCoe=0;
        float offsetYCoe=0;
        if (platform==kIOS_PLATFORM_TYPE_ipad) {
            offsetXCoe=1.5;
            offsetYCoe=2;
        }else{
            //            offsetXCoe=0.5;
            //            offsetYCoe=0.5;
            offsetXCoe=1.5;
            offsetYCoe=2;
        }
        cell->runAction(CCMoveTo::create(duration, ccp((blockProperty->mIndex.vIndex+1)*m_containerLayer->getContentSize().width/GRID_VOLUME-offsetXCoe*cell->getContentSize().width,m_containerLayer->getContentSize().height-blockProperty->mIndex.rIndex*m_containerLayer->getContentSize().height/GRID_ROW-offsetYCoe*cell->getContentSize().height)));
#endif
        
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

void MainGameGridLayer::addConnectLine(GridCell *fCell,GridCell *sCell)
{
    LOG_TRACE
    do {
        CC_BREAK_IF(!m_gridCellConnLineArray);
        CC_BREAK_IF(!fCell);
        CC_BREAK_IF(!sCell);
        GridElementProperty *fBlockProperty=fCell->getCellProperty();
        CC_BREAK_IF(!fBlockProperty);
        GridElementProperty *sBlockProperty=sCell->getCellProperty();
        CC_BREAK_IF(!sBlockProperty);
        
        CCSprite *line=CCSprite::createWithSpriteFrameName("Grid_cell_connect_line.png");
        CC_BREAK_IF(!line);
        line->setAnchorPoint(ccp(0,0.5));
        float tScaleX=1;
        if (fBlockProperty->mIndex.rIndex==sBlockProperty->mIndex.rIndex || fBlockProperty->mIndex.vIndex==sBlockProperty->mIndex.vIndex) {
            tScaleX=m_containerLayer->getContentSize().width/GRID_VOLUME/line->getContentSize().width;
        }else{
            tScaleX=m_containerLayer->getContentSize().width/GRID_VOLUME*1.42/line->getContentSize().width;
        }
        line->setScaleX(tScaleX);
        line->setPosition(ccp(fCell->getPosition().x-fCell->getContentSize().width/2,fCell->getPosition().y+m_containerLayer->getContentSize().height/GRID_ROW/2+fCell->getGridNodeHeight()/2));
        
        float tRotate=0;
        //judge the relative postion relationship for the two cells
        if (fBlockProperty->mIndex.rIndex==sBlockProperty->mIndex.rIndex || fBlockProperty->mIndex.vIndex==sBlockProperty->mIndex.vIndex) {
            tRotate=(fBlockProperty->mIndex.rIndex==sBlockProperty->mIndex.rIndex)?((sBlockProperty->mIndex.vIndex>fBlockProperty->mIndex.vIndex)?0:-180):(sBlockProperty->mIndex.rIndex>fBlockProperty->mIndex.rIndex?90:-90);
        }else{
            tRotate=(sBlockProperty->mIndex.rIndex<fBlockProperty->mIndex.rIndex)?((sBlockProperty->mIndex.vIndex>fBlockProperty->mIndex.vIndex)?-45:-135):((sBlockProperty->mIndex.vIndex>fBlockProperty->mIndex.vIndex)?45:135);
        }
        
        line->setRotation(tRotate);
        
        this->addChild(line);
        m_gridCellConnLineArray->addObject(line);
    } while (0);
}

void MainGameGridLayer::removeConnectLine()
{
    do {
        CC_BREAK_IF(!m_gridCellConnLineArray);
        if (m_gridCellConnLineArray->count()>0) {
            CCSprite *line=dynamic_cast<CCSprite *>(m_gridCellConnLineArray->lastObject());
            CC_BREAK_IF(!line);
            line->removeFromParentAndCleanup(true);
            m_gridCellConnLineArray->removeLastObject();
        }
    } while (0);
}

void MainGameGridLayer::clearConnectLine()
{
    do {
        CC_BREAK_IF(!m_gridCellConnLineArray);
        if (m_gridCellConnLineArray->count()>0) {
            for (int i=0; i<m_gridCellConnLineArray->count(); i++) {
                CCSprite *line=dynamic_cast<CCSprite *>(m_gridCellConnLineArray->objectAtIndex(i));
                CC_BREAK_IF(!line);
                line->removeFromParentAndCleanup(true);
            }
            m_gridCellConnLineArray->removeAllObjects();
        }
    } while (0);
}

bool MainGameGridLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location=pTouch->getLocation();
//    CCLog("grid size(%f,%f)",m_containerLayer->getContentSize().width/GRID_VOLUME,m_containerLayer->getContentSize().height/GRID_ROW);
    do{
        CC_BREAK_IF(!m_delegate);
        CC_BREAK_IF(!m_GridCellArray);
        
        for(int i=0;i<m_GridCellArray->count();i++){
			GridCell *cell=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(i));
			CC_BREAK_IF(!cell);
			if(rectContainPoint(CCRectMake(cell->getPosition().x-cell->getContentSize().width, cell->getPosition().y+m_containerLayer->getContentSize().height/GRID_ROW/2+cell->getContentSize().height, cell->getContentSize().width, cell->getContentSize().height),location))
			{
                m_currentSelCell=cell;
                GridElementProperty *blockProperty=cell->getCellProperty();
                
                //notify controller to insert the cell into connected array if the cell can be connected
                ((MainGameController *)m_delegate)->processGridCellSelected(blockProperty->mIndex.rIndex,blockProperty->mIndex.vIndex);
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
			if(rectContainPoint(CCRectMake(cell->getPosition().x-cell->getContentSize().width, cell->getPosition().y+m_containerLayer->getContentSize().height/GRID_ROW/2+cell->getContentSize().height, cell->getContentSize().width, cell->getContentSize().height),location))
			{
                if (m_currentSelCell==cell) {
                    break;
                }
                m_currentSelCell=cell;
                GridElementProperty *blockProperty=cell->getCellProperty();
                
                //notify controller to insert the cell into connected array if the cell can be connected
                ((MainGameController *)m_delegate)->processGridCellSelected(blockProperty->mIndex.rIndex,blockProperty->mIndex.vIndex);
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
            bool hasNoElementToClear = ((MainGameController *)m_delegate)->clearConnectedElements();
            if (hasNoElementToClear) {
                triggerBossSkill();
            }
            refreshMonsterPropertyLabelOfAllGridCell();           //刷新怪物血量等信息
        }else{
            ((MainGameController *)m_delegate)->resetStageConnectedElements();
        }
    }while(0);
    
    m_currentSelCell=NULL;
}

void MainGameGridLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

//刷新怪物血量等信息
void MainGameGridLayer::refreshMonsterPropertyLabelOfAllGridCell()
{
    do{
        CC_BREAK_IF(!m_GridCellArray);
        
        bool hasBossHealer = false;
        for(int i=0;i<m_GridCellArray->count();i++){
			GridCell *cell=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(i));
			CC_BREAK_IF(!cell);
            cell->refreshMonsterPropertyLabel();
		}
    }while(0);
}

//所有怪物回复生命值到最大
void MainGameGridLayer::recoverMonsterLifeFull()
{
    for(int i=0;i<m_GridCellArray->count();i++){
        
        GridCell *cell=dynamic_cast<GridCell *>(m_GridCellArray->objectAtIndex(i));
        CC_BREAK_IF(!cell);
        GridElementProperty *geProperty = cell->getCellProperty();
        if (geProperty->mType == kElementType_Monster) {
            geProperty->mMonsterProperty.mLife = geProperty->mMonsterProperty.mMaxLife;
        }
    }
}
