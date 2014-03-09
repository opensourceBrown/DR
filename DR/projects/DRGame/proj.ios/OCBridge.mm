
#import "OCBridge.h"
#import "OCUtility.h"
#ifdef PLATFORM_IOS

#endif

#define BREAK_IF(cond)  if(cond)break;


OCBridge::OCBridge()
{
    
}

OCBridge::~OCBridge()
{
}

IOS_PLATFORM_TYPE OCBridge::getPlatformType()
{
    return [OCUtility getPlatformType];
}

