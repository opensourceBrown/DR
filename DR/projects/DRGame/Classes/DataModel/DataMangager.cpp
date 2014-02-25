//
//  DataMangager.cpp
//  DRGame
//
//  Created by magic on 14-2-18.
//
//

#include "DataMangager.h"
#include "XMLParser.h"

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
    
}

DataManager::~DataManager()
{
    if (_savedDict != NULL) {
        _savedDict->release();
        _savedDict = NULL;
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
