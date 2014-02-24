//
//  GridElementProperty.h
//  DRGame
//
//  Created by Magic Song on 14-2-24.
//
//

#ifndef __DRGame__GridElementProperty__
#define __DRGame__GridElementProperty__

#include "cocos2d.h"
#include "DataConstant.h"

USING_NS_CC;

class GridElementProperty : public CCObject {

public:
    GridElementProperty();
    ~GridElementProperty();
    
    GIRDCELL_INDEX          mIndex;             //索引
    ElementType             mType;              //cell对应的类型：怪、盾、、、、、
    unsigned int            mID;                //怪id
    
    void init(){
        mIndex.rIndex=0;
        mIndex.vIndex=0;
        mType=kElementType_Coin;
        mID=0;
    }
};


#endif /* defined(__DRGame__GridElementProperty__) */
