#ifndef _GENERAL_DATAMODEL_H_
#define _GENERAL_DATAMODEL_H_

#include "cocos2d.h"
#include "GameConstant.h"
#include "DataConstant.h"

USING_NS_CC;

//定义基本数据模型
//代表生成的一个消除元素对应的数据

class GeneralDataModel : public CCObject
{
public:
    GeneralDataModel();
    ~GeneralDataModel();
    
    inline void setElementType(ElementType eType) { _elementType = eType;}
    inline ElementType elementType(void) { return _elementType; }        //游戏消除元素类型
    
    //elementType为kElementType_Monster时，以下数据有效
    inline void setAttackPower(int attackPower) { _attackPower = attackPower; }
    inline int AttackPower(void) { return _attackPower; }             //怪物攻击力
    
    inline void setDefencePower(int defencePower) { _defencePower = defencePower; }
    inline int DefencePower(void) { return _defencePower; }           //怪物防御力
    
    inline void setBustyType(BustyType bustyType) { _bustyType = bustyType; }
    inline BustyType bustyType(void){ return _bustyType; }            //怪物类型(boss or 普通怪)
    
protected:
    ElementType _elementType;
    int         _attackPower;
    int         _defencePower;
    BustyType   _bustyType;
};

#endif
