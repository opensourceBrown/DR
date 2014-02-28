//
//  BossFileConfigure.h
//  DRGame
//
//  Created by magic on 14-2-28.
//
//

#ifndef __DRGame__BossFileConfigure__
#define __DRGame__BossFileConfigure__

#include <iostream>

#include "cocos2d.h"

USING_NS_CC;

class BossFileConfigure : public CCObject
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

#endif /* defined(__DRGame__BossFileConfigure__) */
