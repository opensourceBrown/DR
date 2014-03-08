//
//  DataMangager.cpp
//  DRGame
//
//  Created by magic on 14-2-18.
//
//

#include "DataMangager.h"
#include "XMLParser.h"
#include "DRUtility.h"
#include "WeaponConfigure.h"

#define GRID_ELEMENT_FILE_NAME  "gElementFileName.plist"

static DataManager *__sharedInstane = NULL;

DataManager * DataManager::sharedInstance(void)
{
    if (__sharedInstane == NULL) {
        __sharedInstane = new DataManager();
    }
    
    return __sharedInstane;
}

DataManager::DataManager()
{
    _gameStatus = new GameStatusType();
    _gameStatus->mNumberOfRound = 0;
    _gameStatus->mFlag = -1;
    _gameStatus->mBarrierId = 1;
    _gameStatus->mLife = 0;
    _gameStatus->mMaxLife = 0;
    
    _currentBarrierConfigure = NULL;
    
    _barrierConfigures = CCArray::create();
    _barrierConfigures->retain();
    
    _bossConfigures = CCArray::create();
    _bossConfigures->retain();
    
    _monsterConfigures = CCArray::create();
    _monsterConfigures->retain();
    
    _weaponConfigures = CCArray::create();
    _weaponConfigures->retain();
    
    this->readDataFromCSV();
}

DataManager::~DataManager()
{
    if (_savedDict != NULL) {
        _savedDict->release();
        _savedDict = NULL;
    }
    
    delete _gameStatus;
    _barrierConfigures->release();
    _bossConfigures->release();
    _monsterConfigures->release();
    _weaponConfigures->release();
}

void DataManager::readDataFromCSV()
{
    
    //barrierData
    CCArray *barrierData = DRUtility::readCSVFileWithName("barrierData.csv", true);
    
    CCDictionary *dict = NULL;
    CCObject *object = NULL;
    CCARRAY_FOREACH(barrierData, object)
    {
        dict = (CCDictionary *)object;
        
        BarrierFileConfigure *bConfigures = new BarrierFileConfigure();
        bConfigures->autorelease();
        bConfigures->mBarrierId = ((CCString *)dict->objectForKey("barrierid"))->intValue();
        bConfigures->mA = ((CCString *)dict->objectForKey("A"))->floatValue();
        bConfigures->mB = ((CCString *)dict->objectForKey("B"))->floatValue();
        bConfigures->mC = ((CCString *)dict->objectForKey("C"))->floatValue();
        bConfigures->mBowRate = ((CCString *)dict->objectForKey("bowRate"))->floatValue();
        bConfigures->mSwordRate = ((CCString *)dict->objectForKey("swordRate"))->floatValue();
        bConfigures->mMonsterRate = ((CCString *)dict->objectForKey("monsterRate"))->floatValue();
        bConfigures->mSheildRate = ((CCString *)dict->objectForKey("sheildRate"))->floatValue();
        bConfigures->mPotionRate = ((CCString *)dict->objectForKey("potionRate"))->floatValue();
        bConfigures->mCoinRate = ((CCString *)dict->objectForKey("coinRate"))->floatValue();
        _barrierConfigures->addObject(bConfigures);
    }
    
    //bossData
    CCArray *bossData = DRUtility::readCSVFileWithName("bossData.csv", true);
    CCARRAY_FOREACH(bossData, object)
    {
        dict = (CCDictionary *)object;
        
        BossFileConfigure *bossConfigure = new BossFileConfigure();
        bossConfigure->autorelease();
        bossConfigure->mBossId = ((CCString *)dict->objectForKey("bossid"))->intValue();
        bossConfigure->mD = ((CCString *)dict->objectForKey("D"))->floatValue();
        bossConfigure->mE = ((CCString *)dict->objectForKey("E"))->floatValue();
        bossConfigure->mF = ((CCString *)dict->objectForKey("F"))->floatValue();
        bossConfigure->mG = ((CCString *)dict->objectForKey("G"))->floatValue();
        bossConfigure->mH = ((CCString *)dict->objectForKey("H"))->floatValue();
        bossConfigure->mI = ((CCString *)dict->objectForKey("I"))->floatValue();
        bossConfigure->mBossRate = ((CCString *)dict->objectForKey("bossRate"))->floatValue();
        _bossConfigures->addObject(bossConfigure);
        
    }
    
    //monsterData
    CCArray *monsterData = DRUtility::readCSVFileWithName("monsterData.csv", true);
    CCARRAY_FOREACH(monsterData, object)
    {
        dict = (CCDictionary *)object;
        
        MonsterFileConfigure *monsterConfigure = new MonsterFileConfigure();
        monsterConfigure->autorelease();
        monsterConfigure->mBossId = ((CCString *)dict->objectForKey("monsterid"))->intValue();
        monsterConfigure->mD = ((CCString *)dict->objectForKey("D"))->floatValue();
        monsterConfigure->mE = ((CCString *)dict->objectForKey("E"))->floatValue();
        monsterConfigure->mF = ((CCString *)dict->objectForKey("F"))->floatValue();
        monsterConfigure->mG = ((CCString *)dict->objectForKey("G"))->floatValue();
        monsterConfigure->mH = ((CCString *)dict->objectForKey("H"))->floatValue();
        monsterConfigure->mI = ((CCString *)dict->objectForKey("I"))->floatValue();
        monsterConfigure->mBossRate = ((CCString *)dict->objectForKey("monsterRate"))->floatValue();
        _monsterConfigures->addObject(monsterConfigure);
    }
    
    //weaponData
    CCArray *weaponData = DRUtility::readCSVFileWithName("weaponData.csv", false);
    CCARRAY_FOREACH(weaponData, object)
    {
        dict = (CCDictionary *)object;
        
        WeaponConfigure *weaponConfigure = new WeaponConfigure();
        weaponConfigure->autorelease();
        weaponConfigure->mWeaponNumber = ((CCString *)dict->objectForKey("No"))->intValue();
        weaponConfigure->mWeaponDamage = ((CCString *)dict->objectForKey("WeaponDamage"))->intValue();
        weaponConfigure->mName = ((CCString *)dict->objectForKey("Name"))->getCString();
        weaponConfigure->mLevel = ((CCString *)dict->objectForKey("Lv"))->intValue();
        weaponConfigure->mDefencePerShield = ((CCString *)dict->objectForKey("DefencePerShield"))->floatValue();
        weaponConfigure->mMaxSheild = ((CCString *)dict->objectForKey("MaxSheild"))->floatValue();
        weaponConfigure->mHealthPerPotion = ((CCString *)dict->objectForKey("HealthPerPotion"))->floatValue();
        weaponConfigure->mBasicDamage = ((CCString *)dict->objectForKey("BasicDamage"))->floatValue();
        weaponConfigure->mWeaponDamage = ((CCString *)dict->objectForKey("WeaponDamage"))->floatValue();
        weaponConfigure->mLeech = ((CCString *)dict->objectForKey("Leech"))->floatValue();
        weaponConfigure->mCriticalDamageRate = ((CCString *)dict->objectForKey("CriticalDamageRate"))->floatValue();
        weaponConfigure->mCoin = ((CCString *)dict->objectForKey("Coin"))->floatValue();
        weaponConfigure->mPayCoin = ((CCString *)dict->objectForKey("PayCoin"))->floatValue();
        weaponConfigure->mExp = ((CCString *)dict->objectForKey("Exp"))->floatValue();
        weaponConfigure->mLvExp = ((CCString *)dict->objectForKey("LvExp"))->floatValue();
        weaponConfigure->mLvUpWeapon = ((CCString *)dict->objectForKey("LvUpWeapon"))->floatValue();
        _weaponConfigures->addObject(weaponConfigure);
    }
}

CCDictionary * DataManager::getGridElements(void)
{
    
    if (_savedDict == NULL) {
        CCDictionary *dict = NULL;
        std::string fileName = CCFileUtils::sharedFileUtils()->getWritablePath()+GRID_ELEMENT_FILE_NAME;
        if (CCFileUtils::sharedFileUtils()->isFileExist(fileName)) {
            dict = CCDictionary::createWithContentsOfFile(fileName.c_str());
        }
        if (dict == NULL) {
            _savedDict = CCDictionary::create();
        } else {
            _savedDict = dict;
        }
        _savedDict->retain();
    }
    return _savedDict;
}

bool DataManager::saveGridElements(void)
{
    bool isSuccess = false;
    if (_savedDict) {
        std::string fileName = CCFileUtils::sharedFileUtils()->getWritablePath()+GRID_ELEMENT_FILE_NAME;
        isSuccess = _savedDict->writeToFile(fileName.c_str());
    }
    return isSuccess;
}

//此处会频繁地调用，故设置成全局属性，若关卡id改变，则需要将_currentBarrierConfigure设置为NULL
BarrierFileConfigure * DataManager::currentBarrierConfigure()
{
    if (_currentBarrierConfigure == NULL) {
        int barrierId = _gameStatus->mBarrierId;
        
        BarrierFileConfigure *bfConfigure = NULL;
        CCObject *object = NULL;
        CCARRAY_FOREACH(_barrierConfigures, object)
        {
            bfConfigure = (BarrierFileConfigure *)object;
            if (barrierId == bfConfigure->mBarrierId) {
                return bfConfigure;
            }
        }
    }
    return _currentBarrierConfigure;
}