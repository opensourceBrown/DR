

#ifndef __DRGame__WeaponConfigure__
#define __DRGame__WeaponConfigure__

#include "cocos2d.h"
//#include <iostream>

USING_NS_CC;
//using namespace std;

class WeaponConfigure : public CCObject
{
public:
    int     mWeaponNumber;
    std::string  mName;
    int     mLevel;
    float   mDefencePerShield;
    float   mMaxSheild;
    float   mHealthPerPotion;
    float   mBasicDamage;
    float   mWeaponDamage;
    float   mLeech;
    float   mCriticalDamageRate;
    float   mCoin;
    float   mPayCoin;
    float   mExp;
    float   mLvExp;
    float   mLvUpWeapon;
private:
    
};

#endif /* defined(__DRGame__WeaponConfigure__) */
