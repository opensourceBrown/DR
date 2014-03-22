#ifndef __DR_USERDEFAULT_H__
#define __DR_USERDEFAULT_H__

#include "cocos2d.h"

USING_NS_CC;

class DRUserDefault
{
public:
    DRUserDefault();
	virtual ~DRUserDefault();
    
    static DRUserDefault* sharedUserDefault();
    void flush();               //save data
    
    //round
    void setRoundCount(unsigned int pCount){m_roundCount=pCount;}
    unsigned int getRoundCount(){return m_roundCount;}
    
    //score
    void setScore(unsigned int pScore){m_score=pScore;}
    unsigned int getScore(){return m_score;}
    
    //monster
    void setKillMonsterCount(unsigned int pCount){m_killMonsterCount=pCount;}
    unsigned int getKillMonsterCount(){return m_killMonsterCount;}
    
    //coin
    void setCoin(unsigned int pCount){m_coin=pCount;}
    unsigned int getCoin(){return m_coin;}
    
    //weapon
    void setWeaponSwitch(bool pSwitch){m_weaponSwitch=pSwitch;}
    bool getWeaponSwitch(){return m_weaponSwitch;}
    void addWeapon(unsigned int pID);
    CCDictionary *getWeaponPackage(){return m_weaponPackage;}

private:
    void writeUserDefault();
    void readUserDefault();

private:
	unsigned int     m_roundCount;
    unsigned int     m_score;
    unsigned int     m_killMonsterCount;
    unsigned int     m_coin;
    
    bool             m_weaponSwitch;
    CCDictionary     *m_weaponPackage;
};

#endif // __DR_USERDEFAULT_H__
