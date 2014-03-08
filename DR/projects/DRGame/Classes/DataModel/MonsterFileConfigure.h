//
//  MonsterFileConfigure.h
//  DRGame
//
//  Created by magic on 14-3-8.
//
//

#ifndef __DRGame__MonsterFileConfigure__
#define __DRGame__MonsterFileConfigure__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class MonsterFileConfigure : public CCObject
{
public:
    unsigned int mBossId;
    float       mBossRate;
    float       mD;
    float       mE;
    float       mF;
    float       mG;
    float       mH;
    float       mI;
};

#endif /* defined(__DRGame__MonsterFileConfigure__) */
