#include "MainGameStatusBar.h"
#include "MainGameController.h"

#define STATUS_CONTAINER_TAG        50
#define STATUS_PORTION_TAG          100
#define STATUS_COIN_TAG             101
#define STATUS_KILLMONSTER_TAG      102
#define STATUS_SCORE_TAG            103
#define STATUS_SHIELD_TAG           105
#define STATUS_ROUND_TAG            106
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
        containerLayer->setPosition(ccp(0,WIN_SIZE.height-100));
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
        
        //round count
        CCString *roundValue=CCString::createWithFormat("round:%d",0);
        CCLabelTTF *RoundValueTTF = CCLabelTTF::create(roundValue->getCString(),"Marker Felt",24);
        CC_BREAK_IF(!RoundValueTTF);
        RoundValueTTF->setTag(STATUS_ROUND_TAG);
        RoundValueTTF->setAnchorPoint(ccp(0.5,0.5));
        RoundValueTTF->setColor(ccc3(0,0,255));
        RoundValueTTF->setPosition(ccp(m_shiledValueTTF->getPosition().x,m_shiledValueTTF->getPosition().y-m_shiledValueTTF->getContentSize().height));
        containerLayer->addChild(RoundValueTTF);
        
        //portion
        CCString *portionValue=CCString::createWithFormat("portion:%d",player.mMaxHealth);
        CCLabelTTF *portionValueTTF = CCLabelTTF::create(portionValue->getCString(),"Marker Felt",24);
        CC_BREAK_IF(!portionValueTTF);
        portionValueTTF->setAnchorPoint(CCPointZero);
        portionValueTTF->setTag(STATUS_PORTION_TAG);
        portionValueTTF->setColor(ccc3(0,0,255));
        portionValueTTF->setPosition(ccp(75,containerLayer->getContentSize().height-30));
        containerLayer->addChild(portionValueTTF);
        
        //coin
        CCString *coinValue=CCString::createWithFormat("coin:%d",0);
        CCLabelTTF *coinValueTTF = CCLabelTTF::create(coinValue->getCString(),"Marker Felt",24);
        CC_BREAK_IF(!coinValueTTF);
        coinValueTTF->setAnchorPoint(CCPointZero);
        coinValueTTF->setTag(STATUS_COIN_TAG);
        coinValueTTF->setColor(ccc3(0,0,255));
        coinValueTTF->setPosition(ccp(75,containerLayer->getContentSize().height-70));
        containerLayer->addChild(coinValueTTF);
        
        //kill monster
        CCString *killMonsterValue=CCString::createWithFormat("kill:%d",0);
        CCLabelTTF *killMonsterValueTTF = CCLabelTTF::create(killMonsterValue->getCString(),"Marker Felt",24);
        CC_BREAK_IF(!killMonsterValueTTF);
        killMonsterValueTTF->setAnchorPoint(CCPointZero);
        killMonsterValueTTF->setTag(STATUS_KILLMONSTER_TAG);
        killMonsterValueTTF->setColor(ccc3(0,0,255));
        killMonsterValueTTF->setPosition(ccp(containerLayer->getContentSize().width*2/3+30,containerLayer->getContentSize().height-30));
        containerLayer->addChild(killMonsterValueTTF);
        
        //score
        CCString *scoreValue=CCString::createWithFormat("score:%d",0);
        CCLabelTTF *scoreValueTTF = CCLabelTTF::create(scoreValue->getCString(),"Marker Felt",24);
        CC_BREAK_IF(!scoreValueTTF);
        scoreValueTTF->setAnchorPoint(CCPointZero);
        scoreValueTTF->setTag(STATUS_SCORE_TAG);
        scoreValueTTF->setColor(ccc3(0,0,255));
        scoreValueTTF->setPosition(ccp(containerLayer->getContentSize().width*2/3+30,containerLayer->getContentSize().height-70));
        containerLayer->addChild(scoreValueTTF);
        
	}while(0);
}

void MainGameStatusBar::setPortionProgress(int pValue)
{
    do {
        CCLayer *containerLayer=(CCLayerColor *)(this->getChildByTag(STATUS_CONTAINER_TAG));
        CC_BREAK_IF(!containerLayer);
        CCLabelTTF *progress=dynamic_cast<CCLabelTTF *>(containerLayer->getChildByTag(STATUS_PORTION_TAG));
        CC_BREAK_IF(!progress);
        CCString *portionValue=CCString::createWithFormat("portion:%d",pValue);
        CC_BREAK_IF(!portionValue);
        progress->setString(portionValue->getCString());
    } while (0);
}

float MainGameStatusBar::getPortionProgress()
{
    float tProgress=0;
    do {
        
    } while (0);
    
    return tProgress;
}

void MainGameStatusBar::setCoinProgress(int pValue)
{
    do {
        CCLayer *containerLayer=dynamic_cast<CCLayer *>(this->getChildByTag(STATUS_CONTAINER_TAG));
        CC_BREAK_IF(!containerLayer);
        CCLabelTTF *progress=dynamic_cast<CCLabelTTF *>(containerLayer->getChildByTag(STATUS_COIN_TAG));
        CC_BREAK_IF(!progress);
        CCString *coinValue=CCString::createWithFormat("coin:%d",pValue);
        CC_BREAK_IF(!coinValue);
        progress->setString(coinValue->getCString());
    } while (0);
}

float MainGameStatusBar::getCoinProgress()
{
    float tProgress=0;
    do {
        
    } while (0);
    
    return tProgress;
}

void MainGameStatusBar::setKillMonsterProgress(int pValue)
{
    do {
        CCLayer *containerLayer=dynamic_cast<CCLayer *>(this->getChildByTag(STATUS_CONTAINER_TAG));
        CC_BREAK_IF(!containerLayer);
        CCLabelTTF *progress=dynamic_cast<CCLabelTTF *>(containerLayer->getChildByTag(STATUS_KILLMONSTER_TAG));
        CC_BREAK_IF(!progress);
        CCString *killValue=CCString::createWithFormat("kill:%d",pValue);
        CC_BREAK_IF(!killValue);
        progress->setString(killValue->getCString());
    } while (0);
}

float MainGameStatusBar::getKillMonsterProgress()
{
    float tProgress=0;
    do {
        
    } while (0);
    
    return tProgress;
}

void MainGameStatusBar::setScoreProgress(int pValue)
{
    do {
        CCLayer *containerLayer=dynamic_cast<CCLayer *>(this->getChildByTag(STATUS_CONTAINER_TAG));
        CC_BREAK_IF(!containerLayer);
        CCLabelTTF *progress=dynamic_cast<CCLabelTTF *>(containerLayer->getChildByTag(STATUS_SCORE_TAG));
        CC_BREAK_IF(!progress);
        CCString *scoreValue=CCString::createWithFormat("score:%d",pValue);
        CC_BREAK_IF(!scoreValue);
        progress->setString(scoreValue->getCString());
    } while (0);
}

float MainGameStatusBar::getScoreProgress()
{
    float tProgress=0;
    do {
        
    } while (0);
    
    return tProgress;
}

void MainGameStatusBar::setShieldValue(int curValue,int maxValue)
{
    do {
        CCLayer *containerLayer=(CCLayerColor *)(this->getChildByTag(STATUS_CONTAINER_TAG));
        CC_BREAK_IF(!containerLayer);
        CCLabelTTF *label=(CCLabelTTF *)(containerLayer->getChildByTag(STATUS_SHIELD_TAG));
        CC_BREAK_IF(!label);
        CCString *shieldValue=CCString::createWithFormat("%d/%d",curValue,maxValue);
        label->setString(shieldValue->getCString());
    } while (0);
}

void MainGameStatusBar::setRoundValue(int pValue)
{
    do {
        CCLayer *containerLayer=(CCLayerColor *)(this->getChildByTag(STATUS_CONTAINER_TAG));
        CC_BREAK_IF(!containerLayer);
        CCLabelTTF *label=(CCLabelTTF *)(containerLayer->getChildByTag(STATUS_ROUND_TAG));
        CC_BREAK_IF(!label);
        CCString *roundValue=CCString::createWithFormat("round:%d",pValue);
        label->setString(roundValue->getCString());
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
