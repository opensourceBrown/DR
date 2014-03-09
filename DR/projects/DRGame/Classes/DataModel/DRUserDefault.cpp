#include "DRUserDefault.h"

USING_NS_CC;

static DRUserDefault* m_spUserDefault = NULL;

DRUserDefault::DRUserDefault():
    m_roundCount(0),
    m_score(0),
    m_killMonsterCount(0),
    m_coin(0),
    m_weaponSwitch(false)
{
	readUserDefault();
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
        }
    }while(0);
    
	return m_spUserDefault;
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
    }while(0);
}