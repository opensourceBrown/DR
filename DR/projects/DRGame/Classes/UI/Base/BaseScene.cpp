#include "BaseScene.h"
#include "BaseController.h"


BaseScene::BaseScene():
    m_delegate(NULL)
{
    
}



void BaseScene::setDelegate(BaseController *pDelegate)
{
	m_delegate=pDelegate;
}