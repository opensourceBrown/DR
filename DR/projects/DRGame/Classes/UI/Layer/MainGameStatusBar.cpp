#include "MainGameStatusBar.h"
#include "MainGameController.h"

#define STATUS_CONTAINER_TAG        50
#define STATUS_PORTION_TAG          100
#define STATUS_COIN_TAG             101
#define STATUS_KILLMONSTER_TAG      102
#define STATUS_SCORE_TAG            103
#define STATUS_SHIELD_TAG           105
#define STATUS_PORTION_OBIT_TAG     110
#define STATUS_COIN_OBIT_TAG        111
#define STATUS_KILLMONSTER_OBIT_TAG 112
#define STATUS_SCORE_OBIT_TAG       113

MainGameStatusBar::MainGameStatusBar()
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
		CCLayerColor *containerLayer=CCLayerColor::create(ccc4(0,255,0,255));
		CC_BREAK_IF(!containerLayer);
        containerLayer->setTag(STATUS_CONTAINER_TAG);
		containerLayer->setContentSize(CCSizeMake(WIN_SIZE.width,100));
		addChild(containerLayer);
        
        CCSprite *tMonster=CCSprite::createWithSpriteFrameName("Grid_cell_monster.png");
        CC_BREAK_IF(!tMonster);
        tMonster->setPosition(ccp(WIN_SIZE.width/3+tMonster->getContentSize().width,containerLayer->getContentSize().height-tMonster->getContentSize().height));
        containerLayer->addChild(tMonster);
        
        CCSprite *tShield=CCSprite::createWithSpriteFrameName("Grid_cell_shield.png");
        CC_BREAK_IF(!tShield);
        tShield->setPosition(ccp(WIN_SIZE.width/3+WIN_SIZE.width/9+tShield->getContentSize().width,containerLayer->getContentSize().height-tShield->getContentSize().height));
        containerLayer->addChild(tShield);
        
        CCSprite *tSword=CCSprite::createWithSpriteFrameName("Grid_cell_sword.png");
        CC_BREAK_IF(!tSword);
        tSword->setPosition(ccp(WIN_SIZE.width/3+2*WIN_SIZE.width/9+tSword->getContentSize().width,containerLayer->getContentSize().height-tSword->getContentSize().height));
        containerLayer->addChild(tSword);
        
        PlayerProperty player=((MainGameController *)m_delegate)->getPlayerProperty();
        CCString *baseAttachValue=CCString::createWithFormat("+%d",player.mBasicDamage);
        CCLabelTTF *tBaseAttackValueTTF = CCLabelTTF::create(baseAttachValue->getCString(),"Marker Felt",24);
        CC_BREAK_IF(!tBaseAttackValueTTF);
        tBaseAttackValueTTF->setAnchorPoint(ccp(0.5,0.5));
        tBaseAttackValueTTF->setColor(ccc3(0,0,255));
        tBaseAttackValueTTF->setPosition(ccp(tMonster->getPosition().x,tMonster->getPosition().y-tMonster->getContentSize().height));
        containerLayer->addChild(tBaseAttackValueTTF);
        
        int maxShieldValue=player.mMaxShield;
        int curShieldValue=player.mMaxShield;
        CCString *shieldValue=CCString::createWithFormat("%d/%d",curShieldValue,maxShieldValue);
        CCLabelTTF *m_shiledValueTTF = CCLabelTTF::create(shieldValue->getCString(),"Marker Felt",24);
        CC_BREAK_IF(!m_shiledValueTTF);
        m_shiledValueTTF->setTag(STATUS_SHIELD_TAG);
        m_shiledValueTTF->setAnchorPoint(ccp(0.5,0.5));
        m_shiledValueTTF->setColor(ccc3(0,0,255));
        m_shiledValueTTF->setPosition(ccp(tShield->getPosition().x,tShield->getPosition().y-tShield->getContentSize().height));
        containerLayer->addChild(m_shiledValueTTF);
        
        int damageValue=player.mWeaponDamage;
        CCString *equitAttachValue=CCString::createWithFormat("+%d",damageValue);
        CCLabelTTF *tEquipDamageValueTTF = CCLabelTTF::create(equitAttachValue->getCString(),"Marker Felt",24);
        CC_BREAK_IF(!tEquipDamageValueTTF);
        tEquipDamageValueTTF->setAnchorPoint(ccp(0.5,0.5));
        tEquipDamageValueTTF->setColor(ccc3(0,0,255));
        tEquipDamageValueTTF->setPosition(ccp(tSword->getPosition().x,tSword->getPosition().y-tSword->getContentSize().height));
        containerLayer->addChild(tEquipDamageValueTTF);
        
        float tScaleX=1;
        //portion
        CCSprite *m_portionObit=CCSprite::createWithSpriteFrameName("GR_progress_obit.png");
        CC_BREAK_IF(!m_portionObit);
        m_portionObit->setTag(STATUS_PORTION_OBIT_TAG);
        if (m_portionObit->getContentSize().width/(containerLayer->getContentSize().width/3)>1) {
            tScaleX=(containerLayer->getContentSize().width/3)/m_portionObit->getContentSize().width;
        }
        m_portionObit->setPosition(ccp(15+m_portionObit->getContentSize().width/2,containerLayer->getContentSize().height-m_portionObit->getContentSize().height-15));
        m_portionObit->setScaleX(tScaleX);
        containerLayer->addChild(m_portionObit);
        
        CCProgressTimer *m_portionProgress=CCProgressTimer::create(CCSprite::createWithSpriteFrameName("GR_progress_timer.png"));
        CC_BREAK_IF(!m_portionProgress);
        m_portionProgress->setTag(STATUS_PORTION_TAG);
        m_portionProgress->setType(kCCProgressTimerTypeBar);
        m_portionProgress->setBarChangeRate(ccp(1, 0));
        m_portionProgress->setPercentage(100);
        m_portionProgress->setAnchorPoint(ccp(0,0.5));
        m_portionProgress->setScaleX(tScaleX);
        m_portionProgress->setPosition(ccp(m_portionObit->getPosition().x-m_portionObit->getContentSize().width/2-(m_portionObit->getContentSize().width-m_portionProgress->getContentSize().width*m_portionProgress->getPercentage()/100)/2,m_portionObit->getPosition().y));
        containerLayer->addChild(m_portionProgress);
        
        //coin
        CCSprite *m_coinObit=CCSprite::createWithSpriteFrameName("GR_progress_obit.png");
        CC_BREAK_IF(!m_coinObit);
        m_coinObit->setTag(STATUS_COIN_OBIT_TAG);
        m_coinObit->setScaleX(tScaleX);
        m_coinObit->setPosition(ccp(15+m_coinObit->getContentSize().width/2,containerLayer->getContentSize().height-2*m_coinObit->getContentSize().height-35));
        containerLayer->addChild(m_coinObit);
        
        CCProgressTimer *m_coinProgress=CCProgressTimer::create(CCSprite::createWithSpriteFrameName("GR_progress_timer.png"));
        CC_BREAK_IF(!m_coinProgress);
        m_coinProgress->setTag(STATUS_COIN_TAG);
        m_coinProgress->setType(kCCProgressTimerTypeBar);
        m_coinProgress->setBarChangeRate(ccp(1, 0));
        m_coinProgress->setPercentage(0);
        m_coinProgress->setAnchorPoint(ccp(0,0.5));
        m_coinProgress->setScaleX(tScaleX);
        m_coinProgress->setPosition(ccp(m_coinObit->getPosition().x-m_coinObit->getContentSize().width/2-(m_coinObit->getContentSize().width-m_coinProgress->getContentSize().width*m_coinProgress->getPercentage()/100)/2,m_coinObit->getPosition().y));
        containerLayer->addChild(m_coinProgress);
        
        //kill monster
        CCSprite *m_killMonsterObit=CCSprite::createWithSpriteFrameName("GR_progress_obit.png");
        CC_BREAK_IF(!m_killMonsterObit);
        m_killMonsterObit->setTag(STATUS_KILLMONSTER_OBIT_TAG);
        m_killMonsterObit->setScaleX(tScaleX);
        m_killMonsterObit->setPosition(ccp(2*containerLayer->getContentSize().width/3+20+m_killMonsterObit->getContentSize().width/2,containerLayer->getContentSize().height-m_killMonsterObit->getContentSize().height-15));
        containerLayer->addChild(m_killMonsterObit);
        
        CCProgressTimer *m_killMonsterProgress=CCProgressTimer::create(CCSprite::createWithSpriteFrameName("GR_progress_timer.png"));
        CC_BREAK_IF(!m_killMonsterProgress);
        m_killMonsterProgress->setTag(STATUS_KILLMONSTER_TAG);
        m_killMonsterProgress->setType(kCCProgressTimerTypeBar);
        m_killMonsterProgress->setBarChangeRate(ccp(1, 0));
        m_killMonsterProgress->setPercentage(0);
        m_killMonsterProgress->setAnchorPoint(ccp(0,0.5));
        m_killMonsterProgress->setScaleX(tScaleX);
        m_killMonsterProgress->setPosition(ccp(m_killMonsterObit->getPosition().x-m_killMonsterObit->getContentSize().width/2-(m_killMonsterObit->getContentSize().width-m_killMonsterProgress->getContentSize().width*m_killMonsterProgress->getPercentage()/100)/2,m_killMonsterObit->getPosition().y));
        containerLayer->addChild(m_killMonsterProgress);
        
        //score
        CCSprite *m_scoreObit=CCSprite::createWithSpriteFrameName("GR_progress_obit.png");
        CC_BREAK_IF(!m_scoreObit);
        m_scoreObit->setTag(STATUS_SCORE_OBIT_TAG);
        m_scoreObit->setScaleX(tScaleX);
        m_scoreObit->setPosition(ccp(2*containerLayer->getContentSize().width/3+20+m_scoreObit->getContentSize().width/2,containerLayer->getContentSize().height-2*m_scoreObit->getContentSize().height-35));
        containerLayer->addChild(m_scoreObit);
        
        CCProgressTimer *m_scoreProgress=CCProgressTimer::create(CCSprite::createWithSpriteFrameName("GR_progress_timer.png"));
        CC_BREAK_IF(!m_scoreProgress);
        m_scoreProgress->setTag(STATUS_SCORE_TAG);
        m_scoreProgress->setType(kCCProgressTimerTypeBar);
        m_scoreProgress->setBarChangeRate(ccp(1, 0));
        m_scoreProgress->setPercentage(0);
        m_scoreProgress->setAnchorPoint(ccp(0,0.5));
        m_scoreProgress->setScaleX(tScaleX);
        m_scoreProgress->setPosition(ccp(m_scoreObit->getPosition().x-m_scoreObit->getContentSize().width/2-(m_scoreObit->getContentSize().width-m_scoreProgress->getContentSize().width*m_scoreProgress->getPercentage()/100)/2,m_scoreObit->getPosition().y));
        containerLayer->addChild(m_scoreProgress);
		
	}while(0);
}

void MainGameStatusBar::setPortionProgress(int pValue)
{
    do {
        CCLayer *containerLayer=(CCLayerColor *)(this->getChildByTag(STATUS_CONTAINER_TAG));
        CCLog("%s-------%p",__FUNCTION__,containerLayer);
        CC_BREAK_IF(!containerLayer);
        CCProgressTimer *progress=dynamic_cast<CCProgressTimer *>(containerLayer->getChildByTag(STATUS_PORTION_TAG));
        CC_BREAK_IF(!progress);
        CCSprite *obit=dynamic_cast<CCSprite *>(containerLayer->getChildByTag(STATUS_PORTION_OBIT_TAG));
        CC_BREAK_IF(!obit);
        progress->setPercentage(pValue>100?100:pValue);
        progress->setPosition(ccp(obit->getPosition().x-obit->getContentSize().width/2-(obit->getContentSize().width-progress->getContentSize().width*progress->getPercentage()/100)/2,obit->getPosition().y));
    } while (0);
}

float MainGameStatusBar::getPortionProgress()
{
    float tProgress=0;
    do {
        CCLayer *containerLayer=dynamic_cast<CCLayer *>(this->getChildByTag(STATUS_CONTAINER_TAG));
        CC_BREAK_IF(!containerLayer);
        CCProgressTimer *progress=dynamic_cast<CCProgressTimer *>(containerLayer->getChildByTag(STATUS_PORTION_TAG));
        CC_BREAK_IF(!progress);
        tProgress=progress->getPercentage();
    } while (0);
    
    return tProgress;
}

void MainGameStatusBar::setCoinProgress(int pValue)
{
    do {
        CCLayer *containerLayer=dynamic_cast<CCLayer *>(this->getChildByTag(STATUS_CONTAINER_TAG));
        CC_BREAK_IF(!containerLayer);
        CCProgressTimer *progress=dynamic_cast<CCProgressTimer *>(containerLayer->getChildByTag(STATUS_COIN_TAG));
        CC_BREAK_IF(!progress);
        CCSprite *obit=dynamic_cast<CCSprite *>(containerLayer->getChildByTag(STATUS_COIN_OBIT_TAG));
        CC_BREAK_IF(!obit);
        progress->setPercentage(pValue>100?100:pValue);
        progress->setPosition(ccp(obit->getPosition().x-obit->getContentSize().width/2-(obit->getContentSize().width-progress->getContentSize().width*progress->getPercentage()/100)/2,obit->getPosition().y));
    } while (0);
}

float MainGameStatusBar::getCoinProgress()
{
    float tProgress=0;
    do {
        CCLayer *containerLayer=dynamic_cast<CCLayer *>(this->getChildByTag(STATUS_CONTAINER_TAG));
        CC_BREAK_IF(!containerLayer);
        CCProgressTimer *progress=dynamic_cast<CCProgressTimer *>(containerLayer->getChildByTag(STATUS_COIN_TAG));
        CC_BREAK_IF(!progress);
        tProgress=progress->getPercentage();
    } while (0);
    
    return tProgress;
}

void MainGameStatusBar::setKillMonsterProgress(int pValue)
{
    do {
        CCLayer *containerLayer=dynamic_cast<CCLayer *>(this->getChildByTag(STATUS_CONTAINER_TAG));
        CC_BREAK_IF(!containerLayer);
        CCProgressTimer *progress=dynamic_cast<CCProgressTimer *>(containerLayer->getChildByTag(STATUS_KILLMONSTER_TAG));
        CC_BREAK_IF(!progress);
        CCSprite *obit=dynamic_cast<CCSprite *>(containerLayer->getChildByTag(STATUS_KILLMONSTER_OBIT_TAG));
        CC_BREAK_IF(!obit);
        progress->setPercentage(pValue>100?100:pValue);
        progress->setPosition(ccp(obit->getPosition().x-obit->getContentSize().width/2-(obit->getContentSize().width-progress->getContentSize().width*progress->getPercentage()/100)/2,obit->getPosition().y));
    } while (0);
}

float MainGameStatusBar::getKillMonsterProgress()
{
    float tProgress=0;
    do {
        CCLayer *containerLayer=dynamic_cast<CCLayer *>(this->getChildByTag(STATUS_CONTAINER_TAG));
        CC_BREAK_IF(!containerLayer);
        CCProgressTimer *progress=dynamic_cast<CCProgressTimer *>(containerLayer->getChildByTag(STATUS_KILLMONSTER_TAG));
        CC_BREAK_IF(!progress);
        tProgress=progress->getPercentage();
    } while (0);
    
    return tProgress;
}

void MainGameStatusBar::setScoreProgress(int pValue)
{
    do {
        CCLayer *containerLayer=dynamic_cast<CCLayer *>(this->getChildByTag(STATUS_CONTAINER_TAG));
        CC_BREAK_IF(!containerLayer);
        CCProgressTimer *progress=dynamic_cast<CCProgressTimer *>(containerLayer->getChildByTag(STATUS_SCORE_TAG));
        CC_BREAK_IF(!progress);
        CCSprite *obit=dynamic_cast<CCSprite *>(containerLayer->getChildByTag(STATUS_SCORE_OBIT_TAG));
        CC_BREAK_IF(!obit);
        progress->setPercentage(pValue>100?100:pValue);
        progress->setPosition(ccp(obit->getPosition().x-obit->getContentSize().width/2-(obit->getContentSize().width-progress->getContentSize().width*progress->getPercentage()/100)/2,obit->getPosition().y));
    } while (0);
}

float MainGameStatusBar::getScoreProgress()
{
    float tProgress=0;
    do {
        CCLayer *containerLayer=dynamic_cast<CCLayer *>(this->getChildByTag(STATUS_CONTAINER_TAG));
        CC_BREAK_IF(!containerLayer);
        CCProgressTimer *progress=dynamic_cast<CCProgressTimer *>(containerLayer->getChildByTag(STATUS_SCORE_TAG));
        CC_BREAK_IF(!progress);
        tProgress=progress->getPercentage();
    } while (0);
    
    return tProgress;
}

void MainGameStatusBar::setShieldValue(int curValue,int maxValue)
{
    do {
        CCLog("%s:curValue=%d",__FUNCTION__,curValue);
        CCLayer *containerLayer=(CCLayerColor *)(this->getChildByTag(STATUS_CONTAINER_TAG));
        CCLog("%s-------%p",__FUNCTION__,containerLayer);
        CC_BREAK_IF(!containerLayer);
        CCLabelTTF *label=(CCLabelTTF *)(containerLayer->getChildByTag(STATUS_SHIELD_TAG));
        CC_BREAK_IF(!label);
        CCString *shieldValue=CCString::createWithFormat("%d/%d",curValue,maxValue);
        label->setString(shieldValue->getCString());
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
