
#import "OCUtility.h"
//#import "OCBridge.h"

#define BREAK_IF(cond)  if(cond)break;


@implementation OCUtility

+(IOS_PLATFORM_TYPE)getPlatformType
{
    NSString *deviceType=[UIDevice currentDevice].model;
    if([deviceType rangeOfString:@"iPhone"].location!=NSNotFound){
        return kIOS_PLATFORM_TYPE_iphone;
    }else if ([deviceType rangeOfString:@"iPad"].location!=NSNotFound){
        return kIOS_PLATFORM_TYPE_ipad;
    }else if ([deviceType rangeOfString:@"iPod"].location!=NSNotFound){
        return kIOS_PLATFORM_TYPE_ipod;
    }else{
        return kIOS_PLATFORM_TYPE_unknown;
    }
}

- (void)dealloc {
    
    [super dealloc];
}


@end
