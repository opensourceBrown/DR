//
//  DataMangager.cpp
//  DRGame
//
//  Created by magic on 14-2-18.
//
//

#include "DataMangager.h"
#include "XMLParser.h"

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
    
}
