#include "DRUserDefault.h"
#include "DataMangager.h"
#include "WeaponConfigure.h"

static DRUserDefault* m_spUserDefault = NULL;

DRUserDefault::DRUserDefault():
    m_roundCount(0),
    m_score(0),
    m_killMonsterCount(0),
    m_coin(0),
    m_weaponSwitch(false),
    m_weaponPackage(NULL)
{
	
}

DRUserDefault::~DRUserDefault()
{
	
}

DRUserDefault* DRUserDefault::sharedUserDefault()
{
    do{
        if (! m_spUserDefault)
        {
            m_spUserDefault = new DRUserDefault();
            CC_BREAK_IF(!m_spUserDefault);
            m_spUserDefault->readUserDefault();
        }
    }while(0);
    
	return m_spUserDefault;
}

void DRUserDefault::addWeapon(unsigned int pID)
{
    do {
        if (!m_weaponPackage) {
            m_weaponPackage=CCDictionary::create();
            CC_BREAK_IF(!m_weaponPackage);
            m_weaponPackage->retain();
            CCString *key=CCString::createWithFormat("weapon_%02d",pID);
            m_weaponPackage->setObject(CCString::createWithFormat("%d",pID), key->getCString());
        }
    } while (0);
}

void DRUserDefault::flush()
{
    writeUserDefault();
    CCUserDefault::sharedUserDefault()->flush();
}

void DRUserDefault::writeUserDefault()
{
    do{
        CCUserDefault::sharedUserDefault()->setIntegerForKey("round", m_roundCount);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("score", m_score);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("killMonster", m_killMonsterCount);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("coin", m_coin);
        CCUserDefault::sharedUserDefault()->setBoolForKey("weaponSwitch", m_weaponSwitch);
        if (m_weaponPackage) {
            CCDictElement *item=NULL;
            CCDICT_FOREACH(m_weaponPackage, item){
                if (item) {
                    CCString *weaponID=dynamic_cast<CCString *>(item->getObject());
                    CCUserDefault::sharedUserDefault()->setIntegerForKey(item->getStrKey(), weaponID->intValue());
                }
            }
        }
    }while(0);
}

void DRUserDefault::readUserDefault()
{
    do{
        m_weaponSwitch=CCUserDefault::sharedUserDefault()->getBoolForKey("weaponSwitch", false);
        m_coin=CCUserDefault::sharedUserDefault()->getIntegerForKey("coin", 0);
        m_killMonsterCount=CCUserDefault::sharedUserDefault()->getIntegerForKey("killMonster", 0);
        m_score=CCUserDefault::sharedUserDefault()->getIntegerForKey("score", 0);
        m_roundCount=CCUserDefault::sharedUserDefault()->getIntegerForKey("round", 0);
        if (!m_weaponPackage) {
            m_weaponPackage=CCDictionary::create();
            CC_BREAK_IF(!m_weaponPackage);
            m_weaponPackage->retain();
            
            CCArray *weaponConf=DataManager::sharedInstance()->weaponConfigures();
            if (weaponConf && weaponConf->count()) {
                for (int i=0; i<weaponConf->count(); i++) {
                    WeaponConfigure *item=dynamic_cast<WeaponConfigure *>(weaponConf->objectAtIndex(i));
                    CC_BREAK_IF(!item);
                    CCString *key=CCString::createWithFormat("weapon_%02d",item->mWeaponNumber);
                    CC_BREAK_IF(!key);
                    if (CCUserDefault::sharedUserDefault()->getIntegerForKey(key->getCString())>0) {
                        m_weaponPackage->setObject(CCString::createWithFormat("%d",item->mWeaponNumber), key->getCString());
                    }
                }
            }
        }
    }while(0);
}