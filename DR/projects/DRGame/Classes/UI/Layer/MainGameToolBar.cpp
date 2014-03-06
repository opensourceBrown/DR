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
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("MainGame.plist");
    
    this->constructUI();
}

void MainGameToolBar::onExit()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("MainGame.plist");
    
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
        
        int index=0;
        CCSprite *tSkillBG1=CCSprite::createWithSpriteFrameName("Main_game_skill_bg.png");
        CC_BREAK_IF(!tSkillBG1);
        tSkillBG1->setPosition(ccp(index*m_containerLayer->getContentSize().width/6+(m_containerLayer->getContentSize().width/6)/2,m_containerLayer->getContentSize().height/2));
        m_containerLayer->addChild(tSkillBG1);
        
        index++;
        CCSprite *tSkillBG2=CCSprite::createWithSpriteFrameName("Main_game_skill_bg.png");
        CC_BREAK_IF(!tSkillBG2);
        tSkillBG2->setPosition(ccp(index*m_containerLayer->getContentSize().width/6+(m_containerLayer->getContentSize().width/6)/2,m_containerLayer->getContentSize().height/2));
        m_containerLayer->addChild(tSkillBG2);
        
        index++;
        CCSprite *tSkillBG3=CCSprite::createWithSpriteFrameName("Main_game_skill_bg.png");
        CC_BREAK_IF(!tSkillBG3);
        tSkillBG3->setPosition(ccp(index*m_containerLayer->getContentSize().width/6+(m_containerLayer->getContentSize().width/6)/2,m_containerLayer->getContentSize().height/2));
        m_containerLayer->addChild(tSkillBG3);
        
        index++;
        CCSprite *tSkillBG4=CCSprite::createWithSpriteFrameName("Main_game_skill_bg.png");
        CC_BREAK_IF(!tSkillBG4);
        tSkillBG4->setPosition(ccp(index*m_containerLayer->getContentSize().width/6+(m_containerLayer->getContentSize().width/6)/2,m_containerLayer->getContentSize().height/2));
        m_containerLayer->addChild(tSkillBG4);
        
        ccColor3B selColor = ccc3(150, 150, 150);
        CCSprite *tMenuItemSP1=CCSprite::createWithSpriteFrameName("Main_game_menu.png");
        CC_BREAK_IF(!tMenuItemSP1);
        CCSprite *tMenuItemSP2=CCSprite::createWithSpriteFrameName("Main_game_menu.png");
        CC_BREAK_IF(!tMenuItemSP2);
        tMenuItemSP2->setScale(1.1);
        tMenuItemSP2->setColor(selColor);
        CCMenuItemSprite *menuItem = CCMenuItemSprite::create(tMenuItemSP1, tMenuItemSP2,this, menu_selector(MainGameToolBar::menuItemClicked));
        CC_BREAK_IF(!menuItem);
        menuItem->setPosition(ccp(m_containerLayer->getContentSize().width-m_containerLayer->getContentSize().width/6, m_containerLayer->getContentSize().height/2+tMenuItemSP2->getContentSize().height));
        
        CCSprite *tStatusItemSP1=CCSprite::createWithSpriteFrameName("Main_game_status.png");
        CC_BREAK_IF(!tStatusItemSP1);
        CCSprite *tStatusItemSP2=CCSprite::createWithSpriteFrameName("Main_game_status.png");
        CC_BREAK_IF(!tStatusItemSP2);
        tStatusItemSP2->setScale(1.1);
        tStatusItemSP2->setColor(selColor);
        CCMenuItemSprite *statusItem = CCMenuItemSprite::create(tStatusItemSP1, tStatusItemSP2,this, menu_selector(MainGameToolBar::statusItemClicked));
        CC_BREAK_IF(!statusItem);
        statusItem->setPosition(ccp(m_containerLayer->getContentSize().width-m_containerLayer->getContentSize().width/6, m_containerLayer->getContentSize().height/2-tStatusItemSP2->getContentSize().height));
        CCMenu *menu = CCMenu::create(menuItem,statusItem,NULL);
        CC_BREAK_IF(!menu);
        m_containerLayer->addChild(menu);
        
	}while(0);
}

void MainGameToolBar::menuItemClicked(CCObject *pSender)
{
    CCLog("%s",__FUNCTION__);
}

void MainGameToolBar::statusItemClicked(CCObject *pSender)
{
    CCLog("%s",__FUNCTION__);
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
