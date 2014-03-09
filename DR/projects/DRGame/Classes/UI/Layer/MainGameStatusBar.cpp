#include "MainGameStatusBar.h"
#include "MainGameController.h"

MainGameStatusBar::MainGameStatusBar():
    m_containerLayer(NULL),
    m_shiledValueTTF(NULL),
    m_portionProgress(NULL),
    m_coinProgress(NULL),
    m_killMonsterProgress(NULL),
    m_scoreProgress(NULL)
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
        CC_BREAK_IF(!tMonster);
        tMonster->setPosition(ccp(WIN_SIZE.width/3+tMonster->getContentSize().width,m_containerLayer->getContentSize().height-tMonster->getContentSize().height));
        m_containerLayer->addChild(tMonster);
        
        CCSprite *tShield=CCSprite::createWithSpriteFrameName("Grid_cell_shield.png");
        CC_BREAK_IF(!tShield);
        tShield->setPosition(ccp(WIN_SIZE.width/3+WIN_SIZE.width/9+tShield->getContentSize().width,m_containerLayer->getContentSize().height-tShield->getContentSize().height));
        m_containerLayer->addChild(tShield);
        
        CCSprite *tSword=CCSprite::createWithSpriteFrameName("Grid_cell_sword.png");
        CC_BREAK_IF(!tSword);
        tSword->setPosition(ccp(WIN_SIZE.width/3+2*WIN_SIZE.width/9+tSword->getContentSize().width,m_containerLayer->getContentSize().height-tSword->getContentSize().height));
        m_containerLayer->addChild(tSword);
        
        CCString *baseAttachValue=CCString::createWithFormat("+%d",3);
        CCLabelTTF *tBaseAttackValueTTF = CCLabelTTF::create(baseAttachValue->getCString(),"Marker Felt",24);
        CC_BREAK_IF(!tBaseAttackValueTTF);
        tBaseAttackValueTTF->setAnchorPoint(ccp(0.5,0.5));
        tBaseAttackValueTTF->setColor(ccc3(0,0,255));
        tBaseAttackValueTTF->setPosition(ccp(tMonster->getPosition().x,tMonster->getPosition().y-tMonster->getContentSize().height));
        m_containerLayer->addChild(tBaseAttackValueTTF);
        
        int maxShieldValue=4;
        int curShieldValue=4;
        CCString *shieldValue=CCString::createWithFormat("%d/%d",curShieldValue,maxShieldValue);
        m_shiledValueTTF = CCLabelTTF::create(shieldValue->getCString(),"Marker Felt",24);
        CC_BREAK_IF(!m_shiledValueTTF);
        m_shiledValueTTF->setAnchorPoint(ccp(0.5,0.5));
        m_shiledValueTTF->setColor(ccc3(0,0,255));
        m_shiledValueTTF->setPosition(ccp(tShield->getPosition().x,tShield->getPosition().y-tShield->getContentSize().height));
        m_containerLayer->addChild(m_shiledValueTTF);
        
        int damageValue=2;
        CCString *equitAttachValue=CCString::createWithFormat("+%d",damageValue);
        CCLabelTTF *tEquipDamageValueTTF = CCLabelTTF::create(equitAttachValue->getCString(),"Marker Felt",24);
        CC_BREAK_IF(!tEquipDamageValueTTF);
        tEquipDamageValueTTF->setAnchorPoint(ccp(0.5,0.5));
        tEquipDamageValueTTF->setColor(ccc3(0,0,255));
        tEquipDamageValueTTF->setPosition(ccp(tSword->getPosition().x,tSword->getPosition().y-tSword->getContentSize().height));
        m_containerLayer->addChild(tEquipDamageValueTTF);
        
        float tScaleX=1;
        //portion
        m_portionObit=CCSprite::createWithSpriteFrameName("GR_progress_obit.png");
        CC_BREAK_IF(!m_portionObit);
        if (m_portionObit->getContentSize().width/(m_containerLayer->getContentSize().width/3)>1) {
            tScaleX=(m_containerLayer->getContentSize().width/3)/m_portionObit->getContentSize().width;
        }
        m_portionObit->setPosition(ccp(15+m_portionObit->getContentSize().width/2,m_containerLayer->getContentSize().height-m_portionObit->getContentSize().height-15));
        m_portionObit->setScaleX(tScaleX);
        m_containerLayer->addChild(m_portionObit);
        
        m_portionProgress=CCProgressTimer::create(CCSprite::createWithSpriteFrameName("GR_progress_timer.png"));
        CC_BREAK_IF(!m_portionProgress);
        m_portionProgress->setType(kCCProgressTimerTypeBar);
        m_portionProgress->setBarChangeRate(ccp(1, 0));
        m_portionProgress->setPercentage(70);
        m_portionProgress->setAnchorPoint(ccp(0,0.5));
        m_portionProgress->setScaleX(tScaleX);
        m_portionProgress->setPosition(ccp(m_portionObit->getPosition().x-m_portionObit->getContentSize().width/2-(m_portionObit->getContentSize().width-m_portionProgress->getContentSize().width*m_portionProgress->getPercentage()/100)/2,m_portionObit->getPosition().y));
        m_containerLayer->addChild(m_portionProgress);
        
        //coin
        m_coinObit=CCSprite::createWithSpriteFrameName("GR_progress_obit.png");
        CC_BREAK_IF(!m_coinObit);
        m_coinObit->setScaleX(tScaleX);
        m_coinObit->setPosition(ccp(15+m_coinObit->getContentSize().width/2,m_containerLayer->getContentSize().height-2*m_coinObit->getContentSize().height-35));
        m_containerLayer->addChild(m_coinObit);
        
        m_coinProgress=CCProgressTimer::create(CCSprite::createWithSpriteFrameName("GR_progress_timer.png"));
        CC_BREAK_IF(!m_coinProgress);
        m_coinProgress->setType(kCCProgressTimerTypeBar);
        m_coinProgress->setBarChangeRate(ccp(1, 0));
        m_coinProgress->setPercentage(15);
        m_coinProgress->setAnchorPoint(ccp(0,0.5));
        m_coinProgress->setScaleX(tScaleX);
        m_coinProgress->setPosition(ccp(m_coinObit->getPosition().x-m_coinObit->getContentSize().width/2-(m_coinObit->getContentSize().width-m_coinProgress->getContentSize().width*m_coinProgress->getPercentage()/100)/2,m_coinObit->getPosition().y));
        m_containerLayer->addChild(m_coinProgress);
        
        //kill monster
        m_killMonsterObit=CCSprite::createWithSpriteFrameName("GR_progress_obit.png");
        CC_BREAK_IF(!m_killMonsterObit);
        m_killMonsterObit->setScaleX(tScaleX);
        m_killMonsterObit->setPosition(ccp(2*m_containerLayer->getContentSize().width/3+20+m_killMonsterObit->getContentSize().width/2,m_containerLayer->getContentSize().height-m_killMonsterObit->getContentSize().height-15));
        m_containerLayer->addChild(m_killMonsterObit);
        
        m_killMonsterProgress=CCProgressTimer::create(CCSprite::createWithSpriteFrameName("GR_progress_timer.png"));
        CC_BREAK_IF(!m_killMonsterProgress);
        m_killMonsterProgress->setType(kCCProgressTimerTypeBar);
        m_killMonsterProgress->setBarChangeRate(ccp(1, 0));
        m_killMonsterProgress->setPercentage(40);
        m_killMonsterProgress->setAnchorPoint(ccp(0,0.5));
        m_killMonsterProgress->setScaleX(tScaleX);
        m_killMonsterProgress->setPosition(ccp(m_killMonsterObit->getPosition().x-m_killMonsterObit->getContentSize().width/2-(m_killMonsterObit->getContentSize().width-m_killMonsterProgress->getContentSize().width*m_killMonsterProgress->getPercentage()/100)/2,m_killMonsterObit->getPosition().y));
        m_containerLayer->addChild(m_killMonsterProgress);
        
        //score
        m_scoreObit=CCSprite::createWithSpriteFrameName("GR_progress_obit.png");
        CC_BREAK_IF(!m_scoreObit);
        m_scoreObit->setScaleX(tScaleX);
        m_scoreObit->setPosition(ccp(2*m_containerLayer->getContentSize().width/3+20+m_scoreObit->getContentSize().width/2,m_containerLayer->getContentSize().height-2*m_scoreObit->getContentSize().height-35));
        m_containerLayer->addChild(m_scoreObit);
        
        m_scoreProgress=CCProgressTimer::create(CCSprite::createWithSpriteFrameName("GR_progress_timer.png"));
        CC_BREAK_IF(!m_scoreProgress);
        m_scoreProgress->setType(kCCProgressTimerTypeBar);
        m_scoreProgress->setBarChangeRate(ccp(1, 0));
        m_scoreProgress->setPercentage(20);
        m_scoreProgress->setAnchorPoint(ccp(0,0.5));
        m_scoreProgress->setScaleX(tScaleX);
        m_scoreProgress->setPosition(ccp(m_scoreObit->getPosition().x-m_scoreObit->getContentSize().width/2-(m_scoreObit->getContentSize().width-m_scoreProgress->getContentSize().width*m_scoreProgress->getPercentage()/100)/2,m_scoreObit->getPosition().y));
        m_containerLayer->addChild(m_scoreProgress);
		
	}while(0);
}

void MainGameStatusBar::setPortionProgress(int pValue)
{
    do {
        CC_BREAK_IF(!m_portionProgress);
        m_portionProgress->setPercentage(pValue>100?100:pValue);
        m_portionProgress->setPosition(ccp(m_portionObit->getPosition().x-m_portionObit->getContentSize().width/2-(m_portionObit->getContentSize().width-m_portionProgress->getContentSize().width*m_portionProgress->getPercentage()/100)/2,m_portionObit->getPosition().y));
    } while (0);
}

float MainGameStatusBar::getPortionProgress()
{
    float tProgress=0;
    do {
        CC_BREAK_IF(!m_portionProgress);
        tProgress=m_portionProgress->getPercentage();
    } while (0);
    
    return tProgress;
}

void MainGameStatusBar::setCoinProgress(int pValue)
{
    do {
        CC_BREAK_IF(!m_coinProgress);
        m_coinProgress->setPercentage(pValue>100?100:pValue);
        m_coinProgress->setPosition(ccp(m_coinObit->getPosition().x-m_coinObit->getContentSize().width/2-(m_coinObit->getContentSize().width-m_coinProgress->getContentSize().width*m_coinProgress->getPercentage()/100)/2,m_coinObit->getPosition().y));
    } while (0);
}

float MainGameStatusBar::getCoinProgress()
{
    float tProgress=0;
    do {
        CC_BREAK_IF(!m_coinProgress);
        tProgress=m_coinProgress->getPercentage();
    } while (0);
    
    return tProgress;
}

void MainGameStatusBar::setKillMonsterProgress(int pValue)
{
    do {
        CC_BREAK_IF(!m_killMonsterProgress);
        m_killMonsterProgress->setPercentage(pValue>100?100:pValue);
        m_killMonsterProgress->setPosition(ccp(m_killMonsterObit->getPosition().x-m_killMonsterObit->getContentSize().width/2-(m_killMonsterObit->getContentSize().width-m_killMonsterProgress->getContentSize().width*m_killMonsterProgress->getPercentage()/100)/2,m_killMonsterObit->getPosition().y));
    } while (0);
}

float MainGameStatusBar::getKillMonsterProgress()
{
    float tProgress=0;
    do {
        CC_BREAK_IF(!m_killMonsterProgress);
        tProgress=m_killMonsterProgress->getPercentage();
    } while (0);
    
    return tProgress;
}

void MainGameStatusBar::setScoreProgress(int pValue)
{
    do {
        CC_BREAK_IF(!m_scoreProgress);
        m_scoreProgress->setPercentage(pValue>100?100:pValue);
        m_scoreProgress->setPosition(ccp(m_scoreObit->getPosition().x-m_scoreObit->getContentSize().width/2-(m_scoreObit->getContentSize().width-m_scoreProgress->getContentSize().width*m_scoreProgress->getPercentage()/100)/2,m_scoreObit->getPosition().y));
    } while (0);
}

float MainGameStatusBar::getScoreProgress()
{
    float tProgress=0;
    do {
        CC_BREAK_IF(!m_scoreProgress);
        tProgress=m_scoreProgress->getPercentage();
    } while (0);
    
    return tProgress;
}

void MainGameStatusBar::setShieldValue(int curValue,int maxValue)
{
    do {
        CC_BREAK_IF(!m_shiledValueTTF);
        CCString *shieldValue=CCString::createWithFormat("%d/%d",curValue,maxValue);
        m_shiledValueTTF->setString(shieldValue->getCString());
    } while (0);
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
