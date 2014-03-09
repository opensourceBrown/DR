#include "DRUserDefault.h"

USING_NS_CC;

static DRUserDefault* m_spUserDefault = NULL;
#define TASK_COMPLETE 4

DRUserDefault::DRUserDefault()
{
	
}

DRUserDefault::~DRUserDefault()
{
	
}

DRUserDefault* DRUserDefault::sharedUserDefault()
{
    
	if (! m_spUserDefault)
	{
		m_spUserDefault = new DRUserDefault();
	}
    
	return m_spUserDefault;
}

void DRUserDefault::flush()
{
    
}

void DRUserDefault::writeUserDefault()
{
    
}

void DRUserDefault::readUserDefault()
{
    
}