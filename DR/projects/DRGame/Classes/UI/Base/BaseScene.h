#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "cocos2d.h"
#include "GameConstant.h"

USING_NS_CC;

class BaseController;

class BaseScene : public cocos2d::CCScene
{

public:
	BaseScene();
	~BaseScene(){}
    
    
    
    void setDelegate(BaseController *pDelegate);
    BaseController *getDelegate(){return m_delegate;}

public:
	BaseController		*m_delegate;
};
#endif
