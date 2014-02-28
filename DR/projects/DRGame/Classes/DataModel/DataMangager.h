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
#include "BarrierFileConfigure.h"

USING_NS_CC;

class DataManager : public CCObject
{
    
private:
    DataManager(void);
    ~DataManager(void);
    
    CCDictionary *_savedDict = NULL;
    GameStatusType      *_gameStatus;
    CCArray             *_barrierConfigures;
    CCArray             *_bossConfigures;
    
public:
    static DataManager *sharedInstance(void);
    
    //read and save GridElementProperty
    GridElementProperty *getGridElementProperty(unsigned int rIndex,unsigned int vIndex);
    CCDictionary * getGridElements(void);
    bool saveGridElements(void);
    
    //Game Global status
    inline GameStatusType      *gameStatus() { return _gameStatus; };
    inline CCArray             *barrierConfigures() { return _barrierConfigures; };
    CCArray                    *bossConfigures();
};

#endif /* defined(__DRGame__DataMangager__) */