#ifndef __OC_BRIDGE_H__
#define __OC_BRIDGE_H__

typedef enum {
    kIOS_PLATFORM_TYPE_unknown=0,
    kIOS_PLATFORM_TYPE_iphone,
    kIOS_PLATFORM_TYPE_ipad,
    kIOS_PLATFORM_TYPE_ipod,
}IOS_PLATFORM_TYPE;

class OCBridge
{
public:
    OCBridge();
    virtual ~OCBridge();
    
    static IOS_PLATFORM_TYPE getPlatformType();
    
private:


private:
};

#endif
