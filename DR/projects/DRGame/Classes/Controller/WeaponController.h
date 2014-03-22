#ifndef _WEAPON_CONTROLLER_H_
#define _WEAPON_CONTROLLER_H_


#include "BaseController.h"
#include "cocos2d.h"

class DRNetworkMangager;
class MainGameController;

class WeaponController : public BaseController
{
public:
    WeaponController();
    ~WeaponController();
    
    static WeaponController *shareInstance();
    
    void resetWeaponPackage();
    CCArray *getWeaponPackage(){return m_weaponPackage;}
    
    void updateWeaponPackage(unsigned int pID);

private:
    bool init();
    void readWeaponConf();              //读取武器包
private:
    CCArray     *m_weaponPackage;
};

#endif
