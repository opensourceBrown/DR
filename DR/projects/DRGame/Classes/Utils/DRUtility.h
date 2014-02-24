//
//  Utility.h
//  DRGame
//
//  Created by Magic Song on 14-2-20.
//
//

#ifndef __DRGame__Utility__
#define __DRGame__Utility__

#include <iostream>
#include <stdio.h>
#include "cocos2d.h"

using namespace std;

class DRUtility : cocos2d::CCObject
{
public:
    static string getFileByName(string pFileName);
    static bool saveFile(char *pContent, string pFileName);
    
    static cocos2d::CCDictionary* loadDictFromEncFile(char* fileName);
    
private:
    
    
};

#endif /* defined(__DRGame__Utility__) */
