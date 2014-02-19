//
//  DataMangager.h
//  DRGame
//
//  Created by magic on 14-2-18.
//
//

#ifndef __DRGame__DataMangager__
#define __DRGame__DataMangager__

#include <iostream>

#endif /* defined(__DRGame__DataMangager__) */


class DataManager
{
    
private:
    DataManager(void);
    ~DataManager(void);
    
public:
    static DataManager *sharedInstance(void);
};