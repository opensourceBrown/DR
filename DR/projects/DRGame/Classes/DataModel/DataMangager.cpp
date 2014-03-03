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
#include "BossFileConfigure.h"

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
    
    _barrierConfigures = CCArray::create();
    _barrierConfigures->retain();
    
    _bossConfigures = CCArray::create();
    _bossConfigures->retain();
    
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
}

void DataManager::readDataFromCSV()
{
    
    //barrierData
    CCArray *barrierData = DRUtility::readCSVFileWithName("barrierData.csv");
    
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
        _barrierConfigures->addObject(bConfigures);
    }
    
    //bossData
    CCArray *bossData = DRUtility::readCSVFileWithName("bossData.csv");
    CCARRAY_FOREACH(bossData, object)
    {
        dict = (CCDictionary *)object;
        
        BossFileConfigure *bossConfigures = new BossFileConfigure();
        bossConfigures->autorelease();
        bossConfigures->mBossId = ((CCString *)dict->objectForKey("bossid"))->intValue();
        bossConfigures->mD = ((CCString *)dict->objectForKey("D"))->floatValue();
        bossConfigures->mE = ((CCString *)dict->objectForKey("E"))->floatValue();
        bossConfigures->mF = ((CCString *)dict->objectForKey("F"))->floatValue();
        bossConfigures->mG = ((CCString *)dict->objectForKey("G"))->floatValue();
        bossConfigures->mH = ((CCString *)dict->objectForKey("H"))->floatValue();
        bossConfigures->mI = ((CCString *)dict->objectForKey("I"))->floatValue();
        bossConfigures->mBossRate = ((CCString *)dict->objectForKey("bossRate"))->floatValue();
        _bossConfigures->addObject(bossConfigures);
        
    }
}

GridElementProperty* DataManager::getGridElementProperty(unsigned int rIndex,unsigned int vIndex)
{
    
    return NULL;
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

BarrierFileConfigure * DataManager::currentBarrierConfigure()
{
    int barrierId = _gameStatus->mBarrierId;
    cout<<barrierId<<endl;
    
    BarrierFileConfigure *bfConfigure = NULL;
    CCObject *object = NULL;
    CCARRAY_FOREACH(_barrierConfigures, object)
    {
        bfConfigure = (BarrierFileConfigure *)object;
        cout<<bfConfigure->mBarrierId<<endl;
        if (barrierId == bfConfigure->mBarrierId) {
            return bfConfigure;
        }
    }
    return NULL;
}