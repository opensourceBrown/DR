/****************************************************************************
//通用数据模型类
****************************************************************************/
#include "MainGameController.h"
#include "MainGameScene.h"


MainGameController::MainGameController():
    mGridCellContainer(NULL),
    mMagicInStage(NULL),
    mStageConnectedElements(NULL)
{
   
}

MainGameController::~MainGameController()
{
	
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
    CCLog("%s",__FUNCTION__);
    bool tRet=false;
    do {
        //TO:DO initialization
        m_scene=MainGameScene::create(this);
        CC_BREAK_IF(!m_scene);
        
        mGridCellContainer=CCArray::create();
        CC_BREAK_IF(!mGridCellContainer);
        
        mMagicInStage=CCArray::create();
        CC_BREAK_IF(!mMagicInStage);
        
        mStageConnectedElements=CCArray::create();
        CC_BREAK_IF(!mStageConnectedElements);
        tRet=true;
    } while (0);
    
    return tRet;
}

bool MainGameController::judgeGameIsEnd()
{
	return true;
}

bool MainGameController::judgeConnectedElementsCanClear()
{
	return true;
}

//生成grid cell
bool MainGameController::generateGridCell(unsigned int rIndex,unsigned int vIndex)
{
    bool tSuc=false;
    
    do {
        GridElementProperty blockProperty;
        blockProperty.init();
        
        //test
        blockProperty.mIndex.rIndex=rIndex;
        blockProperty.mIndex.vIndex=vIndex;
        blockProperty.mType=kElementType_Sword;
        blockProperty.mID=11;
        
        //generate cell property according to the configure(rate)
        
        mGridPropertyContainer[rIndex*GRID_ROW+vIndex]=blockProperty;
        tSuc=true;
    } while (0);
    
    return tSuc;
}

GridElementProperty MainGameController::getGridElementProperty(unsigned int rIndex,unsigned int vIndex)
{
    GridElementProperty blockProperty;
    do {
        CC_BREAK_IF(rIndex>=GRID_ROW || vIndex>=GRID_VOLUME);
        
        blockProperty=mGridPropertyContainer[rIndex*GRID_ROW+vIndex];
    } while (0);
    
    return blockProperty;
}
	
//更新grid cell：位置和索引
void MainGameController::updateGridCell(unsigned int rIndex,unsigned int vIndex)
{

}
	
//判断滑动过程中的元素是否可以相连
bool MainGameController::judgeElementsCanConnected()
{
    return true;
}

//insert a cell into the connected array
void MainGameController::insertCellIntoConnectedArray(unsigned int rIndex,unsigned int vIndex)
{
    
}

//remove a cell from the connected array
void MainGameController::removeCellFromConnectedArray(unsigned int pIndex)
{
    
}

//insert a cell into the cell container
void MainGameController::insertCellIntoGridContainer(unsigned int pIndex)
{
    //play sound effect
    
    //judge whether the cell has been in connected array
    
}

//remove a cell from the cell container(clear a cell from the screen for connecting)
void MainGameController::removeCellFromGridContainer(unsigned int pIndex)
{
    
}



