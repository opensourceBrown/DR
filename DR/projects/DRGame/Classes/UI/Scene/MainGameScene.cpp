#include "MainGameScene.h"
#include "BaseController.h"
#include "MainGameGridLayer.h"


USING_NS_CC;

MainGameScene::MainGameScene():
    m_gridLayer(NULL),
    m_statusBar(NULL),
    m_toolBar(NULL)
{
    
}

MainGameScene::~MainGameScene()
{
    
}

void MainGameScene::constructUI()
{
    do{
        m_gridLayer=new MainGameGridLayer();
		CC_BREAK_IF(!m_gridLayer);
		m_gridLayer->initWithDelegate(m_delegate);
        m_gridLayer->constructUI();
		addChild(m_gridLayer);
        
        /*
		m_statusBar=CCLayer::create();
		CC_BREAK_IF(!m_statusBar);
		addChild(m_statusBar);

		m_toolBar=CCLayer::create();
		CC_BREAK_IF(!m_toolBar);
		addChild(m_toolBar);

		CCLayerColor *statusInfoContainer=CCLayerColor::create(ccc4(256, 0, 0, 256));
        statusInfoContainer->setContentSize(CCSizeMake(WIN_SIZE.width, 80.0));
		statusInfoContainer->setPosition(CCPointZero);
		m_statusBar->addChild(statusInfoContainer);

		CCLayerColor *toolContainer=CCLayerColor::create(ccc4(0, 256, 0, 256));
		toolContainer->setContentSize(CCSizeMake(WIN_SIZE.width,80.0));
		toolContainer->setPosition(ccp(0,WIN_SIZE.height-80));
		m_toolBar->addChild(statusInfoContainer);

		//status bar
		CCLabelTTF *coinLabel=NULL;
		CCLabelTTF *roundLabel=NULL;
		CCLabelTTF *scoreLabel=NULL;
		CCLabelTTF *killdMonsterLabel=NULL;
		CCLabelTTF *healthLabel=NULL;

		CCSprite *baseDamageIcon=NULL;
		CCSprite *shieldIcon=NULL;
		CCSprite *weaponDamageIcon=NULL;
		CCLabelTTF *baseDamageLabel=NULL;
		CCLabelTTF *shieldLabel=NULL;
		CCLabelTTF *weaponDamageLabel=NULL;

		//tool bar

         */
    }while(0);
}
