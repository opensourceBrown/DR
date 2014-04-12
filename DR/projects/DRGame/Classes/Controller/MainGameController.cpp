/****************************************************************************
//√ï¬Æ‚Äù‚àö¬†Àù√¶‚Ä∫∆í¬£‚Äì√ï¬ø‚Ä°
****************************************************************************/
#include "MainGameController.h"
#include "MainGameScene.h"
#include "MainGameGridLayer.h"
#include "GridCell.h"
#include "DataMangager.h"
#include "DRUserDefault.h"
#include "MainGameStatusBar.h"
#include "WeaponConfigure.h"
#include "WeaponController.h"
#include "MainGameToolBar.h"

MainGameController::MainGameController():
    mMagicInStage(NULL),
    mStageConnectedElements(NULL),
    mCurShield(0),
    mCurPortion(0),
    mCurStageKillMonster(0),
    mCurStageCoin(0),
    mCurStageScore(0),
    mSpiky(false),
    mMageEnable(true),
    mMagicTriggerTip(false),
    mCurrentSpikyCount(0),
    mRunGoldenBossContainer(NULL)
{
    mMagic.init();
    mPlayerProperty.init();
}

MainGameController::~MainGameController()
{
    CC_SAFE_RELEASE(mMagicInStage);
    CC_SAFE_RELEASE(mStageConnectedElements);
    CC_SAFE_RELEASE(m_scene);
}

MainGameController *MainGameController::create()
{
    MainGameController *controller=new MainGameController();
    do {
        CC_BREAK_IF(!controller || !(controller->initWith()));
        //controller->autorelease();
        return controller;
    } while (0);
    
    CC_SAFE_DELETE(controller);
    return NULL;
}

bool MainGameController::initWith()
{
    LOG_TRACE
    bool tRet=false;
    do {
        readPlayerProperty();
        
        //TO:DO initialization
        mMagicInStage=CCArray::create();
        CC_BREAK_IF(!mMagicInStage);
        mMagicInStage->retain();
        
        mStageConnectedElements=CCArray::create();
        CC_BREAK_IF(!mStageConnectedElements);
        mStageConnectedElements->retain();
        
        mGridPropertyContainer=CCArray::createWithCapacity(GRID_VOLUME*GRID_ROW);
        CC_BREAK_IF(!mGridPropertyContainer);
        mGridPropertyContainer->retain();
        
        m_scene=MainGameScene::create(this);
        CC_BREAK_IF(!m_scene);
        m_scene->retain();
        
        mCurShield=mPlayerProperty.mMaxShield;
        mCurPortion=mPlayerProperty.mMaxHealth;
        
        updateStatusData();
        
        tRet=true;
    } while (0);
    
    return tRet;
}

void MainGameController::readPlayerProperty()
{
    mPlayerProperty.init();
}

void MainGameController::updateStatusData()
{
    do {
        MainGameStatusBar *statusBar = ((MainGameScene *)m_scene)->getStatusLayer();
        CC_BREAK_IF(!statusBar);
        statusBar->setShieldValue(mCurShield,mPlayerProperty.mMaxShield);
        statusBar->setPortionProgress(mCurPortion);
        statusBar->setKillMonsterProgress(mCurStageKillMonster);
        statusBar->setCoinProgress(mCurStageCoin);
        statusBar->setRoundValue(mCurStageRound);
        statusBar->setScoreProgress(mCurStageScore);
    } while (0);
}

void MainGameController::cleanAnimationCompeleteCallback()
{
    triggerBossSkill();
    triggerMagicAfterCleanAnimation();
}

void MainGameController::refreshWeapon()
{
    
}

void MainGameController::selectMagic(MagicType pID)
{
    if (mMagic.mMagicType!=pID) {
        mMagic.mMagicType=pID;
        mMagic.mID=pID;
        switch (pID) {
            case kMagicType_Steal:
                mMagic.mCDTime=18;
                break;
            case kMagicType_Fireball:
                mMagic.mCDTime=19;
                break;
            case kMagicType_CounterAttack:
                mMagic.mCDTime=23;
                break;
            case kMagicType_GoldenTouch:
                mMagic.mCDTime=20;
                break;
            case kMagicType_BoostHealth:
                mMagic.mCDTime=20;
                break;
            case kMagicType_Scavenge:
                mMagic.mCDTime=20;
                break;
            case kMagicType_Shatter:
                mMagic.mCDTime=23;
                break;
            case kMagicType_BoostGold:
                mMagic.mCDTime=25;
                break;
            case kMagicType_Teleport:
                mMagic.mCDTime=25;
                break;
            case kMagicType_Heal:
                mMagic.mCDTime=20;
                break;
            default:
                break;
        }
        
        MainGameToolBar *toolBar=((MainGameScene *)m_scene)->getToolBar();
        if (toolBar) {
            toolBar->refreshMagicCD(mMagic.mCDTime);
        }
    }
}

bool MainGameController::judgeIsTriggerMagic(CCArray *pArray)
{
    bool tRet=false;
    if (mMageEnable) {
        return tRet;
    }
    switch (mMagic.mMagicType) {
        case kMagicType_Steal:{     //get 1 coin per monster every round
            CC_BREAK_IF(mMagic.mCDTime>0);
            do {
                CC_BREAK_IF(!pArray || pArray->count()<=0);
                for (int i=0; i<pArray->count(); i++) {
                    GridCell *cell=dynamic_cast<GridCell *>(pArray->objectAtIndex(i));
                    CC_BREAK_IF(!cell);
                    
                    GridElementProperty *block=cell->getCellProperty();
                    CC_BREAK_IF(!block);
                    if (block->mType==kElementType_Monster){
                        tRet=true;
                        mMagic.mCDTime=18;
                        break;
                    }
                }
            } while (0);
            break;
        }
        case kMagicType_Fireball:
        case kMagicType_CounterAttack:
        case kMagicType_GoldenTouch:
        case kMagicType_BoostHealth:
        case kMagicType_Scavenge:
        case kMagicType_Shatter:
        case kMagicType_BoostGold:
        case kMagicType_Teleport:
        case kMagicType_Heal:{
            do {
                if (mMagic.mCDTime==0) {
                    tRet=true;
                }
            } while (0);
            break;
        }
        default:
            break;
    }
    mMagicTriggerTip=tRet;
    return tRet;
}

bool MainGameController::judgeIsEnableMagic()
{
    bool tRet=true;
    do {
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        
        for (int i=0; i<GRID_ROW; i++) {
            for (int j=0; j<GRID_VOLUME; j++) {
                GridCell *cell=gridLayer->getGridCell(i, j);
                CC_BREAK_IF(!cell);
                GridElementProperty *block=cell->getCellProperty();
                CC_BREAK_IF(!block);
                if (block->mType==kElementType_Monster && block->mMonsterProperty.mSkillType==kBossBustyType_Mage && block->mMonsterProperty.mLife>0) {
                    tRet=false;
                    break;
                }
            }
        }
    } while (0);
    
    return tRet;
}

void MainGameController::triggerMagic(MagicType pID,CCArray *pArray)
{
    do {
        bool hasMageBoss=(judgeIsEnableMagic()==false);
//        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
//        CC_BREAK_IF(!gridLayer);
//        
//        for (int i=0; i<GRID_ROW; i++) {
//            for (int j=0; j<GRID_VOLUME; j++) {
//                GridCell *cell=gridLayer->getGridCell(i, j);
//                CC_BREAK_IF(!cell);
//                GridElementProperty *block=cell->getCellProperty();
//                CC_BREAK_IF(!block);
//                if (block->mType==kElementType_Monster && block->mMonsterProperty.mSkillType==kBossBustyType_Mage && block->mMonsterProperty.mLife>0) {
//                    hasMageBoss=true;
//                    break;
//                }
//            }
//        }
        
        switch (pID) {
            case kMagicType_Steal:{     //get 1 coin per monster every round
                if (!hasMageBoss) {
                    do {
                        CC_BREAK_IF(!pArray || pArray->count()<=0);
                        for (int i=0; i<pArray->count(); i++) {
                            GridCell *cell=dynamic_cast<GridCell *>(pArray->objectAtIndex(i));
                            CC_BREAK_IF(!cell);
                            
                            GridElementProperty *block=cell->getCellProperty();
                            CC_BREAK_IF(!block);
                            if (block->mType==kElementType_Monster){
                                DRUserDefault::sharedUserDefault()->setCoin(DRUserDefault::sharedUserDefault()->getCoin()+1);
                                mCurStageCoin++;
                            }
                        }
                    } while (0);
                    
                    triggerMagicAnimation(kMagicType_Steal);
                }
                
                mMagic.mCDTime=18;
                mMagicTriggerTip=false;
                break;
            }
            case kMagicType_Fireball:{
                if (!hasMageBoss) {
                    do {
                        //随机消去一个3*3的block
                        CC_BREAK_IF(!pArray);
                        
                        int randomIndex = 0;
                        do {
                            randomIndex = arc4random()%(GRID_ROW*GRID_VOLUME);
                        } while ((randomIndex/GRID_VOLUME!=0) && (randomIndex/GRID_VOLUME!=GRID_ROW-1) && (randomIndex%GRID_VOLUME!=0) && (randomIndex%GRID_VOLUME!=GRID_VOLUME-1));
                        
                        insertCellIntoConnectedArray(randomIndex/GRID_VOLUME, randomIndex%GRID_VOLUME);
                        insertCellIntoConnectedArray(randomIndex/GRID_VOLUME-1, randomIndex%GRID_VOLUME-1);
                        insertCellIntoConnectedArray(randomIndex/GRID_VOLUME-1, randomIndex%GRID_VOLUME);
                        insertCellIntoConnectedArray(randomIndex/GRID_VOLUME-1, randomIndex%GRID_VOLUME+1);
                        insertCellIntoConnectedArray(randomIndex/GRID_VOLUME, randomIndex%GRID_VOLUME-1);
                        insertCellIntoConnectedArray(randomIndex/GRID_VOLUME, randomIndex%GRID_VOLUME+1);
                        insertCellIntoConnectedArray(randomIndex/GRID_VOLUME+1, randomIndex%GRID_VOLUME-1);
                        insertCellIntoConnectedArray(randomIndex/GRID_VOLUME+1, randomIndex%GRID_VOLUME);
                        insertCellIntoConnectedArray(randomIndex/GRID_VOLUME+1, randomIndex%GRID_VOLUME+1);
                        
                        for (int i=0; i<pArray->count(); i++) {
                            GridCell *item=dynamic_cast<GridCell *>(pArray->objectAtIndex(i));
                            CC_BREAK_IF(!item);
                            GridElementProperty *block=item->getCellProperty();
                            CC_BREAK_IF(!block);
                            if (block->mType==kElementType_Coin) {
                                DRUserDefault::sharedUserDefault()->setCoin(DRUserDefault::sharedUserDefault()->getCoin()+1);
                                mCurStageCoin++;
                            }else if (block->mType==kElementType_Potion){
                                mCurPortion++;
                                if (mCurPortion>mPlayerProperty.mMaxHealth) {
                                    mCurPortion=mPlayerProperty.mMaxHealth;
                                }
                            }else if (block->mType==kElementType_Shield){
                                mCurShield++;
                                if (mCurShield>mPlayerProperty.mMaxShield) {
                                    mCurShield=mPlayerProperty.mMaxShield;
                                }
                            }else if (block->mType==kElementType_Monster){
                                DRUserDefault::sharedUserDefault()->setKillMonsterCount(DRUserDefault::sharedUserDefault()->getKillMonsterCount()+1);
                                mCurStageKillMonster++;
                                
                                if (block->mMonsterProperty.mType==kBustyType_Common) {
                                    DRUserDefault::sharedUserDefault()->setScore(DRUserDefault::sharedUserDefault()->getScore()+1);
                                    mCurStageScore++;
                                }else{
                                    DRUserDefault::sharedUserDefault()->setScore(DRUserDefault::sharedUserDefault()->getScore()+1);
                                    mCurStageScore++;
                                }
                            }
                        }
                        cleanAndRefreshGrid();
                        updateStatusData();
                        triggerMagicAnimation(kMagicType_Fireball);
                    } while (0);
                }
                mMagic.mCDTime=19;
                mMagicTriggerTip=false;
                break;
            }
            case kMagicType_CounterAttack:{
                //monster attack itself
                mMagic.mCDTime=23;
                break;
            }
            case kMagicType_BoostHealth:{
                if (!hasMageBoss) {
                    do{
                        for (int i=0; i<pArray->count(); i++) {
                            GridCell *item=dynamic_cast<GridCell *>(pArray->objectAtIndex(i));
                            CC_BREAK_IF(!item);
                            GridElementProperty *block=item->getCellProperty();
                            CC_BREAK_IF(!block);
                            if (block->mType==kElementType_Potion){
                                mCurPortion++;
                                if (mCurPortion>mPlayerProperty.mMaxHealth) {
                                    mCurPortion=mPlayerProperty.mMaxHealth;
                                }
                            }
                        }
                        updateStatusData();
                        triggerMagicAnimation(kMagicType_BoostHealth);
                    } while (0);
                }
                mMagic.mCDTime=20;
                mMagicTriggerTip=false;
                break;
            }
            case kMagicType_BoostGold:{
                if (!hasMageBoss) {
                    do{
                        for (int i=0; i<pArray->count(); i++) {
                            GridCell *item=dynamic_cast<GridCell *>(pArray->objectAtIndex(i));
                            CC_BREAK_IF(!item);
                            GridElementProperty *block=item->getCellProperty();
                            CC_BREAK_IF(!block);
                            if (block->mType==kElementType_Coin) {
                                DRUserDefault::sharedUserDefault()->setCoin(DRUserDefault::sharedUserDefault()->getCoin()+1);
                                mCurStageCoin++;
                            }
                        }
                        updateStatusData();
                        triggerMagicAnimation(kMagicType_BoostGold);
                    } while (0);
                }

                mMagic.mCDTime=25;
                mMagicTriggerTip=false;
                break;
            }
            default:
                break;
        }
    } while (0);
}

void MainGameController::triggerMagicAfterCleanAnimation()
{
    do {
        CC_BREAK_IF(mMagic.mID<=0 || mMagic.mCDTime>0);
        bool hasMageBoss=(judgeIsEnableMagic()==false);;
//        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
//        CC_BREAK_IF(!gridLayer);
//        
//        for (int i=0; i<GRID_ROW; i++) {
//            for (int j=0; j<GRID_VOLUME; j++) {
//                GridCell *cell=gridLayer->getGridCell(i, j);
//                CC_BREAK_IF(!cell);
//                GridElementProperty *block=cell->getCellProperty();
//                CC_BREAK_IF(!block);
//                if (block->mType==kElementType_Monster && block->mMonsterProperty.mSkillType==kBossBustyType_Mage && block->mMonsterProperty.mLife>0) {
//                    hasMageBoss=true;
//                    break;
//                }
//            }
//        }
        
        switch (mMagic.mID) {
            case kMagicType_GoldenTouch:{
                //change sword to gold coin which is not in mStageConnectedElements
                if (!hasMageBoss) {
                    do {
                        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
                        CC_BREAK_IF(!gridLayer);
                        
                        for (int i=0; i<GRID_ROW; i++) {
                            for (int j=0; j<GRID_VOLUME; j++) {
                                GridCell *cell=gridLayer->getGridCell(i, j);
                                CC_BREAK_IF(!cell);
                                GridElementProperty *block=cell->getCellProperty();
                                CC_BREAK_IF(!block);
                                if (block->mType==kElementType_Sword) {
                                    block->mType=kElementType_Coin;
                                }
                                GridElementProperty *eleBlock=dynamic_cast<GridElementProperty *>(mGridPropertyContainer->objectAtIndex(i*GRID_VOLUME+j));;
                                CC_BREAK_IF(!eleBlock);
                                if (eleBlock->mType==kElementType_Sword) {
                                    eleBlock->mType=kElementType_Coin;
                                }
                                gridLayer->refreshCell(i, j);
                            }
                        }
                    } while (0);
                    triggerMagicAnimation(kMagicType_GoldenTouch);
                }
                
                mMagic.mCDTime=20;
                mMagicTriggerTip=false;
                break;
            }
            case kMagicType_Shatter:{
                //half the monster's property(shield & damage)
                if (!hasMageBoss) {
                    do {
                        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
                        CC_BREAK_IF(!gridLayer);
                        
                        for (int i=0; i<GRID_ROW; i++) {
                            for (int j=0; j<GRID_VOLUME; j++) {
                                GridCell *cell=gridLayer->getGridCell(i, j);
                                CC_BREAK_IF(!cell);
                                GridElementProperty *block=cell->getCellProperty();
                                CC_BREAK_IF(!block);
                                if (block->mType==kElementType_Monster) {
                                    block->mMonsterProperty.mDamage=block->mMonsterProperty.mDamage/2;
                                    block->mMonsterProperty.mDefence=block->mMonsterProperty.mDefence/2;
                                }
                                GridElementProperty *eleBlock=dynamic_cast<GridElementProperty *>(mGridPropertyContainer->objectAtIndex(i*GRID_VOLUME+j));;
                                CC_BREAK_IF(!eleBlock);
                                if (eleBlock->mType==kElementType_Monster) {
                                    eleBlock->mMonsterProperty.mDamage=eleBlock->mMonsterProperty.mDamage/2;
                                    eleBlock->mMonsterProperty.mDefence=eleBlock->mMonsterProperty.mDefence/2;
                                }
                                gridLayer->refreshCell(i, j);
                            }
                        }
                    } while (0);
                    triggerMagicAnimation(kMagicType_Shatter);
                }
                
                mMagic.mCDTime=23;
                mMagicTriggerTip=false;
                break;
            }
            case kMagicType_Scavenge:{
                if (!hasMageBoss) {
                    do {
                        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
                        CC_BREAK_IF(!gridLayer);
                        
                        for (int i=0; i<GRID_ROW; i++) {
                            for (int j=0; j<GRID_VOLUME; j++) {
                                GridCell *cell=gridLayer->getGridCell(i, j);
                                CC_BREAK_IF(!cell);
                                GridElementProperty *block=cell->getCellProperty();
                                CC_BREAK_IF(!block);
                                if (block->mType==kElementType_Sword) {
                                    block->mType=kElementType_Shield;
                                }
                                GridElementProperty *eleBlock=dynamic_cast<GridElementProperty *>(mGridPropertyContainer->objectAtIndex(i*GRID_VOLUME+j));;
                                CC_BREAK_IF(!eleBlock);
                                if (eleBlock->mType==kElementType_Sword) {
                                    eleBlock->mType=kElementType_Shield;
                                }
                                gridLayer->refreshCell(i, j);
                            }
                        }
                    } while (0);
                    triggerMagicAnimation(kMagicType_Scavenge);
                }
                
                mMagic.mCDTime=20;
                mMagicTriggerTip=false;
                break;
            }
            case kMagicType_Teleport:{
                //remove all block and generate new block
                if (!hasMageBoss) {
                    do {
                        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
                        CC_BREAK_IF(!gridLayer);
                        
                        for (int i=0; i<GRID_ROW; i++) {
                            for (int j=0; j<GRID_VOLUME; j++) {
                                insertCellIntoConnectedArray(i, j);
                            }
                        }
                    } while (0);
                    
                    cleanAndRefreshGrid();
                    triggerMagicAnimation(kMagicType_Teleport);
                }
                
                mMagic.mCDTime=20;
                mMagicTriggerTip=false;
                break;
            }
            case kMagicType_Heal:{
                if (!hasMageBoss) {
                    do {
                        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
                        CC_BREAK_IF(!gridLayer);
                        
                        for (int i=0; i<GRID_ROW; i++) {
                            for (int j=0; j<GRID_VOLUME; j++) {
                                GridCell *cell=gridLayer->getGridCell(i, j);
                                CC_BREAK_IF(!cell);
                                GridElementProperty *block=cell->getCellProperty();
                                CC_BREAK_IF(!block);
                                if (block->mType==kElementType_Potion) {
                                    insertCellIntoConnectedArray(i, j);
                                }
                            }
                        }
                        
                    } while (0);
                    
                    mCurPortion=mPlayerProperty.mMaxHealth;
                    cleanAndRefreshGrid();
                    updateStatusData();
                    triggerMagicAnimation(kMagicType_Heal);
                }
                
                mMagic.mCDTime=20;
                mMagicTriggerTip=false;
                break;
            }
            default:
                break;
        }
    } while (0);
    MainGameToolBar *toolBar=((MainGameScene *)m_scene)->getToolBar();
    if (toolBar) {
        toolBar->refreshMagicCD(mMagic.mCDTime);
    }
}

void MainGameController::triggerMagicAnimation(MagicType pID)
{
    
}

void MainGameController::equipWeapon(unsigned int pID)
{
    mPlayerProperty.mWeaponID=pID;                  //duplicated
    WeaponController::shareInstance()->addWeaponToPackage(pID);
}

void MainGameController::disableWeapon(unsigned int pID)
{
    if (mPlayerProperty.mWeaponID==pID) {
        mPlayerProperty.mWeaponID=0;
    }
    if (WeaponController::shareInstance()->getWeapon(pID)) {
        WeaponController::shareInstance()->removeWeapon(pID);
    }
}

void MainGameController::triggerWeapon(unsigned int pID)
{
    
}

void MainGameController::triggerBossSkill()
{
    do{
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        
        bool hasBossHealer = false;
        bool hasBossTrampling = false;
        bool hasBossGoldenRun = false;
        for (int i=0; i<GRID_ROW; i++) {
            for (int j=0; j<GRID_VOLUME; j++) {
                GridCell *cell=gridLayer->getGridCell(i, j);
                CC_BREAK_IF(!cell);
                GridElementProperty *blockProperty=cell->getCellProperty();
                CC_BREAK_IF(!blockProperty);
                
                if (blockProperty->mType == kElementType_Monster
                    && blockProperty->mMonsterProperty.mType == kBustyType_Boss) {
                    if (blockProperty->mMonsterProperty.mSkillType == kBossBustyType_Chaotic) {
                        //Chaotic boss,随机移动自己的地方
                        int randomIndex = 0;
                        do {
                            randomIndex = arc4random()%(GRID_ROW*GRID_VOLUME);
                        } while ((randomIndex/GRID_VOLUME==blockProperty->mIndex.rIndex) && (randomIndex%GRID_VOLUME==blockProperty->mIndex.vIndex));
                        
                        GridElementProperty *randomBlockProperty=dynamic_cast<GridElementProperty *>(mGridPropertyContainer->objectAtIndex(randomIndex));
                        CC_BREAK_IF(!randomBlockProperty);
                        
                        //update the vIndex after exchange the two elements
                        int tIndex=blockProperty->mIndex.rIndex;
                        int vIndex=blockProperty->mIndex.vIndex;
                        blockProperty->mIndex.rIndex=randomBlockProperty->mIndex.rIndex;
                        blockProperty->mIndex.vIndex=randomBlockProperty->mIndex.vIndex;
                        randomBlockProperty->mIndex.rIndex=tIndex;
                        randomBlockProperty->mIndex.vIndex=vIndex;
                        mGridPropertyContainer->exchangeObject(blockProperty, randomBlockProperty);
                        
                        //notify the grid layer to exchange cell in m_GridCellArray
                        gridLayer->exchangeGridCell(blockProperty->mIndex.rIndex*GRID_VOLUME+blockProperty->mIndex.vIndex, randomBlockProperty->mIndex.rIndex*GRID_VOLUME+randomBlockProperty->mIndex.vIndex);
                    } else if (blockProperty->mMonsterProperty.mSkillType == kBossBustyType_Poisonous) {
                        if (blockProperty->mMonsterProperty.mValidRound>0) {
                            mCurPortion-=(mPlayerProperty.mMaxHealth/10);
                            if (mCurPortion<0) {
                                mCurPortion=0;
                            }
                            blockProperty->mMonsterProperty.mValidRound--;
                        }
                    } else if (blockProperty->mMonsterProperty.mSkillType == kBossBustyType_Healer){
                        //让所有受到伤害的怪兽回复生命值到最大值。
                        hasBossHealer = true;
                    } else if (blockProperty->mMonsterProperty.mSkillType == kBossBustyType_Vampire) {
                        int vampiredLife = blockProperty->mMonsterProperty.mLife + blockProperty->mMonsterProperty.mDamage;     //吸血boss吸血后的生命值
                        if (vampiredLife > blockProperty->mMonsterProperty.mMaxLife) {
                            blockProperty->mMonsterProperty.mLife = blockProperty->mMonsterProperty.mMaxLife;
                        } else {
                            blockProperty->mMonsterProperty.mLife = vampiredLife;
                        }
                    } else if (blockProperty->mMonsterProperty.mSkillType == kBossBustyType_Trampling) {
                        //践踏boss，随机破坏一个剑或者盾
                        hasBossTrampling = true;
                    } else if (blockProperty->mMonsterProperty.mSkillType == kBossBustyType_Golden) {
                        blockProperty->mMonsterProperty.mValidRound--;
                        if (blockProperty->mMonsterProperty.mValidRound == 0) {
                            hasBossGoldenRun = true;
                            
                            if (mRunGoldenBossContainer == NULL) {
                                mRunGoldenBossContainer = CCArray::create();
                                mRunGoldenBossContainer->retain();
                            }
                            mRunGoldenBossContainer->addObject(blockProperty);
                        }
                    } else if (blockProperty->mMonsterProperty.mSkillType == kBossBustyType_Kamikaze) {
                        blockProperty->mMonsterProperty.mValidRound--;
                        if (blockProperty->mMonsterProperty.mValidRound == 0) {
                            mCurPortion = mCurPortion/2;
                            blockProperty->mMonsterProperty.mValidRound = 2;
                        }
                    }
                }
            }
        }
        
        if (hasBossHealer) {
            recoverMonsterLifeFull();
        }
        if (hasBossTrampling) {
            markRandomSwordOrShieldBroken();
        }
        if (hasBossGoldenRun) {
            cleanRunGoldenBoss();
        }
        gridLayer->refreshMonsterPropertyLabelOfAllGridCell();
        gridLayer->updateGrid();
        updateStatusData();
    }while(0);
}

void MainGameController::recoverMonsterLifeFull()
{
    do {
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        for (int i=0; i<GRID_ROW; i++) {
            for (int j=0; j<GRID_VOLUME; j++) {
                GridCell *cell=gridLayer->getGridCell(i, j);
                CC_BREAK_IF(!cell);
                GridElementProperty *geProperty = cell->getCellProperty();
                CC_BREAK_IF(!geProperty);
                if (geProperty->mType == kElementType_Monster) {
                    geProperty->mMonsterProperty.mLife = geProperty->mMonsterProperty.mMaxLife;
                }
            }
        }
    } while (0);
}

void MainGameController::markRandomSwordOrShieldBroken()
{
    do {
        CCArray *toMarkGrids = CCArray::createWithCapacity(0);
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        for (int i=0; i<GRID_ROW; i++) {
            for (int j=0; j<GRID_VOLUME; j++) {
                GridCell *cell=gridLayer->getGridCell(i, j);
                CC_BREAK_IF(!cell);
                GridElementProperty *geProperty = cell->getCellProperty();
                CC_BREAK_IF(!geProperty);
                if (geProperty->mType == kElementType_Bow
                    || geProperty->mType == kElementType_Sword
                    || geProperty->mType == kElementType_Shield) {
                    toMarkGrids->addObject(geProperty);
                }
            }
        }
        
        if (toMarkGrids->count() > 0) {
            int randomIndex = arc4random() % toMarkGrids->count();
            GridElementProperty *gProperty = (GridElementProperty *)toMarkGrids->objectAtIndex(randomIndex);
            gProperty->mbBroken = true;
        }
    } while (0);
}

void MainGameController::cleanRunGoldenBoss()
{
    for (int i = 0; i < mRunGoldenBossContainer->count(); i++) {
        //set grid element property status
        GridElementProperty *gProperty = (GridElementProperty *)mRunGoldenBossContainer->objectAtIndex(i);
        CC_BREAK_IF(!gProperty);
        insertCellIntoConnectedArray(gProperty->mIndex.rIndex, gProperty->mIndex.vIndex);
    }
    //set grid element property status
    for (int i=0; i<mStageConnectedElements->count(); i++) {
        GridCell *cell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(i));
        CC_BREAK_IF(!cell);
        
        GridElementProperty *block=cell->getCellProperty();
        CC_BREAK_IF(!block);
        
        GridElementProperty *item=dynamic_cast<GridElementProperty *>(mGridPropertyContainer->objectAtIndex(block->mIndex.rIndex*GRID_VOLUME+block->mIndex.vIndex));
        CC_BREAK_IF(!item);
        if (block->mType==kElementType_Monster && block->mMonsterProperty.mType==kBossBustyType_Golden) {
            block->setStatus(true);
            item->setStatus(true);
            
            DRUserDefault::sharedUserDefault()->setScore(DRUserDefault::sharedUserDefault()->getScore()+1);
            mCurStageScore++;
            DRUserDefault::sharedUserDefault()->setKillMonsterCount(DRUserDefault::sharedUserDefault()->getKillMonsterCount()+1);
            mCurStageKillMonster++;
        }
    }
    
    cleanAndRefreshGrid();
    updateStatusData();
    
    mRunGoldenBossContainer->removeAllObjects();
}

void MainGameController::statisticsDataPerRound()
{
    //statistics cur connected cell status data
    bool hasMageBoss=false;
    do {
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        CC_BREAK_IF(!mStageConnectedElements);
        
        int totalDamagePerRound = this->computeTotalDamageOfRound();
        bool hasMonsterHurt = false;        //是否在消除怪
        bool hasSpikyClear = mCurrentSpikyCount==0?true:false;         //反弹怪是否全消除了
        bool hasCorrosiveBoss=false;
        
        for (int i=0; i<GRID_ROW; i++) {
            for (int j=0; j<GRID_VOLUME; j++) {
                GridCell *cell=gridLayer->getGridCell(i, j);
                CC_BREAK_IF(!cell);
                GridElementProperty *block=cell->getCellProperty();
                CC_BREAK_IF(!block);
                if (block->mType==kElementType_Monster && block->mMonsterProperty.mSkillType==kBossBustyType_Corrosive && block->mMonsterProperty.mLife>0) {
                    hasCorrosiveBoss=true;
                    break;
                }
            }
        }
        for (int i=0; i<mStageConnectedElements->count(); i++) {
            GridCell *cell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(i));
            CC_BREAK_IF(!cell);
            
            GridElementProperty *block=cell->getCellProperty();
            CC_BREAK_IF(!block);
            if (block->mType==kElementType_Monster) {
                if (totalDamagePerRound >= block->mMonsterProperty.mLife+block->mMonsterProperty.mDefence) {
                    hasMonsterHurt = true;
                    block->mMonsterProperty.mLife = 0;
                    DRUserDefault::sharedUserDefault()->setKillMonsterCount(DRUserDefault::sharedUserDefault()->getKillMonsterCount()+1);
                    mCurStageKillMonster++;
                    
                    DRUserDefault::sharedUserDefault()->setScore(DRUserDefault::sharedUserDefault()->getScore()+1);
                    mCurStageScore++;
                    
                    if (block->mMonsterProperty.mType==kBustyType_Boss) {
                        
                        if (block->mMonsterProperty.mSkillType == kBossBustyType_Spiky) {
                            mCurrentSpikyCount--;
                            if (mCurrentSpikyCount<=0) {
                                mCurrentSpikyCount = 0;
                                hasSpikyClear = true;
                            }
                        } else if (block->mMonsterProperty.mSkillType == kBossBustyType_Mage) {
                            mMageEnable = true;
                        }
                    }
                } else {
                    if (block->mMonsterProperty.mDefence>0 && block->mMonsterProperty.mDefence>=totalDamagePerRound) {
                    }else{
                        block->mMonsterProperty.mLife -= (totalDamagePerRound-block->mMonsterProperty.mDefence);
                    }
                }
                if (block->mMonsterProperty.mSkillType==kBossBustyType_Mage && block->mMonsterProperty.mLife>0) {
                    hasMageBoss=true;
                }
            }else if(block->mType==kElementType_Coin){
                DRUserDefault::sharedUserDefault()->setCoin(DRUserDefault::sharedUserDefault()->getCoin()+1);
                mCurStageCoin++;
            }else if(block->mType==kElementType_Shield){
                if (!hasCorrosiveBoss && !(block->mbBroken)) {
                    mCurShield++;
                    if (mCurShield>mPlayerProperty.mMaxShield) {
                        mCurShield=mPlayerProperty.mMaxShield;
                    }
                }
            }else if(block->mType==kElementType_Potion){
                int weaponPortion=1;
                if (mPlayerProperty.mWeaponID) {
                    WeaponConfigure *weapon=WeaponController::shareInstance()->getWeapon(mPlayerProperty.mWeaponID);
                    if (weapon) {
                        weaponPortion=weapon->mHealthPerPotion;
                    }
                }
                mCurPortion+=weaponPortion;
                if (mCurPortion>mPlayerProperty.mMaxHealth) {
                    mCurPortion=mPlayerProperty.mMaxHealth;
                }
            }
        }
        
        if (hasMonsterHurt && mSpiky) { //有反弹boss
            mCurPortion-=totalDamagePerRound;
            if (mCurPortion<=0) {
                mCurPortion=0;
            }
        }
        if (hasSpikyClear) {
            mSpiky = false;
        }
    }while(0);
    
    //statistics the unconnected cell status data(shield and portion)
    do {
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        
        if (!hasMageBoss && mMagicTriggerTip && mMagic.mMagicType==kMagicType_CounterAttack && mMagic.mCDTime==22) {
            //CounterAttack magic
            for (int i=0; i<GRID_ROW; i++) {
                for (int j=0; j<GRID_VOLUME; j++) {
                    GridCell *cell=gridLayer->getGridCell(i, j);
                    CC_BREAK_IF(!cell);
                    
                    GridElementProperty *block=cell->getCellProperty();
                    CC_BREAK_IF(!block);
                    if (block->mType==kElementType_Monster && block->mMonsterProperty.mLife>0) {
                        if (block->mMonsterProperty.mDamage >= block->mMonsterProperty.mLife+block->mMonsterProperty.mDefence) {
                            block->mMonsterProperty.mLife = 0;
                            DRUserDefault::sharedUserDefault()->setKillMonsterCount(DRUserDefault::sharedUserDefault()->getKillMonsterCount()+1);
                            mCurStageKillMonster++;
                            
                            if (block->mMonsterProperty.mType==kBustyType_Common) {
                                DRUserDefault::sharedUserDefault()->setScore(DRUserDefault::sharedUserDefault()->getScore()+1);
                                mCurStageScore++;
                            }else{
                                DRUserDefault::sharedUserDefault()->setScore(DRUserDefault::sharedUserDefault()->getScore()+1);
                                mCurStageScore++;
                            }
                            
                            insertCellIntoConnectedArray(block->mIndex.rIndex, block->mIndex.vIndex);
                        }else{
                            if (block->mMonsterProperty.mDefence>0 && block->mMonsterProperty.mDefence>=block->mMonsterProperty.mDamage) {
                            }else{
                                block->mMonsterProperty.mLife -= (block->mMonsterProperty.mDamage-block->mMonsterProperty.mDefence);
                                block->mMonsterProperty.mLife = 0;
                            }
                            gridLayer->refreshCell(block->mIndex.rIndex, block->mIndex.vIndex);
                        }
                    }
                }
            }
            mMagicTriggerTip=false;
            triggerMagicAnimation(kMagicType_CounterAttack);
        }else{
            int totalDamage=0;
            for (int i=0; i<GRID_ROW; i++) {
                for (int j=0; j<GRID_VOLUME; j++) {
                    GridCell *cell=gridLayer->getGridCell(i, j);
                    CC_BREAK_IF(!cell);
                    
                    GridElementProperty *block=cell->getCellProperty();
                    CC_BREAK_IF(!block);
                    if (false==block->getStatus()) {
                        if (block->mType==kElementType_Monster && block->mMonsterProperty.mLife>0) {
                            totalDamage+=block->mMonsterProperty.mDamage;
                        }
                    }
                }
            }
            
            int weaponShield=1;
            if (mPlayerProperty.mWeaponID) {
                WeaponConfigure *weapon=WeaponController::shareInstance()->getWeapon(mPlayerProperty.mWeaponID);
                if (weapon) {
                    weaponShield=weapon->mDefencePerShield;
                }
            }
            mCurShield=weaponShield*mCurShield-totalDamage;
            if (mCurShield>0 && mCurShield>mPlayerProperty.mMaxShield) {
                mCurShield=mPlayerProperty.mMaxShield;
            }
            if (mCurShield<0) {
                mCurPortion+=mCurShield;
                if (mCurPortion<=0) {
                    mCurPortion=0;
                }
                mCurShield=0;
            }
        }
    } while (0);
}

//此处判断是否装备了武器,如果装备了武器，则需要根据武器属性计算总伤害值
int MainGameController::computeTotalDamageOfRound()
{
//    CCArray *weaponsConf=DataManager::sharedInstance()->weaponConfigures();
    CCArray *weaponsConf=WeaponController::shareInstance()->getWeaponPackage();
    WeaponConfigure *weapon=NULL;
    if (mPlayerProperty.mWeaponID>0 && weaponsConf && weaponsConf->count()) {
        for (int i=0;i<weaponsConf->count();i++) {
            WeaponConfigure *item=dynamic_cast<WeaponConfigure *>(weaponsConf->objectAtIndex(i));
            CC_BREAK_IF(!item);
            if (item->mWeaponNumber==mPlayerProperty.mWeaponID) {
                weapon=item;
                break;
            }
        }
    }
    int totalDamagePerRound = 0;
    do {
        CC_BREAK_IF(!mStageConnectedElements);
        bool hasMonster = false;
        for (int i=0; i<mStageConnectedElements->count(); i++) {
            GridCell *cell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(i));
            CC_BREAK_IF(!cell);
            
            GridElementProperty *block=cell->getCellProperty();
            CC_BREAK_IF(!block);
            if ((block->mType==kElementType_Sword || block->mType == kElementType_Bow)
                && !block->mbBroken) {
                totalDamagePerRound+=mPlayerProperty.mWeaponDamage;
                if (weapon) {
                    totalDamagePerRound+=(int)(weapon->mWeaponDamage);
                }
            } else if (block->mType==kElementType_Monster) {
                hasMonster = true;
            }
        }
        
        if (hasMonster) {
            if (weapon) {
                totalDamagePerRound+=(int)(weapon->mBasicDamage);
            }
            totalDamagePerRound+=mPlayerProperty.mBasicDamage;
        }
    } while (0);
    
    return totalDamagePerRound;
}

void MainGameController::resetStageStatusData()
{
    mCurStageKillMonster=0;
    mCurStageCoin=0;
    mCurPortion=0;
    mCurShield=mPlayerProperty.mMaxShield;
    mCurStageScore=0;
    mCurStageRound=0;
}

bool MainGameController::judgeGameStageIsEnd()
{
    bool tRet=false;
    
    do{
        //judge whether current game stage can end according to the pass condition ID
        switch (mStageProperty.mPassCondID) {
            case 0:
                
                break;
        }
    }while(0);
    
	return tRet;
}

void MainGameController::endCurrentStage()
{
    //end game stage:save game status data
    do{
        resetStageStatusData();
        updateStatusData();
        CCLog("_______________stage end");
    }while(0);
}

bool MainGameController::judgeConnectedElementsCanClear()
{
	bool tRet=false;
    
    do{
        CC_BREAK_IF(!mStageConnectedElements || mStageConnectedElements->count()<3);
        tRet=true;
    }while(0);
    
	return tRet;
}

void MainGameController::resetStageConnectedElements()
{
    do {
        CC_BREAK_IF(!mStageConnectedElements);
        
        mStageConnectedElements->removeAllObjects();
        
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        gridLayer->clearConnectLine();
    } while (0);
}

void MainGameController::cleanAndRefreshGrid()
{
    do {
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        
        //clear cells on MainGameGridLayer
        for (int i=0; i<mStageConnectedElements->count(); i++) {
            GridCell *cell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(i));
            CC_BREAK_IF(!cell);
            
            GridElementProperty *block=cell->getCellProperty();
            CC_BREAK_IF(!block);
            if (block->getStatus()) {
                gridLayer->removeGridCell(block->mIndex.rIndex, block->mIndex.vIndex);
            }
        }
        
        //update property data in mGridPropertyContainer:bubble sort
        for (int i=0; i<GRID_VOLUME; i++) {
            for (int j=GRID_ROW-1; j>=0; j--) {
                GridElementProperty *item=dynamic_cast<GridElementProperty *>(mGridPropertyContainer->objectAtIndex(j*GRID_VOLUME+i));
                CC_BREAK_IF(!item);
                if (item->getStatus()) {
                    //exchange with the above nearest property that is not cleared
                    for (int k=j-1; k>=0; k--) {
                        GridElementProperty *block=dynamic_cast<GridElementProperty *>(mGridPropertyContainer->objectAtIndex(k*GRID_VOLUME+i));
                        CC_BREAK_IF(!block);
                        if (false==block->getStatus()) {
                            //update the vIndex after exchange the two elements
                            int tIndex=item->mIndex.rIndex;
                            item->mIndex.rIndex=block->mIndex.rIndex;
                            block->mIndex.rIndex=tIndex;
                            mGridPropertyContainer->exchangeObject(block, item);
                            
                            //notify the grid layer to exchange cell in m_GridCellArray
                            gridLayer->exchangeGridCell(k*GRID_VOLUME+i, j*GRID_VOLUME+i);
                            break;
                        }
                    }
                }
            }
            
            //generate new property replace the clear elements up to down
            for (int j=0; j<GRID_ROW; j++) {
                GridElementProperty *item=dynamic_cast<GridElementProperty *>(mGridPropertyContainer->objectAtIndex(j*GRID_VOLUME+i));
                CC_BREAK_IF(!item);
                if (item->getStatus()) {
                    generateGridCell(item->mIndex.rIndex, item->mIndex.vIndex);
                    
                    //notify grid layer to generate new cell to replace the cleard cell
                    gridLayer->addGridCell(item->mIndex.rIndex, item->mIndex.vIndex);
                }else{
                    break;
                }
            }
        }
        
        gridLayer->clearConnectLine();
        //update MainGameGridLayer to show new cell
        gridLayer->setUpdateTip(true);
        gridLayer->updateGrid();
    } while (0);
}

bool MainGameController::clearConnectedElements()
{
    bool hasNoElementToClear = true;
    do {
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        CC_BREAK_IF(!mStageConnectedElements);
        
        statisticsDataPerRound();
        
        //set grid element property status
        for (int i=0; i<mStageConnectedElements->count(); i++) {
            GridCell *cell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(i));
            CC_BREAK_IF(!cell);
            
            GridElementProperty *block=cell->getCellProperty();
            CC_BREAK_IF(!block);
            
            GridElementProperty *item=dynamic_cast<GridElementProperty *>(mGridPropertyContainer->objectAtIndex(block->mIndex.rIndex*GRID_VOLUME+block->mIndex.vIndex));
            CC_BREAK_IF(!item);
            if (block->mType==kElementType_Monster) {
                if (block->mMonsterProperty.mLife == 0) {
                    block->setStatus(true);
                    item->setStatus(true);
                    
                    hasNoElementToClear = false;
                } else {
                    block->setStatus(false);
                    item->setStatus(false);
                }
            } else {
                block->setStatus(true);
                item->setStatus(true);
                
                hasNoElementToClear = false;
            }
        }
        
        cleanAndRefreshGrid();
    } while (0);
    
    CCArray *connectedEle=CCArray::create();
    connectedEle->addObjectsFromArray(mStageConnectedElements);
    mStageConnectedElements->removeAllObjects();
    
    if (mMagic.mID>0) {
        mMagic.mCDTime--;
        MainGameToolBar *toolBar=((MainGameScene *)m_scene)->getToolBar();
        if (toolBar) {
            toolBar->refreshMagicCD(mMagic.mCDTime);
        }
    }
    if (judgeIsTriggerMagic(connectedEle)) {
        triggerMagic(mMagic.mMagicType,connectedEle);
    }
    MainGameToolBar *toolBar=((MainGameScene *)m_scene)->getToolBar();
    if (toolBar) {
        toolBar->refreshMagicCD(mMagic.mCDTime);
        if (judgeIsEnableMagic()) {
            toolBar->enableMagic();
        }else{
            toolBar->disableMagic();
        }
    }
    
    DRUserDefault::sharedUserDefault()->setRoundCount(DRUserDefault::sharedUserDefault()->getRoundCount()+1);
    mCurStageRound++;
    DRUserDefault::sharedUserDefault()->setScore(DRUserDefault::sharedUserDefault()->getScore()+1);
    mCurStageScore++;
    
    updateStatusData();
	//√øªÿ∫œΩ· ¯∂º≈–∂œµ±«∞πÿø® «∑ÒΩ· ¯
	//judge whether the current stage is end
    if (this->judgeGameStageIsEnd()) {
        this->endCurrentStage();
    }
    
    return hasNoElementToClear;
}

bool MainGameController::generateGridCell(unsigned int rIndex,unsigned int vIndex)
{
    bool tSuc=false;
    
    do {
        CCDictionary *rDict = DataManager::sharedInstance()->getGridElements();
        
        GridElementProperty *blockProperty = new GridElementProperty();
        blockProperty->init();

        if (rDict->count() > 0) {
            
//            std::stringstream sStream;
//            sStream<<rIndex<<"_"<<vIndex;
//            
//            CCDictionary *currentDic = (CCDictionary *)rDict->objectForKey(sStream.str());
//            if (currentDic) {
//                //read plist Data
//                CCString *strRIndex = (CCString *)currentDic->objectForKey("rIndex");
//                blockProperty->mIndex.rIndex= strRIndex->intValue();
//                CCString *strVIndex = (CCString *)currentDic->objectForKey("vIndex");
//                blockProperty->mIndex.vIndex=strVIndex->intValue();
//                CCString *strType = (CCString *)currentDic->objectForKey("mType");
//                blockProperty->mType=(ElementType)strType->intValue();
//                CCString *strID = (CCString *)currentDic->objectForKey("mID");
//                blockProperty->mID=strID->intValue();
//            } else {
                blockProperty->mIndex.rIndex=rIndex;
                blockProperty->mIndex.vIndex=vIndex;
                blockProperty->generateGridElementDataByCSV(true);
                
                blockProperty->saveToDictionary(rDict);
//            }
        } else {
            blockProperty->mIndex.rIndex=rIndex;
            blockProperty->mIndex.vIndex=vIndex;
            blockProperty->generateGridElementDataByCSV(true);
            
            blockProperty->saveToDictionary(rDict);
        }
        
        //生成boss时判断状态逻辑
        if (blockProperty->mMonsterProperty.mType == kBustyType_Boss) {
            
            if (blockProperty->mMonsterProperty.mSkillType == kBossBustyType_Spiky) {
                mSpiky = true;
                mCurrentSpikyCount++;
            } else if (blockProperty->mMonsterProperty.mSkillType == kBossBustyType_Mage) {
                mMageEnable = false;
            }
        }
        
        if (rIndex*GRID_VOLUME+vIndex<mGridPropertyContainer->count() && mGridPropertyContainer->objectAtIndex(rIndex*GRID_VOLUME+vIndex)) {
            //replace
            mGridPropertyContainer->replaceObjectAtIndex(rIndex*GRID_VOLUME+vIndex, blockProperty);
        }else{
            //add
            mGridPropertyContainer->insertObject(blockProperty, rIndex*GRID_VOLUME+vIndex);
        }
        
        tSuc=true;
    } while (0);
    
    return tSuc;
}

GridElementProperty* MainGameController::getGridElementProperty(unsigned int rIndex,unsigned int vIndex)
{
    GridElementProperty *blockProperty;
    do {
        CC_BREAK_IF(rIndex>=GRID_ROW || vIndex>=GRID_VOLUME);
        
        blockProperty=(GridElementProperty *)mGridPropertyContainer->objectAtIndex(rIndex*GRID_ROW+vIndex);
    } while (0);
    
    return blockProperty;
}
	
void MainGameController::processGridCellSelected(unsigned int rIndex,unsigned int vIndex)
{
    LOG_TRACE
    
    do{
        CC_BREAK_IF(!mStageConnectedElements);
        
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        
        GridCell *cell=gridLayer->getGridCell(rIndex, vIndex);
        CC_BREAK_IF(!cell);
        
        GridElementProperty *blockProperty=cell->getCellProperty();
        CC_BREAK_IF(!blockProperty);
        
        if (mStageConnectedElements->count()==0) {
            insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
            break;
        }else{
            GridCell *preCell=dynamic_cast<GridCell *>(mStageConnectedElements->lastObject()) ;
            CC_BREAK_IF(!preCell);
            GridElementProperty *preBlockProperty=preCell->getCellProperty();
            CC_BREAK_IF(!preBlockProperty);
            
            GridCell *prePreCell=NULL;
            GridElementProperty *prePreBlockProperty=NULL;
            if (mStageConnectedElements->count()>=2) {
                prePreCell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(mStageConnectedElements->count()-2)) ;
                CC_BREAK_IF(!prePreCell);
                prePreBlockProperty=prePreCell->getCellProperty();
                CC_BREAK_IF(!prePreBlockProperty);
            }
            
            if(prePreBlockProperty && blockProperty->mIndex.vIndex==prePreBlockProperty->mIndex.vIndex && blockProperty->mIndex.rIndex== prePreBlockProperty->mIndex.rIndex){
                //remove
                removeCellFromConnectedArray();
            }else{
                if (blockProperty->mType == preBlockProperty->mType) {
                    //same type elements
                    if (preBlockProperty->mType==kElementType_Bow) {
                        //attach distance +1
                        if (abs(preBlockProperty->mIndex.rIndex-blockProperty->mIndex.rIndex)<=2 && abs(preBlockProperty->mIndex.vIndex-blockProperty->mIndex.vIndex)<=2) {
                            
                            insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
                            break;
                        }
                    }else{
                        if (abs(preBlockProperty->mIndex.rIndex-blockProperty->mIndex.rIndex)<=1 && abs(preBlockProperty->mIndex.vIndex-blockProperty->mIndex.vIndex)<=1) {
                            
                            insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
                            break;
                        }
                    }
                }else{
                    //different type
                    if ((blockProperty->mType==kElementType_Bow || blockProperty->mType==kElementType_Sword || blockProperty->mType==kElementType_Monster) && (preBlockProperty->mType==kElementType_Bow || preBlockProperty->mType==kElementType_Sword || preBlockProperty->mType==kElementType_Monster)) {
                        if (preBlockProperty->mType==kElementType_Bow) {
                            //attach distance +1
                            if (abs(preBlockProperty->mIndex.rIndex-blockProperty->mIndex.rIndex)<=2 && abs(preBlockProperty->mIndex.vIndex-blockProperty->mIndex.vIndex)<=2) {
                                
                                insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
                                break;
                            }
                        }else{
                            if (abs(preBlockProperty->mIndex.rIndex-blockProperty->mIndex.rIndex)<=1 && abs(preBlockProperty->mIndex.vIndex-blockProperty->mIndex.vIndex)<=1) {
                                
                                insertCellIntoConnectedArray(blockProperty->mIndex.rIndex, blockProperty->mIndex.vIndex);
                                break;
                            }
                        }
                    }
                }
                
            }
        }
        
    }while(0);
}

//insert a cell into the connected array
void MainGameController::insertCellIntoConnectedArray(unsigned int rIndex,unsigned int vIndex)
{
    LOG_TRACE
    do{
        if (judgeGridCellCanInserted(rIndex, vIndex)) {
            MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
            CC_BREAK_IF(!gridLayer);
            
            GridCell *cell=gridLayer->getGridCell(rIndex, vIndex);
            CC_BREAK_IF(!cell);
            
            mStageConnectedElements->addObject(cell);
            
            //add the connected line between the two cells
            addConnectedLine();
            
            //play sound effect
            GridElementProperty *blockProperty=cell->getCellProperty();
            playSelctedSoundEffect(blockProperty->mType);
        }
    }while(0);
}

//remove a cell from the connected array
void MainGameController::removeCellFromConnectedArray()
{
    LOG_TRACE
    do{
        CC_BREAK_IF(!mStageConnectedElements || mStageConnectedElements->count()==0);
        GridCell *cell=dynamic_cast<GridCell *>(mStageConnectedElements->lastObject());
        GridElementProperty *blockProperty=cell->getCellProperty();
        
        //remove the connected line between the two cells
        cleanConnectedLine();
        
        mStageConnectedElements->removeLastObject();
        
        //play sound effect
        playSelctedSoundEffect(blockProperty->mType);
    }while(0);
}

void MainGameController::playSelctedSoundEffect(ElementType pType)
{
    LOG_TRACE
    
}

void MainGameController::playClearSoundEffect()
{
    LOG_TRACE
    
}

void MainGameController::addConnectedLine()
{
    LOG_TRACE
    do {
        CC_BREAK_IF(!mStageConnectedElements || mStageConnectedElements->count()<2);
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        GridCell *fCell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(mStageConnectedElements->count()-2));
        GridCell *sCell=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(mStageConnectedElements->count()-1));
        gridLayer->addConnectLine(fCell,sCell);
    } while (0);
}

void MainGameController::cleanConnectedLine()
{
    LOG_TRACE
    do {
        MainGameGridLayer *gridLayer = ((MainGameScene *)m_scene)->getGridLayer();
        CC_BREAK_IF(!gridLayer);
        gridLayer->removeConnectLine();
    } while (0);
}

bool MainGameController::judgeGridCellCanInserted(unsigned int rIndex,unsigned int vIndex)
{
    LOG_TRACE
    bool tRet=true;
    
    do {
        CC_BREAK_IF(!mStageConnectedElements || mStageConnectedElements->count()<=0);
        for (int i=0;i<mStageConnectedElements->count();i++) {
            GridCell *item=dynamic_cast<GridCell *>(mStageConnectedElements->objectAtIndex(i));
            CC_BREAK_IF(!item);
            
            GridElementProperty *blockProperty=item->getCellProperty();
            if (blockProperty->mIndex.rIndex==rIndex && blockProperty->mIndex.vIndex==vIndex) {
                tRet=false;
                break;
            }
        }
    } while (0);
    //CCLog("tRet:%d",tRet);
    return tRet;
}



