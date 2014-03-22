/****************************************************************************
//√ï¬Æ‚Äù‚àö¬†Àù√¶‚Ä∫∆í¬£‚Äì√ï¬ø‚Ä°
****************************************************************************/
#include "WeaponController.h"
#include "DataMangager.h"
#include "DRUserDefault.h"
#include "WeaponConfigure.h"
#include "DRNetworkMangager.h"

static WeaponController *instance=NULL;

WeaponController::WeaponController():
    m_weaponPackage(NULL)
{
    
}

WeaponController::~WeaponController()
{
    CC_SAFE_RELEASE(m_weaponPackage);
}

WeaponController *WeaponController::shareInstance()
{
    if (instance==NULL) {
        instance=new WeaponController();
    }
    
    return instance;
}

bool WeaponController::init()
{
    bool tRet=false;
    do {
        CC_BREAK_IF(!instance->init());
        m_weaponPackage=CCArray::create();
        CC_BREAK_IF(!m_weaponPackage);
        m_weaponPackage->retain();
        
        DRNetworkManager::sharedInstance()->requestWeaponSwitch(this);              //请求武器的开关：后台控制
        tRet=true;
    } while (0);
    return tRet;
}

void WeaponController::readWeaponConf()
{
    do {
        if (DRUserDefault::sharedUserDefault()->getWeaponSwitch()) {
            if (!m_weaponPackage) {
                m_weaponPackage=CCArray::create();
                CC_BREAK_IF(!m_weaponPackage);
                m_weaponPackage->retain();
            }
            CCArray *weapons = DataManager::sharedInstance()->weaponConfigures();
            CC_BREAK_IF(!weapons || weapons->count()==0);
            
            //将可以拥有的武器放入到武器包中
            CCDictionary *weaponDic=DRUserDefault::sharedUserDefault()->getWeaponPackage();
            CC_BREAK_IF(!weaponDic);
            CCDictElement *item=NULL;
            CCDICT_FOREACH(weaponDic, item){
                if (item) {
                    CCString *weaponID=dynamic_cast<CCString *>(item->getObject());
                    CC_BREAK_IF(!weaponID);
                    
                    CCArray *weaponConf=DataManager::sharedInstance()->weaponConfigures();
                    CC_BREAK_IF(!weaponConf || weaponConf->count()==0);
                    for (int i=0; i<weaponConf->count(); i++) {
                        WeaponConfigure *weapon=dynamic_cast<WeaponConfigure *>(weaponConf->objectAtIndex(i));
                        CC_BREAK_IF(weapon);
                        if (weapon->mWeaponNumber==weaponID->intValue()) {
                            m_weaponPackage->addObject(weapon);
                            break;
                        }
                    }
                }
            }
        }
    } while (0);
}

void WeaponController::resetWeaponPackage()
{
    do {
        CC_BREAK_IF(!m_weaponPackage);
        m_weaponPackage->removeAllObjects();
    } while (0);
}

void WeaponController::updateWeaponPackage(unsigned int pID)
{
    //判断是否满足升级条件，如果满足则进行升级，然后更新toolbar上的武器列表（test）,并同步更新给游戏的玩家的武器数据
    do {
        CC_BREAK_IF(!m_weaponPackage);
        
    } while (0);
}



