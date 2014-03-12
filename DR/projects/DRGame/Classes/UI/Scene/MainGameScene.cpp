#include "MainGameScene.h"
#include "BaseController.h"
#include "MainGameGridLayer.h"
#include "DataMangager.h"
#include "DRUtility.h"
#include "MainGameStatusBar.h"
#include "MainGameToolBar.h"

USING_NS_CC;

MainGameScene::MainGameScene():
    m_gridLayer(NULL),
    m_statusBar(NULL),
    m_toolBar(NULL)
{
    LOG_TRACE
}

MainGameScene::~MainGameScene()
{
    CC_SAFE_DELETE(m_gridLayer);
    CC_SAFE_DELETE(m_statusBar);
    CC_SAFE_DELETE(m_toolBar);
}

MainGameScene *MainGameScene::create(BaseController *pDelegate)
{
    MainGameScene *scene=new MainGameScene();
    do {
        CC_BREAK_IF(!scene || !(scene->initWith(pDelegate)));
        //scene->autorelease();
        return scene;
    } while (0);
    
    CC_SAFE_DELETE(scene);
    return NULL;
}

bool MainGameScene::initWith(BaseController *pDelegate)
{
	bool tRet = false;
	do{
        CC_BREAK_IF(!init());
		CC_BREAK_IF(!pDelegate);
		m_delegate=pDelegate;
        
        this->constructUI();
        
		tRet = true;
	}while(0);
    
	return tRet;
}

void MainGameScene::constructUI()
{
    do{
        m_gridLayer=MainGameGridLayer::create();
		CC_BREAK_IF(!m_gridLayer);
        m_gridLayer->retain();
		m_gridLayer->setDelegate(m_delegate);
		addChild(m_gridLayer);
        
		m_statusBar=MainGameStatusBar::create();
		CC_BREAK_IF(!m_statusBar);
        m_statusBar->retain();
		m_statusBar->setDelegate(m_delegate);
		addChild(m_statusBar);

		m_toolBar=MainGameToolBar::create();
		CC_BREAK_IF(!m_toolBar);
        m_toolBar->retain();
		m_toolBar->setDelegate(m_delegate);
		addChild(m_toolBar);
        
    }while(0);
}

MainGameGridLayer *MainGameScene::getGridLayer()
{
    LOG_TRACE
    CCAssert(m_gridLayer, "m_gridLayer is null");
    
    return m_gridLayer;
}

MainGameStatusBar *MainGameScene::getStatusLayer()
{
    LOG_TRACE
    CCAssert(m_statusBar, "status bar is null");
    return m_statusBar;
}

MainGameToolBar *MainGameScene::getToolBar()
{
    LOG_TRACE
    CCAssert(m_toolBar, "tool bar is null");
    return m_toolBar;
}
