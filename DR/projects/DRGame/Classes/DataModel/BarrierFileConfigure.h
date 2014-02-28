//
//  BarrierFileConfigure.h
//  DRGame
//
//  Created by magic on 14-2-28.
//
//

#ifndef __DRGame__BarrierFileConfigure__
#define __DRGame__BarrierFileConfigure__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class BarrierFileConfigure:public CCObject
{
public:
    unsigned int mBarrierId;
    float        mA;
    float        mB;
    float        mC;
};

#endif /* defined(__DRGame__BarrierFileConfigure__) */
