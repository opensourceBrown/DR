#include "MainGameStatusBar.h"
#include "MainGameController.h"

MainGameStatusBar::MainGameStatusBar():
    m_containerLayer(NULL)
{
    do {
        
    } while (0);
    
}

MainGameStatusBar::~MainGameStatusBar()
{
    do{
        
    }while(0);
}

MainGameStatusBar *MainGameStatusBar::create()
{
    MainGameStatusBar *layer=new MainGameStatusBar();
    do {
        CC_BREAK_IF(!layer);
        //layer->autorelease();
        return layer;
    } while (0);
    
    CC_SAFE_DELETE(layer);
    return NULL;
}

void MainGameStatusBar::onEnter()
{
	BaseLayer::onEnter();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("MainGame.plist");
    
    this->constructUI();
}

void MainGameStatusBar::onExit()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("MainGame.plist");
    
	BaseLayer::onExit();
}

void  MainGameStatusBar::constructUI()
{
    do{
		m_containerLayer=CCLayerColor::create(ccc4(0,255,0,255));
		CC_BREAK_IF(!m_containerLayer);
		m_containerLayer->setContentSize(CCSizeMake(WIN_SIZE.width,100));
		addChild(m_containerLayer);
        
        CCSprite *tMonster=CCSprite::createWithSpriteFrameName("Grid_cell_monster.png");
        tMonster->setPosition(ccp(WIN_SIZE.width/3,m_containerLayer->getContentSize().height-tMonster->getContentSize().height));
        m_containerLayer->addChild(tMonster);
        
        CCSprite *tShield=CCSprite::createWithSpriteFrameName("Grid_cell_shield.png");
        tShield->setPosition(ccp(WIN_SIZE.width/3+WIN_SIZE.width/9,m_containerLayer->getContentSize().height-tShield->getContentSize().height));
        m_containerLayer->addChild(tShield);
        
        CCSprite *tSword=CCSprite::createWithSpriteFrameName("Grid_cell_sword.png");
        tSword->setPosition(ccp(WIN_SIZE.width/3+2*WIN_SIZE.width/9,m_containerLayer->getContentSize().height-tSword->getContentSize().height));
        m_containerLayer->addChild(tSword);
        
        CCString *baseAttachValue=CCString::createWithFormat("+%d",3);
        CCLabelTTF *tBaseAttackValueTTF = CCLabelTTF::create(baseAttachValue->getCString(),"Marker Felt",28);
        tBaseAttackValueTTF->setAnchorPoint(ccp(0.5,0.5));
        tBaseAttackValueTTF->setColor(ccc3(0,0,255));
        tBaseAttackValueTTF->setPosition(ccp(tMonster->getPosition().x,tMonster->getPosition().y-tMonster->getContentSize().height));
        m_containerLayer->addChild(tBaseAttackValueTTF);
        
        int maxShieldValue=4;
        int curShieldValue=4;
        CCString *shieldValue=CCString::createWithFormat("%d/%d",curShieldValue,maxShieldValue);
        CCLabelTTF *tShiledValueTTF = CCLabelTTF::create(shieldValue->getCString(),"Marker Felt",28);
        tShiledValueTTF->setAnchorPoint(ccp(0.5,0.5));
        tShiledValueTTF->setColor(ccc3(0,0,255));
        tShiledValueTTF->setPosition(ccp(tShield->getPosition().x,tShield->getPosition().y-tShield->getContentSize().height));
        m_containerLayer->addChild(tShiledValueTTF);
        
        int damageValue=2;
        CCString *equitAttachValue=CCString::createWithFormat("+%d",damageValue);
        CCLabelTTF *tEquipDamageValueTTF = CCLabelTTF::create(equitAttachValue->getCString(),"Marker Felt",28);
        tEquipDamageValueTTF->setAnchorPoint(ccp(0.5,0.5));
        tEquipDamageValueTTF->setColor(ccc3(0,0,255));
        tEquipDamageValueTTF->setPosition(ccp(tSword->getPosition().x,tSword->getPosition().y-tSword->getContentSize().height));
        m_containerLayer->addChild(tEquipDamageValueTTF);
		
	}while(0);
}

bool MainGameStatusBar::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    
	return true;
}

void MainGameStatusBar::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void MainGameStatusBar::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void MainGameStatusBar::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
