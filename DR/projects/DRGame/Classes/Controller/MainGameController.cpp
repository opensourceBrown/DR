/****************************************************************************
//通用数据模型类
****************************************************************************/
#include "MainGameController.h"


MainGameController::MainGameController()
{
   
}

MainGameController::~MainGameController()
{
	
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
void MainGameController::generateGridCell(unsigned int rIndex,unsigned int vIndex)
{

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
void MainGameController::insertCellIntoConnectedArray(unsigned int pIndex)
{
    
}

//remove a cell from the connected array
void MainGameController::removeCellFromConnectedArray(unsigned int pIndex)
{
    
}

//insert a cell into the cell container
void MainGameController::insertCellIntoGridContainer(unsigned int pIndex)
{
    
}

//remove a cell from the cell container(clear a cell from the screen for connecting)
void MainGameController::removeCellFromGridContainer(unsigned int pIndex)
{
    
}



