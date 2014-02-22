#ifndef _BASE_CONTROLLER_H_
#define _BASE_CONTROLLER_H_

#include "cocos2d.h"
#include "GameConstant.h"

USING_NS_CC;

class BaseScene;

class BaseController : public CCObject
{
public:
    BaseController();
    ~BaseController();
    
    BaseScene *getScene(){return m_scene;}
    
    
public:
    BaseScene   *m_scene;
};

#endif
