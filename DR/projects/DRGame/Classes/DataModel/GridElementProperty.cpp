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

void GridElementProperty::generateGridElementDataByCSV(bool monsterIncluded)
{
    GameStatusType *gameStatus = DataManager::sharedInstance()->gameStatus();
    int flag = gameStatus->mFlag;
    if (flag == -1) {
        //not boss
        BarrierFileConfigure *currentBConfigure = DataManager::sharedInstance()->currentBarrierConfigure();
        int mA = currentBConfigure->mA;
        int mB = currentBConfigure->mB;
        DataManager::sharedInstance()->gameStatus()->mFlag = mA - mB * gameStatus->mNumberOfRound;
        this->configureNormalElementProperty(monsterIncluded);
    } else if (flag == 0 && monsterIncluded) {
        //boss
        BarrierFileConfigure *currentBConfigure = DataManager::sharedInstance()->currentBarrierConfigure();
        int mA = currentBConfigure->mA;
        int mB = currentBConfigure->mB;
        DataManager::sharedInstance()->gameStatus()->mFlag = mA - mB * gameStatus->mNumberOfRound;
        
        this->configureBossProperty();
    } else {
        //not boss
        
        DataManager::sharedInstance()->gameStatus()->mFlag -= 1;
        this->configureNormalElementProperty(monsterIncluded);
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
void GridElementProperty::configureNormalElementProperty(bool monsterInluced)
{
    //confirm the element appear
    this->mID = 0;
    
    ElementType type = (ElementType)this->getRandomElementType();
    if (!monsterInluced) {
        while (type == kElementType_Monster) {
            type = (ElementType)this->getRandomElementType();
        }
    }
    this->mType = type;
    
    if (this->mType == kElementType_Monster) {
        this->configureNormalMonsterProperty();
    }
}

//获取根据当前关卡csv概率判断生成NormalElement
ElementType GridElementProperty::getRandomElementType()
{
    BarrierFileConfigure *currentBConfigure = DataManager::sharedInstance()->currentBarrierConfigure();
    float randomFloat = DRUtility::randFraction();
    float increasedRate = currentBConfigure->mBowRate;
    if (randomFloat <= increasedRate) {
        return kElementType_Bow;
    }
    increasedRate += currentBConfigure->mSwordRate;
    if (randomFloat <= increasedRate) {
        return kElementType_Sword;
    }
    increasedRate += currentBConfigure->mSheildRate;
    if (randomFloat <= increasedRate) {
        return kElementType_Shield;
    }
    increasedRate += currentBConfigure->mPotionRate;
    if (randomFloat <= increasedRate) {
        return kElementType_Potion;
    }
    increasedRate += currentBConfigure->mCoinRate;
    if (randomFloat <= increasedRate) {
        return kElementType_Coin;
    }
    
    return kElementType_Monster;
}

//生成普通怪
void GridElementProperty::configureNormalMonsterProperty()
{
    //TODO:需要确认普通怪生成逻辑，这里写成固定的
    mMonsterProperty.mType = kBustyType_Common;
    mMonsterProperty.mSkillType = kBossBustyType_None;
    mMonsterProperty.mName = "normal monster";
    mMonsterProperty.mDescription = "This is a test Normal Monster";
    
    GameStatusType *gameStatus = DataManager::sharedInstance()->gameStatus();
    MonsterFileConfigure *mfConfigure = this->getRandomMonster();
    mMonsterProperty.mID = mfConfigure->mBossId;
    mMonsterProperty.mDefence = mfConfigure->mF + mfConfigure->mG*(float)gameStatus->mNumberOfRound;      //defence = f + g * round
    mMonsterProperty.mMaxLife = mfConfigure->mD + mfConfigure->mE*(float)gameStatus->mNumberOfRound;      //life = d + e * round
    mMonsterProperty.mLife = mMonsterProperty.mMaxLife;
    mMonsterProperty.mDamage = mfConfigure->mH + mfConfigure->mI*(float)gameStatus->mNumberOfRound;      //damage = H + I * round
    
}

void GridElementProperty::configureBossProperty()
{    
    this->mType = kElementType_Monster;
    
    GameStatusType *gameStatus = DataManager::sharedInstance()->gameStatus();
    
    BossFileConfigure *bossConfigure = this->getRandomBoss();
    mMonsterProperty.mType = kBustyType_Boss;
    mMonsterProperty.mID = bossConfigure->mBossId;
    
    switch (bossConfigure->mBossId) {
        case 1:{
            mMonsterProperty.mSkillType = kBossBustyType_Chaotic;
            mMonsterProperty.mName = "chaotic";
            mMonsterProperty.mDescription = "chaotic";
            break;
        }
            /*
        case 2:{
            mMonsterProperty.mSkillType = kBossBustyType_Poisonous;
            mMonsterProperty.mName = "Poisonous";
            mMonsterProperty.mDescription = "Poisonous";
            mMonsterProperty.mValidRound=5;
            break;
        }
        case 3:{
            mMonsterProperty.mSkillType = kBossBustyType_Healer;
            mMonsterProperty.mName = "healer";
            mMonsterProperty.mDescription = "healer";
            break;
        }
        case 4:{
            mMonsterProperty.mSkillType = kBossBustyType_Spiky;
            mMonsterProperty.mName = "spiky";
            mMonsterProperty.mDescription = "spiky";
            break;
        }
//        case 5:{
//            mMonsterProperty.mSkillType = kBossBustyType_Acidic;
//            mMonsterProperty.mName = "Acidic";
//            mMonsterProperty.mDescription = "Acidic";
//            break;
//        }
        case 6:{
            mMonsterProperty.mSkillType = kBossBustyType_Vampire;
            mMonsterProperty.mName = "Vampire";
            mMonsterProperty.mDescription = "Vampire";
            break;
        }
        case 7:{
            mMonsterProperty.mSkillType = kBossBustyType_Golden;
            mMonsterProperty.mName = "Golden";
            mMonsterProperty.mDescription = "Golden";
            mMonsterProperty.mValidRound=2;
            break;
        }
//        case 8:{
//            mMonsterProperty.mSkillType = kBossBustyType_Freezing;
//            mMonsterProperty.mName = "Freezing";
//            mMonsterProperty.mDescription = "Freezing";
//            break;
//        }
        case 9:{
            mMonsterProperty.mSkillType = kBossBustyType_Mage;
            mMonsterProperty.mName = "Mage";
            mMonsterProperty.mDescription = "Mage";
            break;
        }
        case 10:{
            mMonsterProperty.mSkillType = kBossBustyType_Corrosive;
            mMonsterProperty.mName = "Corrosive";
            mMonsterProperty.mDescription = "Corrosive";
            break;
        }
//        case 11:{
//            mMonsterProperty.mSkillType = kBossBustyType_Overseer;
//            mMonsterProperty.mName = "Overseer";
//            mMonsterProperty.mDescription = "Overseer";
//            break;
//        }
//        case 12:{
//            mMonsterProperty.mSkillType = kBossBustyType_Flaming;
//            mMonsterProperty.mName = "Flaming";
//            mMonsterProperty.mDescription = "Flaming";
//            break;
//        }
        case 13:{
            mMonsterProperty.mSkillType = kBossBustyType_Trampling;
            mMonsterProperty.mName = "Trampling";
            mMonsterProperty.mDescription = "Trampling";
            break;
        }
        case 14:{
            mMonsterProperty.mSkillType = kBossBustyType_Kamikaze;
            mMonsterProperty.mName = "Kamikaze";
            mMonsterProperty.mDescription = "Kamikaze";
            mMonsterProperty.mValidRound=2;
            break;
        }
             */
        default:{
            mMonsterProperty.mSkillType = kBossBustyType_Chaotic;
            mMonsterProperty.mName = "Chaotic";
            mMonsterProperty.mDescription = "Chaotic";
            break;
        }
    }
    mMonsterProperty.mDefence = bossConfigure->mF + bossConfigure->mG*(float)gameStatus->mNumberOfRound;      //defence = f + g * round
    mMonsterProperty.mMaxLife = bossConfigure->mD + bossConfigure->mE*(float)gameStatus->mNumberOfRound;      //life = d + e * round
    mMonsterProperty.mLife = mMonsterProperty.mMaxLife;
    mMonsterProperty.mDamage = bossConfigure->mH + bossConfigure->mI*(float)gameStatus->mNumberOfRound;      //damage = H + I * round
}

//根据csv文件的概率生成boss配置
BossFileConfigure * GridElementProperty::getRandomBoss()
{
    CCArray *bossConfigures = DataManager::sharedInstance()->bossConfigures();
    
    int bCongfiguresCount = bossConfigures->count();
    float bossRates[bCongfiguresCount];
    
    BossFileConfigure *bossConfigure = NULL;
    CCObject *object = NULL;
    
    float randomFloat = DRUtility::randFraction();
    
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

//MonsterFileConfigure * Grid
MonsterFileConfigure * GridElementProperty::getRandomMonster()
{
    CCArray *monsterConfigures = DataManager::sharedInstance()->monsterConfigures();
    
    int mCongfiguresCount = monsterConfigures->count();
    float monsterRates[mCongfiguresCount];
    
    BossFileConfigure *monsterConfigure = NULL;
    CCObject *object = NULL;
    
    float randomFloat = DRUtility::randFraction();
    
    float previousMonsterRate = 0.0f;
    int i = 0;
    CCARRAY_FOREACH(monsterConfigures, object)
    {
        monsterConfigure = (BossFileConfigure *)object;
        
        monsterRates[i] = previousMonsterRate + monsterConfigure->mBossRate;
        if (randomFloat < monsterRates[i]) {
            return monsterConfigure;
        }
        
        previousMonsterRate = monsterRates[i];
        i++;
    }
    return NULL;
}