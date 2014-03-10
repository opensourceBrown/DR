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
using namespace cocos2d;

class DRUtility : cocos2d::CCObject
{
public:
    static string getFileByName(string pFileName);
    static bool saveFile(char *pContent, string pFileName);
    
    static CCDictionary* loadDictFromEncFile(char* fileName);
    static CCString* getCCStringWithInt(int intValue);
    static CCArray * readCSVFileWithName(const char *fileName, bool byCol);
    
    static int randn(int n);            //generate [0,n-1] uniform distribution random int number
    static float randFraction();        //generate [0,1] float number
    
    //iPad Adaptation
    static bool isiPadAdaptation();
private:
    
    
};

#endif /* defined(__DRGame__Utility__) */
