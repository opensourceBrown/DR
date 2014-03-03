//
//  GridElementProperty.h
//  DRGame
//
//  Created by Magic Song on 14-2-24.
//
//

#ifndef __DRGame__GridElementProperty__
#define __DRGame__GridElementProperty__

#include "cocos2d.h"
#include "DataConstant.h"
#include "BossFileConfigure.h"

USING_NS_CC;

class GridElementProperty : public CCObject {

public:
    GridElementProperty();
    ~GridElementProperty();
    
    GIRDCELL_INDEX          mIndex;
    ElementType             mType;              //monster,sword,shield,Potion and so on
    unsigned int            mID;                //boss id, 0 is normal
    BustyProperty           mMonsterProperty;
    
    void init(){
        mIndex.rIndex=0;
        mIndex.vIndex=0;
        mType=kElementType_Coin;
        mID=0;
        
        m_status=false;
        
        mMonsterProperty.mType = kBustyType_Common;
        mMonsterProperty.mSkillType = kBossBustyType_Chaotic;
        mMonsterProperty.mID = 0;
        mMonsterProperty.mName = "name";
        mMonsterProperty.mDescription = "Description";
        mMonsterProperty.mDefence = 0;
        mMonsterProperty.mLife = 0;
        mMonsterProperty.mMaxLife = 0;
        mMonsterProperty.mDamage = 0;
    }
    
    void generateGridElementDataByCSV();
    void saveToDictionary(CCDictionary *dict);   //save to the Dictionary which parses in
    
    bool canbeDestroyed();      //when monster`s life>0, can not be destroyed
    
    void setStatus(bool pStatus){m_status=pStatus;}
    bool getStatus(){return m_status;}
    
private:
    void configureNormalElementProperty();  //element except boss
    void configureNormalMonsterProperty();  //normal monster
    void configureBossProperty();           //boss
    BossFileConfigure *getRandomBoss();   //get the boss according to rate;
    
private:
    bool m_status;                          //true:cleared    false:uncleared
};


#endif /* defined(__DRGame__GridElementProperty__) */
