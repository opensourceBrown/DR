
#ifndef __NETWORK_MANAGER__
#define __NETWORK_MANAGER__

#include "cocos2d.h"

USING_NS_CC;

class WeaponController;

class DRNetworkManager : public CCObject
{
    
private:
    DRNetworkManager(void);
    ~DRNetworkManager(void);
    
public:
    static DRNetworkManager *sharedInstance(void);
    
    void requestWeaponSwitch(WeaponController *pDelegat);
private:
    
};

#endif /* defined(__DRGame__DataMangager__) */