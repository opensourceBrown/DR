/****************************************************************************
//√ï¬Æ‚Äù‚àö¬†Àù√¶‚Ä∫∆í¬£‚Äì√ï¬ø‚Ä°
****************************************************************************/
#include "MainGameController.h"
#include "MainGameScene.h"
#include "MainGameGridLayer.h"
#include "GridCell.h"
#include "DataMangager.h"
#include "DRUserDefault.h"
#include "MainGameStatusBar.h"

//test
#define PASS_STAGE_KILL_MONSTER         100
#define PASS_STAGE_COIN                 100
#define PASS_STAGE_ROUND                100

MainGameController::MainGameController():
    mMagicInStage(NULL),
    mStageConnectedElements(NULL),
    mCurShield(0),
    mCurPortion(0),
    mCurStageKillMonster(0),
    mCurStageCoin(0),
    mCurStageScore(0)
{
    mMagic.init();
    mPlayerProperty.init();
}

MainGameController::~MainGameController()
{
    CC_SAFE_RELEASE(mMagicInStage);
    CC_SAFE_RELEASE(mStageConnectedElements);
    CC_SAFE_RELEASE(m_scene);
}

MainGameController *MainGameController::create()
{
    MainGameController *controller=new MainGameController();
    do {
        CC_BREAK_IF(!controller || !(controller->initWith()));
        //controller->autorelease();
        return controller;
    } while (0);
    
    CC_SAFE_DELETE(controller);
    return NULL;
}

bool MainGameController::initWith()
{
    LOG_TRACE
    bool tRet=false;
    do {
        //TO:DO initialization
        mMagicInStage=CCArray::create();
        CC_BREAK_IF(!mMagicInStage);
        mMagicInStage->retain();
        
        mStageConnectedElements=CCArray::create();
        CC_BREAK_IF(!mStageConnectedElements);
        mStageConnectedElements->retain();
        
        mGridPropertyContainer=CCArray::createWithCapacity(GRID_VOLUME*GRID_ROW);
        CC_BREAK_IF(!mGridPropertyContainer);
        mGridPropertyContainer->retain();
        
        m_scene=MainGameScene::create(this);
        CC_BREAK_IF(!m_scene);
        m_scene->retain();
        
        readPlayerProperty();
        mCurShield=mPlayerProperty.mMaxShield;
        mCurPortion=mPlayerProperty.mMaxHealth;
        
        updateStatusData();
        
        tRet=true;
    } while (0);
    
    return tRet;
}

void MainGameController::readPlayerProperty()
{
    //
    mPlayerProperty.mType=kOccupationType_Human;
    mPlayerProperty.mMaxHealth=50;
    mPlayerProperty.mDefencePerShield=1;
    mPlayerProperty.mMaxShield=4;
    mPlayerProperty.mHealthPerPotion=1;
    mPlayerProperty.mBasicDamage=3;
    mPlayerProperty.mWeaponDamage=2;
    mPlayerProperty.mLeech=0;
    mPlayerProperty.mCriticalDamageRate=0;
    mPlayerProperty.mPierce=0;
}

void MainGameController::updateStatusData()
{
    do {
        CCLog("%s:mCurShield=%d,mCurPortion=%d,mCurStageKillMonster=%d,mCurStageCoin=%d",__FUNCTION__,mCurShield,mCurPortion,mCurStageKillMonster,mCurStageCoin);
        MainGameStatusBar *statusBar = ((MainGameScene *)m_scene)->getStatusLayer();
        CC_BREAK_IF(!statusBar);
        statusBar->setShieldValue(mCurShield,mPlayerProperty.mMaxShield);
        statusBar->setPortionProgress((int)(100.0*mCurPortion/mPlayerProperty.mMaxHealth));
        statusBar->setKillMonsterProgress((int)(100.0*mCurStageKillMonster/PASS_STAGE_KILL_MONSTER));
        statusBar->setCoinProgress((int)(100.0*mCurStageCoin/PASS_STAGE_COIN));
        statusBar->setRoundValue(DRUserDefault::sharedUserDefault()->getRoundCount());
    } while (0);
}

void MainGameController::selectMagic(MagicType pID)
{
    mMagic.mMagicType=pID;
    mMagic.mID=pID;
    switch (pID) {
        case kMagicType_Steal:
            mMagic.mCDTime=18;
            break;
        case kMagicType_Fireball:
            mMagic.mCDTime=19;
            break;
        case kMagicType_CounterAttack:
            mMagic.mCDTime=23;
            break;
        case kMagicType_GoldenTouch:
            mMagic.mCDTime=20;
            break;
        case kMagicType_BoostHealth:
            mMagic.mCDTime=20;
            break;
        case kMagicType_BigGameHunter:
            mMagic.mCDTime=20;
            break;
        case kMagicType_Shatter:
            mMagic.mCDTime=23;
            break;
        case kMagicType_BoostGold:
            mMagic.mCDTime=25;
            break;
        case kMagicType_Teleport:
            mMagic.mCDTime=25;
            break;
        case kMagicType_Heal:
            mMagic.mCDTime=20;
            break;
        default:
            break;
    }
}

bool MainGameController::judgeIsTriggerMagic()
{
    bool tRet=false;
    switch (mMagic.mMagicType) {
        case kMagicType_Steal:{     //get 1 coin per monster every round
            CC_BREAK_IF(mMagic.mCDTime>0);
            do {
                CC_BREAK_IF(!mStageConnectedElements || mStageConnectedElements->count()<=0);
                for (int i=0; i<mStageConnectedElements->count(); i++) {
                    GridCell *cell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(i));
                    CC_BREAK_IF(!cell);
                    
                    GridElementProperty *block=cell->getCellProperty();
                    CC_BREAK_IF(!block);
                    if (block->mType==kElementType_Monster){
                        tRet=true;
                        break;
                    }
                }
            } while (0);
            break;
        }
        case kMagicType_Fireball:
            
            break;
        case kMagicType_CounterAttack:
            
            break;
        case kMagicType_GoldenTouch:
            
            break;
        case kMagicType_BoostHealth:
            
            break;
        case kMagicType_BigGameHunter:
            
            break;
        case kMagicType_Shatter:
            
            break;
        case kMagicType_BoostGold:
            
            break;
        case kMagicType_Teleport:
            
            break;
        case kMagicType_Heal:
            
            break;
        default:
            break;
    }
    return tRet;
}

void MainGameController::triggerMagic(MagicType pID)
{
    do {
        switch (pID) {
            case kMagicType_Steal:{     //get 1 coin per monster every round
                do {
                    CC_BREAK_IF(!mStageConnectedElements || mStageConnectedElements->count()<=0);
                    for (int i=0; i<mStageConnectedElements->count(); i++) {
                        GridCell *cell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(i));
                        CC_BREAK_IF(!cell);
                        
                        GridElementProperty *block=cell->getCellProperty();
                        CC_BREAK_IF(!block);
                        if (block->mType==kElementType_Monster){
                            DRUserDefault::sharedUserDefault()->setCoin(DRUserDefault::sharedUserDefault()->getCoin()+1);
                        }
                    }
                } while (0);
                mMagic.mCDTime=18;
                break;
            }
            case kMagicType_Fireball:
                
                break;
            case kMagicType_CounterAttack:
                
                break;
            case kMagicType_GoldenTouch:
                
                break;
            case kMagicType_BoostHealth:
                
                break;
            case kMagicType_BigGameHunter:
                
                break;
            case kMagicType_Shatter:
                
                break;
            case kMagicType_BoostGold:
                
                break;
            case kMagicType_Teleport:
                
                break;
            case kMagicType_Heal:
                
                break;
            default:
                break;
        }
    } while (0);
}

void MainGameController::triggerWeapon(unsigned int pID)
{
    
}

void MainGameController::statisticsDataPerRound()
{
    //statistics cur connected cell status data
    do {
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        CC_BREAK_IF(!mStageConnectedElements);
        for (int i=0; i<mStageConnectedElements->count(); i++) {
            GridCell *cell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(i));
            CC_BREAK_IF(!cell);
            
            GridElementProperty *block=cell->getCellProperty();
            CC_BREAK_IF(!block);
            if (block->mType==kElementType_Monster) {
                DRUserDefault::sharedUserDefault()->setKillMonsterCount(DRUserDefault::sharedUserDefault()->getKillMonsterCount()+1);
                mCurStageKillMonster++;
            }else if(block->mType==kElementType_Coin){
                DRUserDefault::sharedUserDefault()->setCoin(DRUserDefault::sharedUserDefault()->getCoin()+1);
                mCurStageCoin++;
            }else if(block->mType==kElementType_Shield){
                mCurShield++;
                if (mCurShield>mPlayerProperty.mMaxShield) {
                    mCurShield=mPlayerProperty.mMaxShield;
                }
            }else if(block->mType==kElementType_Potion){
                mCurPortion++;
                if (mCurPortion>mPlayerProperty.mMaxHealth) {
                    mCurPortion=mPlayerProperty.mMaxHealth;
                }
            }
        }
    }while(0);
    
    //statistics the unconnected cell status data(shield and portion)
    do {
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        
        for (int i=0; i<GRID_ROW; i++) {
            for (int j=0; j<GRID_VOLUME; j++) {
                GridCell *cell=gridLayer->getGridCell(i, j);
                CC_BREAK_IF(!cell);
                
                GridElementProperty *block=cell->getCellProperty();
                CC_BREAK_IF(!block);
                if (false==block->getStatus()) {
                    if (block->mType==kElementType_Monster) {
                        mCurShield--;
                        if (mCurShield<=0) {
                            mCurShield=0;
                            mCurPortion--;
                            if (mCurPortion<=0) {
                                mCurPortion=0;
                            }
                        }
                    }
                }
            }
        }
    } while (0);
}

void MainGameController::resetStageStatusData()
{
    mCurStageKillMonster=0;
    mCurStageCoin=0;
    mCurPortion=0;
    mCurShield=0;
}

bool MainGameController::judgeGameStageIsEnd()
{
    bool tRet=false;
    
    do{
        //judge whether current game stage can end according to the pass condition ID
        switch (mStageProperty.mPassCondID) {
            case 0:
                
                break;
        }
    }while(0);
    
	return tRet;
}

void MainGameController::endCurrentStage()
{
    //end game stage:save game status data
    do{
        resetStageStatusData();
    }while(0);
}

bool MainGameController::judgeConnectedElementsCanClear()
{
	bool tRet=false;
    
    do{
        CC_BREAK_IF(!mStageConnectedElements || mStageConnectedElements->count()<3);
        tRet=true;
    }while(0);
    
	return tRet;
}

void MainGameController::resetStageConnectedElements()
{
    do {
        CC_BREAK_IF(!mStageConnectedElements);
        
        mStageConnectedElements->removeAllObjects();
        
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        gridLayer->clearConnectLine();
    } while (0);
}

void MainGameController::clearConnectedElements()
{
    do {
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        
        CC_BREAK_IF(!mStageConnectedElements);
        
        if (judgeIsTriggerMagic()) {
            triggerMagic(mMagic.mMagicType);
        }
        //set grid element property status
        for (int i=0; i<mStageConnectedElements->count(); i++) {
            GridCell *cell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(i));
            CC_BREAK_IF(!cell);
            
            GridElementProperty *block=cell->getCellProperty();
            CC_BREAK_IF(!block);
            block->setStatus(true);
            
            GridElementProperty *item=dynamic_cast<GridElementProperty *>(mGridPropertyContainer->objectAtIndex(block->mIndex.rIndex*GRID_VOLUME+block->mIndex.vIndex));
            CC_BREAK_IF(!item);
            item->setStatus(true);
        }
        
        statisticsDataPerRound();
        
        //clear cells on MainGameGridLayer
        for (int i=0; i<mStageConnectedElements->count(); i++) {
            GridCell *cell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(i));
            CC_BREAK_IF(!cell);
            
            GridElementProperty *block=cell->getCellProperty();
            CC_BREAK_IF(!block);
            gridLayer->removeGridCell(block->mIndex.rIndex, block->mIndex.vIndex);
        }
        
        //update property data in mGridPropertyContainer:bubble sort
        for (int i=0; i<GRID_VOLUME; i++) {
            for (int j=GRID_ROW-1; j>=0; j--) {
                GridElementProperty *item=dynamic_cast<GridElementProperty *>(mGridPropertyContainer->objectAtIndex(j*GRID_VOLUME+i));
                CC_BREAK_IF(!item);
                if (item->getStatus()) {
                    //exchange with the above nearest property that is not cleared
                    for (int k=j-1; k>=0; k--) {
                        GridElementProperty *block=dynamic_cast<GridElementProperty *>(mGridPropertyContainer->objectAtIndex(k*GRID_VOLUME+i));
                        CC_BREAK_IF(!block);
                        if (false==block->getStatus()) {
                            //update the vIndex after exchange the two elements
                            int tIndex=item->mIndex.rIndex;
                            item->mIndex.rIndex=block->mIndex.rIndex;
                            block->mIndex.rIndex=tIndex;
                            mGridPropertyContainer->exchangeObject(block, item);
                            
                            //notify the grid layer to exchange cell in m_GridCellArray
                            gridLayer->exchangeGridCell(k*GRID_VOLUME+i, j*GRID_VOLUME+i);
                            break;
                        }
                    }
                }
            }
            
            //generate new property replace the clear elements up to down
            for (int j=0; j<GRID_ROW; j++) {
                GridElementProperty *item=dynamic_cast<GridElementProperty *>(mGridPropertyContainer->objectAtIndex(j*GRID_VOLUME+i));
                CC_BREAK_IF(!item);
                if (item->getStatus()) {
                    generateGridCell(item->mIndex.rIndex, item->mIndex.vIndex);
                    
                    //notify grid layer to generate new cell to replace the cleard cell
                    gridLayer->addGridCell(item->mIndex.rIndex, item->mIndex.vIndex);
                }else{
                    break;
                }
            }
        }
        
        gridLayer->clearConnectLine();
        //update MainGameGridLayer to show new cell
        gridLayer->updateGrid();
    } while (0);
        
    mStageConnectedElements->removeAllObjects();
    
    mMagic.mCDTime--;
    DRUserDefault::sharedUserDefault()->setRoundCount(DRUserDefault::sharedUserDefault()->getRoundCount()+1);
    
    updateStatusData();
	//√øªÿ∫œΩ· ¯∂º≈–∂œµ±«∞πÿø® «∑ÒΩ· ¯
	//judge whether the current stage is end
    if (this->judgeGameStageIsEnd()) {
        this->endCurrentStage();
    }
}

bool MainGameController::generateGridCell(unsigned int rIndex,unsigned int vIndex)
{
    bool tSuc=false;
    
    do {
        CCDictionary *rDict = DataManager::sharedInstance()->getGridElements();
        
        GridElementProperty *blockProperty = new GridElementProperty();
        blockProperty->init();

        if (rDict->count() > 0) {
            
            std::stringstream sStream;
            sStream<<rIndex<<"_"<<vIndex;
            
            CCDictionary *currentDic = (CCDictionary *)rDict->objectForKey(sStream.str());
            if (currentDic) {
                //read plist Data
                CCString *strRIndex = (CCString *)currentDic->objectForKey("rIndex");
                blockProperty->mIndex.rIndex= strRIndex->intValue();
                CCString *strVIndex = (CCString *)currentDic->objectForKey("vIndex");
                blockProperty->mIndex.vIndex=strVIndex->intValue();
                CCString *strType = (CCString *)currentDic->objectForKey("mType");
                blockProperty->mType=(ElementType)strType->intValue();
                CCString *strID = (CCString *)currentDic->objectForKey("mID");
                blockProperty->mID=strID->intValue();
            } else {
                blockProperty->mIndex.rIndex=rIndex;
                blockProperty->mIndex.vIndex=vIndex;
                blockProperty->generateGridElementDataByCSV(true);
                
                blockProperty->saveToDictionary(rDict);
            }
        } else {
            blockProperty->mIndex.rIndex=rIndex;
            blockProperty->mIndex.vIndex=vIndex;
            blockProperty->generateGridElementDataByCSV(true);
            
            blockProperty->saveToDictionary(rDict);
        }
        
        if (rIndex*GRID_VOLUME+vIndex<mGridPropertyContainer->count() && mGridPropertyContainer->objectAtIndex(rIndex*GRID_VOLUME+vIndex)) {
            //replace
            mGridPropertyContainer->replaceObjectAtIndex(rIndex*GRID_VOLUME+vIndex, blockProperty);
        }else{
            //add
            mGridPropertyContainer->insertObject(blockProperty, rIndex*GRID_VOLUME+vIndex);
        }
        
        tSuc=true;
    } while (0);
    
    return tSuc;
}

GridElementProperty* MainGameController::getGridElementProperty(unsigned int rIndex,unsigned int vIndex)
{
    GridElementProperty *blockProperty;
    do {
        CC_BREAK_IF(rIndex>=GRID_ROW || vIndex>=GRID_VOLUME);
        
        blockProperty=(GridElementProperty *)mGridPropertyContainer->objectAtIndex(rIndex*GRID_ROW+vIndex);
    } while (0);
    
    return blockProperty;
}
	
void MainGameController::processGridCellSelected(unsigned int rIndex,unsigned int vIndex)
{
    LOG_TRACE
    
    do{
        CC_BREAK_IF(!mStageConnectedElements);
        
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        
        GridCell *cell=gridLayer->getGridCell(rIndex, vIndex);
        CC_BREAK_IF(!cell);
        
        GridElementProperty *blockProperty=cell->getCellProperty();
        CC_BREAK_IF(!blockProperty);
        
        if (mStageConnectedElements->count()==0) {
            insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
            break;
        }else{
            GridCell *preCell=dynamic_cast<GridCell *>(mStageConnectedElements->lastObject()) ;
            CC_BREAK_IF(!preCell);
            GridElementProperty *preBlockProperty=preCell->getCellProperty();
            CC_BREAK_IF(!preBlockProperty);
            
            GridCell *prePreCell=NULL;
            GridElementProperty *prePreBlockProperty=NULL;
            if (mStageConnectedElements->count()>=2) {
                prePreCell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(mStageConnectedElements->count()-2)) ;
                CC_BREAK_IF(!prePreCell);
                prePreBlockProperty=prePreCell->getCellProperty();
                CC_BREAK_IF(!prePreBlockProperty);
            }
            
            if(prePreBlockProperty && blockProperty->mIndex.vIndex==prePreBlockProperty->mIndex.vIndex && blockProperty->mIndex.rIndex== prePreBlockProperty->mIndex.rIndex){
                //remove
                removeCellFromConnectedArray();
            }else{
                if (blockProperty->mType == preBlockProperty->mType) {
                    //same type elements
                    if (preBlockProperty->mType==kElementType_Bow) {
                        //attach distance +1
                        if (abs(preBlockProperty->mIndex.rIndex-blockProperty->mIndex.rIndex)<=2 && abs(preBlockProperty->mIndex.vIndex-blockProperty->mIndex.vIndex)<=2) {
                            
                            insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
                            break;
                        }
                    }else{
                        if (abs(preBlockProperty->mIndex.rIndex-blockProperty->mIndex.rIndex)<=1 && abs(preBlockProperty->mIndex.vIndex-blockProperty->mIndex.vIndex)<=1) {
                            
                            insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
                            break;
                        }
                    }
                }else{
                    //different type
                    if ((blockProperty->mType==kElementType_Bow || blockProperty->mType==kElementType_Sword || blockProperty->mType==kElementType_Monster) && (preBlockProperty->mType==kElementType_Bow || preBlockProperty->mType==kElementType_Sword || preBlockProperty->mType==kElementType_Monster)) {
                        if (preBlockProperty->mType==kElementType_Bow) {
                            //attach distance +1
                            if (abs(preBlockProperty->mIndex.rIndex-blockProperty->mIndex.rIndex)<=2 && abs(preBlockProperty->mIndex.vIndex-blockProperty->mIndex.vIndex)<=2) {
                                
                                insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
                                break;
                            }
                        }else{
                            if (abs(preBlockProperty->mIndex.rIndex-blockProperty->mIndex.rIndex)<=1 && abs(preBlockProperty->mIndex.vIndex-blockProperty->mIndex.vIndex)<=1) {
                                
                                insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
                                break;
                            }
                        }
                    }
                }
                
            }
        }
        
    }while(0);
}

//insert a cell into the connected array
void MainGameController::insertCellIntoConnectedArray(unsigned int rIndex,unsigned int vIndex)
{
    LOG_TRACE
    do{
        if (judgeGridCellCanInserted(rIndex, vIndex)) {
            MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
            CC_BREAK_IF(!gridLayer);
            
            GridCell *cell=gridLayer->getGridCell(rIndex, vIndex);
            CC_BREAK_IF(!cell);
            
            mStageConnectedElements->addObject(cell);
            
            //add the connected line between the two cells
            addConnectedLine();
            
            //play sound effect
            GridElementProperty *blockProperty=cell->getCellProperty();
            playSelctedSoundEffect(blockProperty->mType);
        }
    }while(0);
}

//remove a cell from the connected array
void MainGameController::removeCellFromConnectedArray()
{
    LOG_TRACE
    do{
        CC_BREAK_IF(!mStageConnectedElements || mStageConnectedElements->count()==0);
        GridCell *cell=dynamic_cast<GridCell *>(mStageConnectedElements->lastObject());
        GridElementProperty *blockProperty=cell->getCellProperty();
        
        //remove the connected line between the two cells
        cleanConnectedLine();
        
        mStageConnectedElements->removeLastObject();
        
        //play sound effect
        playSelctedSoundEffect(blockProperty->mType);
    }while(0);
}

void MainGameController::playSelctedSoundEffect(ElementType pType)
{
    LOG_TRACE
    
}

void MainGameController::playClearSoundEffect()
{
    LOG_TRACE
    
}

void MainGameController::addConnectedLine()
{
    LOG_TRACE
    do {
        CC_BREAK_IF(!mStageConnectedElements || mStageConnectedElements->count()<2);
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        GridCell *fCell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(mStageConnectedElements->count()-2));
        GridCell *sCell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(mStageConnectedElements->count()-1));
        gridLayer->addConnectLine(fCell,sCell);
    } while (0);
}

void MainGameController::cleanConnectedLine()
{
    LOG_TRACE
    do {
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        gridLayer->removeConnectLine();
    } while (0);
}

bool MainGameController::judgeGridCellCanInserted(unsigned int rIndex,unsigned int vIndex)
{
    LOG_TRACE
    bool tRet=true;
    
    do {
        CC_BREAK_IF(!mStageConnectedElements || mStageConnectedElements->count()<=0);
        for (int i=0;i<mStageConnectedElements->count();i++) {
            GridCell *item=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(i));
            CC_BREAK_IF(!item);
            
            GridElementProperty *blockProperty=item->getCellProperty();
            if (blockProperty->mIndex.rIndex==rIndex && blockProperty->mIndex.vIndex==vIndex) {
                tRet=false;
                break;
            }
        }
    } while (0);
    //CCLog("tRet:%d",tRet);
    return tRet;
}



