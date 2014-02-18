#include "BaseScene.h"


bool BaseScene::initWithDelegate(BaseController *pDelegate)
{
	bool tRet = false;
	do{
		CC_BREAK_IF(!pDelegate);
		m_delegate=pDelegate;

		tRet = true;
	}while(0);

	return tRet;
}

void BaseScene::setDelegate(BaseController *pDelegate)
{
	m_delegate=pDelegate;
}