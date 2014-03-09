#ifndef __DR_USERDEFAULT_H__
#define __DR_USERDEFAULT_H__

#include "cocos2d.h"

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

private:
    void writeUserDefault();
    void readUserDefault();

private:
	unsigned int     m_roundCount;
    unsigned int     m_score;
};

#endif // __DR_USERDEFAULT_H__
