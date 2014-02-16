#include "MainGameScene.h"
#include "BaseController.h"
#include "MainGameGridLayer.h"

USING_NS_CC;

MainGameScene::MainGameScene():
    m_delegate(NULL),
    m_gridLayer(NULL),
    m_statusBar(NULL),
    m_toolBar(NULL)
{
    
}

MainGameScene::~MainGameScene()
{
    
}

bool MainGameScene::initWithDelegate(MainGameController *pDelegate)
{
    bool tRet=false;
    do{
        CC_BREAK_IF(!init());
        CC_BREAK_IF(!pDelegate);
        
        m_delegate=pDelegate;
        tRet=true;
    }while(0);
    
    return tRet;
}

void MainGameScene::constructUI()
{
    do{
        
    }while(0);
}
