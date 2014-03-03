//
//  GridElementProperty.cpp
//  DRGame
//
//  Created by Magic Song on 14-2-24.
//
//

#include "GridElementProperty.h"
#include "DRUtility.h"
#include "CSVParser.h"
#include "DataMangager.h"
#include "BossFileConfigure.h"

GridElementProperty::GridElementProperty()
{
    
}

GridElementProperty::~GridElementProperty()
{
    
}

void GridElementProperty::generateGridElementDataByCSV()
{
    GameStatusType *gameStatus = DataManager::sharedInstance()->gameStatus();
    int flag = gameStatus->mFlag;
    if (flag == -1) {
        //not boss
        BarrierFileConfigure *currentBConfigure = DataManager::sharedInstance()->currentBarrierConfigure();
        int mA = currentBConfigure->mA;
        int mB = currentBConfigure->mB;
        DataManager::sharedInstance()->gameStatus()->mFlag = mA - mB * gameStatus->mNumberOfRound;
        this->configureNormalElementProperty();
    } else if (flag == 0) {
        //boss
        BarrierFileConfigure *currentBConfigure = DataManager::sharedInstance()->currentBarrierConfigure();
        int mA = currentBConfigure->mA;
        int mB = currentBConfigure->mB;
        DataManager::sharedInstance()->gameStatus()->mFlag = mA - mB * gameStatus->mNumberOfRound;
        
        this->configureBossProperty();
    } else {
        //not boss
        
        DataManager::sharedInstance()->gameStatus()->mFlag -= 1;
        this->configureNormalElementProperty();
    }
}


void GridElementProperty::saveToDictionary(CCDictionary *dict)
{
    stringstream strStream;
    strStream << mIndex.rIndex << "_" << mIndex.vIndex;
    
    CCDictionary *gridDict = new CCDictionary();
    
    gridDict->setObject(DRUtility::getCCStringWithInt(mType), "mType");
    gridDict->setObject(DRUtility::getCCStringWithInt(mID), "mID");
    gridDict->setObject(DRUtility::getCCStringWithInt(mIndex.rIndex), "rIndex");
    gridDict->setObject(DRUtility::getCCStringWithInt(mIndex.vIndex), "vIndex");
    dict->setObject(gridDict, strStream.str());
    gridDict->autorelease();
}

bool GridElementProperty::canbeDestroyed()
{
    return mMonsterProperty.mLife <= 0;
}

#pragma mark - Private Method
void GridElementProperty::configureNormalElementProperty()
{
    //confirm the element appear
    this->mID = 0;
    
    //TODO:Element生成概率先写成平均随机的，若有需求，在此改动
    this->mType = (ElementType)DRUtility::randn(kElementType_End-1);
    
    this->configureNormalMonsterProperty();
}

void GridElementProperty::configureNormalMonsterProperty()
{
    //TODO:需要确认普通怪生成逻辑，这里写成固定的
    mMonsterProperty.mType = kBustyType_Common;
    mMonsterProperty.mSkillType = kBossBustyType_None;
    mMonsterProperty.mID = 0;
    mMonsterProperty.mName = "normal monster";
    mMonsterProperty.mDescription = "This is a test Normal Monster";
    mMonsterProperty.mDefence = 2;
    mMonsterProperty.mLife = 3;
    mMonsterProperty.mMaxLife = 3;
    mMonsterProperty.mDamage = 2;
}

void GridElementProperty::configureBossProperty()
{
    GameStatusType *gameStatus = DataManager::sharedInstance()->gameStatus();
    
    BossFileConfigure *bossConfigure = this->getRandomBoss();
    cout<<"bossConfigure = "<< bossConfigure<<endl;
    mMonsterProperty.mType = kBustyType_Boss;
    mMonsterProperty.mSkillType = kBossBustyType_Chaotic;
    mMonsterProperty.mID = bossConfigure->mBossId;
    mMonsterProperty.mName = "boss";
    mMonsterProperty.mDescription = "This is a boss Monster";
    mMonsterProperty.mDefence = bossConfigure->mF + bossConfigure->mG*(float)gameStatus->mNumberOfRound;      //defence = f + g * round
    mMonsterProperty.mMaxLife = bossConfigure->mD + bossConfigure->mE*(float)gameStatus->mNumberOfRound;      //life = d + e * round
    mMonsterProperty.mLife = mMonsterProperty.mMaxLife;
    mMonsterProperty.mDamage = bossConfigure->mH + bossConfigure->mI*(float)gameStatus->mNumberOfRound;      //damage = H + I * round
}

BossFileConfigure * GridElementProperty::getRandomBoss()
{
    CCArray *bossConfigures = DataManager::sharedInstance()->bossConfigures();
    
    int bCongfiguresCount = bossConfigures->count();
    float bossRates[bCongfiguresCount];
    
    BossFileConfigure *bossConfigure = NULL;
    CCObject *object = NULL;
    
    float randomFloat = DRUtility::randFraction();
    cout<<randomFloat<<endl;
    
    float previousBossRate = 0.0f;
    int i = 0;
    CCARRAY_FOREACH(bossConfigures, object)
    {
        bossConfigure = (BossFileConfigure *)object;
        
        bossRates[i] = previousBossRate + bossConfigure->mBossRate;
        if (randomFloat < bossRates[i]) {
            return bossConfigure;
        }
        
        previousBossRate = bossRates[i];
        i++;
    }
    return NULL;
}

