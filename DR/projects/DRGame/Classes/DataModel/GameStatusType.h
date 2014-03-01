//
//  GameStatusType.h
//  DRGame
//
//  Created by magic on 14-2-26.
//
//

#ifndef __DRGame__GameStatusType__
#define __DRGame__GameStatusType__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class GameStatusType:public CCObject
{
public:
    int mNumberOfRound;          //回合数
    int mBarrierId;              //current barrier
    int mFlag;                   //to calculate param
    int mLife;                   //rest of life
    int mMaxLife;                //Max life
};

#endif /* defined(__DRGame__GameStatusType__) */
