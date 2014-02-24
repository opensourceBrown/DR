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
#include <list.h>

USING_NS_CC;

class DataManager : public CCObject
{
    
private:
    DataManager(void);
    ~DataManager(void);
    
public:
    static DataManager *sharedInstance(void);
    
    inline GameLayerElement gameLayerElement(void) {
        return _gameLayerElement;
    };
    
    inline list<BlockData> blocks(void) {
        
        return  _blocks;
    };
    
protected:
    GameLayerElement    _gameLayerElement;
    list<BlockData>     _blocks;
};

#endif /* defined(__DRGame__DataMangager__) */