#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "cocos2d.h"
#include "BaseController.h"
#include "GameConstant.h"

USING_NS_CC;

class BaseScene : public cocos2d::CCScene
{

public:
	BaseScene(){}
	~BaseScene(){}

	bool initWithDelegate(BaseController *pDelegate);

private:
	BaseController		*m_delegate;
};
#endif
