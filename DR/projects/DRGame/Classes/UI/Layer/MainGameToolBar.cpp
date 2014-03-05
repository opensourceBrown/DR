#include "MainGameToolBar.h"
#include "MainGameController.h"

MainGameToolBar::MainGameToolBar():
    m_containerLayer(NULL)
{
    do {
        
    } while (0);
    
}

MainGameToolBar::~MainGameToolBar()
{
    do{
        
    }while(0);
}

MainGameToolBar *MainGameToolBar::create()
{
    MainGameToolBar *layer=new MainGameToolBar();
    do {
        CC_BREAK_IF(!layer);
        //layer->autorelease();
        return layer;
    } while (0);
    
    CC_SAFE_DELETE(layer);
    return NULL;
}

void MainGameToolBar::onEnter()
{
	BaseLayer::onEnter();
    
    this->constructUI();
}

void MainGameToolBar::onExit()
{
	BaseLayer::onExit();
}

void  MainGameToolBar::constructUI()
{
    do{
		m_containerLayer=CCLayerColor::create(ccc4(255,0,0,255));
		CC_BREAK_IF(!m_containerLayer);
		m_containerLayer->setContentSize(CCSizeMake(WIN_SIZE.width,100));
		m_containerLayer->setPosition(ccp(0,WIN_SIZE.height-100));
		addChild(m_containerLayer);
        
        CC_BREAK_IF(!m_delegate);
        
	}while(0);
}

bool MainGameToolBar::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location=pTouch->getLocation();
    do{
        CC_BREAK_IF(!m_delegate);
        
    }while(0);
	
    
	return true;
}

void MainGameToolBar::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location=pTouch->getLocation();
    do{
        
        CC_BREAK_IF(!m_delegate);
        
    }while(0);
}

void MainGameToolBar::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    do{
        CC_BREAK_IF(!m_delegate);
        
    }while(0);
}

void MainGameToolBar::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
