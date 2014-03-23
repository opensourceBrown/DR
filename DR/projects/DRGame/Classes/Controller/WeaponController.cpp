/****************************************************************************
//√ï¬Æ‚Äù‚àö¬†Àù√¶‚Ä∫∆í¬£‚Äì√ï¬ø‚Ä°
****************************************************************************/
#include "WeaponController.h"
#include "DataMangager.h"
#include "DRUserDefault.h"
#include "WeaponConfigure.h"
#include "DRNetworkMangager.h"
#include "MainGameToolBar.h"

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

WeaponConfigure *WeaponController::getWeapon(unsigned int pID)
{
    WeaponConfigure *weapon=NULL;
    do {
        CC_BREAK_IF(!m_weaponPackage);
        for (int i=0; i<m_weaponPackage->count(); i++) {
            WeaponConfigure *item = dynamic_cast<WeaponConfigure *>(m_weaponPackage->objectAtIndex(i));
            CC_BREAK_IF(!item);
            if (item->mWeaponNumber==pID) {
                weapon=item;
            }
        }
    } while (0);
    
    return weapon;
}

void WeaponController::removeWeapon(unsigned int pID)
{
    do {
        CC_BREAK_IF(!m_weaponPackage);
        for (int i=0; i<m_weaponPackage->count(); i++) {
            WeaponConfigure *item = dynamic_cast<WeaponConfigure *>(m_weaponPackage->objectAtIndex(i));
            CC_BREAK_IF(!item);
            if (item->mWeaponNumber==pID) {
                m_weaponPackage->removeObject(item);
                break;
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

void WeaponController::addWeaponToPackage(unsigned int pID)
{
    do {
        if (DRUserDefault::sharedUserDefault()->getWeaponSwitch()) {
            if (!m_weaponPackage) {
                m_weaponPackage=CCArray::create();
                CC_BREAK_IF(!m_weaponPackage);
                m_weaponPackage->retain();
            }
            bool isValid=false;
            CCArray *weaponsConf = DataManager::sharedInstance()->weaponConfigures();
            CC_BREAK_IF(!weaponsConf || weaponsConf->count()==0);
            for (int i=0; i<weaponsConf->count(); i++) {
                WeaponConfigure *weapon=dynamic_cast<WeaponConfigure *>(weaponsConf->objectAtIndex(i));
                CC_BREAK_IF(!weapon);
                if (weapon->mWeaponNumber==pID) {
                    bool isRedundancy=false;
                    for (int j=0; j<m_weaponPackage->count(); j++) {
                        WeaponConfigure *inweapon=dynamic_cast<WeaponConfigure *>(weaponsConf->objectAtIndex(j));
                        CC_BREAK_IF(!inweapon);
                        if (inweapon->mWeaponNumber==pID) {
                            isRedundancy=true;
                            break;
                        }
                    }
                    if (isRedundancy==false) {
                        m_weaponPackage->addObject(weapon);
                        isValid=true;
                    }
                    break;
                }
            }
            
            if (isValid) {
                DRUserDefault::sharedUserDefault()->addWeapon(pID);
                DRUserDefault::sharedUserDefault()->flush();
            }
        }
    }while(0);
}

bool WeaponController::judgeWeaponEnableUpgrade(unsigned int pID)
{
    bool tRet=false;
    do {
        CCString *weaponName=NULL;
        CCArray *weaponsConf = DataManager::sharedInstance()->weaponConfigures();
        CC_BREAK_IF(!weaponsConf || weaponsConf->count()==0);
        
        WeaponConfigure *curWeapon=NULL;
        for (int i=0; i<weaponsConf->count(); i++) {
            WeaponConfigure *weapon=dynamic_cast<WeaponConfigure *>(weaponsConf->objectAtIndex(i));
            CC_BREAK_IF(!weapon);
            if (weapon->mWeaponNumber==pID) {
                weaponName=CCString::createWithFormat("%s",weapon->mName.c_str());
                weaponName->retain();
                curWeapon=weapon;
                break;
            }
        }
        if (weaponName) {
            for (int i=0; i<weaponsConf->count(); i++) {
                WeaponConfigure *weapon=dynamic_cast<WeaponConfigure *>(weaponsConf->objectAtIndex(i));
                CC_BREAK_IF(!weapon);
                if (weapon->mName.compare(weaponName->getCString())==0 && weapon->mLevel==curWeapon->mLevel+1) {
                    tRet=true;
                    break;
                }
            }
        }
        
        CC_SAFE_RELEASE(weaponName);
    } while (0);
    
    return tRet;
}

void WeaponController::updateWeaponPackage(unsigned int pID)
{
    //判断是否满足升级条件，如果满足则进行升级，然后更新toolbar上的武器列表（test）,并同步更新给游戏的玩家的武器数据
    do {
        CC_BREAK_IF(!m_weaponPackage);
        bool enableUpgrade=false;
        CCArray *weaponsConf = DataManager::sharedInstance()->weaponConfigures();
        CC_BREAK_IF(!weaponsConf || weaponsConf->count()==0);
        WeaponConfigure *curWeapon=NULL;
        int curIndex=0;
        for (int i=0; i<weaponsConf->count(); i++) {
            WeaponConfigure *weapon=dynamic_cast<WeaponConfigure *>(weaponsConf->objectAtIndex(i));
            CC_BREAK_IF(!weapon);
            if (weapon->mWeaponNumber==pID) {
                curWeapon=weapon;
                curIndex=i;
                break;
            }
        }
        if (curWeapon) {
            for (int i=0; i<weaponsConf->count(); i++) {
                WeaponConfigure *weapon=dynamic_cast<WeaponConfigure *>(weaponsConf->objectAtIndex(i));
                CC_BREAK_IF(!weapon);
                if (weapon->mName.compare(curWeapon->mName)==0 && weapon->mLevel==curWeapon->mLevel+1) {
                    //判断金币和升级时所需的经验数是否够
                    if (DRUserDefault::sharedUserDefault()->getCoin()>=weapon->mCoin
                        && DRUserDefault::sharedUserDefault()->getScore()>=weapon->mLvExp) {
                        enableUpgrade=true;
                        
                        m_weaponPackage->replaceObjectAtIndex(curIndex, weapon);
                        break;
                    }
                }
            }
        }
        
        if (enableUpgrade) {
            //自动升级当前的武器级别，刷新武器包裹中的武器（ui）
            
        }
        
    } while (0);
}



