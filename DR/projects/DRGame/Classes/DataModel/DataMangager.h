//
//  DataMangager.h
//  DRGame
//
//  Created by magic on 14-2-18.
//
//

#ifndef __DRGame__DataMangager__
#define __DRGame__DataMangager__

#include <iostream>
#include "cocos2d.h"
#include "DataConstant.h"
#include "GridElementProperty.h"
#include "GameStatusType.h"

USING_NS_CC;

class DataManager : public CCObject
{
    
private:
    DataManager(void);
    ~DataManager(void);
    
    CCDictionary *_savedDict = NULL;
    GameStatusType      *_gameStatus;
    
public:
    static DataManager *sharedInstance(void);
    
    //read and save GridElementProperty
    GridElementProperty *getGridElementProperty(unsigned int rIndex,unsigned int vIndex);
    CCDictionary * getGridElements(void);
    bool saveGridElements(void);
    
    //Game Global status
    inline GameStatusType      *gameStatus() { return _gameStatus; };
    
};

#endif /* defined(__DRGame__DataMangager__) */