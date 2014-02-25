/****************************************************************************
//Õ®”√ ˝æ›ƒ£–Õ¿‡
****************************************************************************/
#include "MainGameController.h"
#include "MainGameScene.h"
#include "MainGameGridLayer.h"
#include "GridCell.h"
#include "DataMangager.h"

MainGameController::MainGameController():
    mGridCellContainer(NULL),
    mMagicInStage(NULL),
    mStageConnectedElements(NULL)
{
   
}

MainGameController::~MainGameController()
{
	CC_SAFE_RELEASE(mGridCellContainer);
    CC_SAFE_RELEASE(mMagicInStage);
    CC_SAFE_RELEASE(mStageConnectedElements);
    CC_SAFE_RELEASE(m_scene);
}

MainGameController *MainGameController::create()
{
    MainGameController *controller=new MainGameController();
    do {
        CC_BREAK_IF(!controller || !(controller->initWith()));
        controller->autorelease();
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
        m_scene=MainGameScene::create(this);
        CC_BREAK_IF(!m_scene);
        m_scene->retain();
        
        mGridCellContainer=CCArray::createWithCapacity(GRID_ROW*GRID_VOLUME);
        CC_BREAK_IF(!mGridCellContainer);
        mGridCellContainer->retain();
        
        mMagicInStage=CCArray::create();
        CC_BREAK_IF(!mMagicInStage);
        mMagicInStage->retain();
        
        mStageConnectedElements=CCArray::create();
        CC_BREAK_IF(!mStageConnectedElements);
        mStageConnectedElements->retain();
        tRet=true;
    } while (0);
    
    return tRet;
}

bool MainGameController::judgeGameIsEnd()
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

bool MainGameController::judgeConnectedElementsCanClear()
{
	bool tRet=false;
    
    do{
        CC_BREAK_IF(!mStageConnectedElements || mStageConnectedElements->count()<3);
        tRet=true;
    }while(0);
    
	return tRet;
}

//…˙≥…grid cell
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
                //test
                blockProperty->mIndex.rIndex=rIndex;
                blockProperty->mIndex.vIndex=vIndex;
                blockProperty->mType=kElementType_Sword;
                blockProperty->mID=11;
                
                blockProperty->saveToDictionary(rDict);
            }
        } else {
            //test
            blockProperty->mIndex.rIndex=rIndex;
            blockProperty->mIndex.vIndex=vIndex;
            blockProperty->mType=kElementType_Sword;
            blockProperty->mID=11;
            
            blockProperty->saveToDictionary(rDict);
        }
        
        
        //generate cell property according to the configure(rate)
        
        mGridPropertyContainer[rIndex*GRID_ROW+vIndex]=blockProperty;
        tSuc=true;
    } while (0);
    
    return tSuc;
}

GridElementProperty* MainGameController::getGridElementProperty(unsigned int rIndex,unsigned int vIndex)
{
    GridElementProperty *blockProperty;
    do {
        CC_BREAK_IF(rIndex>=GRID_ROW || vIndex>=GRID_VOLUME);
        
        blockProperty=mGridPropertyContainer[rIndex*GRID_ROW+vIndex];
    } while (0);
    
    return blockProperty;
}
	
//∏¸–¬grid cell£∫Œª÷√∫ÕÀ˜“˝
void MainGameController::updateGridCell(unsigned int rIndex,unsigned int vIndex)
{
    
}
	
//≈–∂œª¨∂Øπ˝≥Ã÷–µƒ‘™Àÿ «∑Òø…“‘œ‡¡¨
bool MainGameController::judgeElementsCanConnected(unsigned int rIndex,unsigned int vIndex)
{
    bool tRet=false;
    
    do{
        CC_BREAK_IF(!mStageConnectedElements);
        
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        
        GridCell *cell=gridLayer->getGridCell(rIndex, vIndex);
        CC_BREAK_IF(!cell);
        
        GridElementProperty *blockProperty=cell->getCellProperty();
        
        if (mStageConnectedElements->count()<=0) {
            //activate the first selected effect
            
        }
        
        
        if (mStageConnectedElements->count()==0) {
            insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
            tRet=true;
            break;
        }else{
            GridCell *preCell=dynamic_cast<GridCell *>(mStageConnectedElements->lastObject()) ;
            CC_BREAK_IF(!preCell);
            GridElementProperty *preBlockProperty=preCell->getCellProperty();
            
            if (blockProperty->mIndex.vIndex==preBlockProperty->mIndex.vIndex && blockProperty->mIndex.rIndex== preBlockProperty->mIndex.rIndex) {
                //remove
                removeCellFromConnectedArray();
            }else{
                if (blockProperty->mType == preBlockProperty->mType) {
                    //same type elements
                    if (preBlockProperty->mType==kElementType_Bow) {
                        //attach distance +1
                        if (abs(preBlockProperty->mIndex.rIndex-blockProperty->mIndex.rIndex)<=2 && abs(preBlockProperty->mIndex.vIndex-blockProperty->mIndex.vIndex)<=2) {
                            
                            insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
                            tRet=true;
                            break;
                        }
                    }else{
                        if (abs(preBlockProperty->mIndex.rIndex-blockProperty->mIndex.rIndex)<=1 && abs(preBlockProperty->mIndex.vIndex-blockProperty->mIndex.vIndex)<=1) {
                            
                            insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
                            tRet=true;
                            break;
                        }
                    }
                }else{
                    //different type
                    if (blockProperty->mType==kElementType_Bow || blockProperty->mType==kElementType_Sword || blockProperty->mType==kElementType_Monster) {
                        if (preBlockProperty->mType==kElementType_Bow) {
                            //attach distance +1
                            if (abs(preBlockProperty->mIndex.rIndex-blockProperty->mIndex.rIndex)<=2 && abs(preBlockProperty->mIndex.vIndex-blockProperty->mIndex.vIndex)<=2) {
                                
                                insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
                                tRet=true;
                                break;
                            }
                        }else{
                            if (abs(preBlockProperty->mIndex.rIndex-blockProperty->mIndex.rIndex)<=1 && abs(preBlockProperty->mIndex.vIndex-blockProperty->mIndex.vIndex)<=1) {
                                
                                insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
                                tRet=true;
                                break;
                            }
                        }
                    }
                }
                
            }
        }
        
    }while(0);
    
    return tRet;
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
        mStageConnectedElements->removeLastObject();
        
        //remove the connected line between the two cells
        cleanConnectedLine();
        
        //play sound effect
        playSelctedSoundEffect(blockProperty->mType);
    }while(0);
}

//insert a cell into the cell container
//void MainGameController::insertCellIntoGridContainer(unsigned int pIndex)
//{
//    //judge whether the cell has been in connected array
//    
//}

//remove a cell from the cell container(clear a cell from the screen for connecting)
void MainGameController::removeCellFromGridContainer(unsigned int pIndex)
{
    
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
    
}

void MainGameController::cleanConnectedLine()
{
    LOG_TRACE
    do{
        
    }while(0);
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
    
    return tRet;
}



