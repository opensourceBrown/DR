
#include "DRNetworkMangager.h"
#include "WeaponController.h"
#include "DRUserDefault.h"

//#define WEAPON_SWITCH   0

static DRNetworkManager *__sharedInstane = NULL;

DRNetworkManager::DRNetworkManager()
{
    
}

DRNetworkManager::~DRNetworkManager()
{
    
}

DRNetworkManager * DRNetworkManager::sharedInstance(void)
{
    if (__sharedInstane == NULL) {
        __sharedInstane = new DRNetworkManager();
    }
    
    return __sharedInstane;
}

void DRNetworkManager::requestWeaponSwitch(WeaponController *pDelegat)
{
    //请求武器的开关，请求回来后写入到userdefault中
    
    
    //test
    //DRUserDefault::sharedUserDefault()->setWeaponSwitch(WEAPON_SWITCH);
}