/****************************************************************************
//ͨ������ģ����
****************************************************************************/
#include "MainGameController.h"
#include "MainGameScene.h"


MainGameController::MainGameController()
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

//����grid cell
void MainGameController::generateGridCell(unsigned int rIndex,unsigned int vIndex)
{

}
	
//����grid cell��λ�ú�����
void MainGameController::updateGridCell(unsigned int rIndex,unsigned int vIndex)
{

}
	
//�жϻ��������е�Ԫ���Ƿ��������
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



