//
//  GridElementProperty.cpp
//  DRGame
//
//  Created by Magic Song on 14-2-24.
//
//

#include "GridElementProperty.h"
#include "DRUtility.h"
#include "CSVParser.h"

GridElementProperty::GridElementProperty()
{
    
}

GridElementProperty::~GridElementProperty()
{
    
}

void GridElementProperty::generateGridElementDataByCSV()
{
        CSVParser *csvParser = new CSVParser();
        csvParser->openFile("testdata.csv");

        CCArray      *dataArray = CCArray::create();
        CCArray      *keys = CCArray::create();
        CCDictionary *dictionary;
        string strLine = "";
        for (int i = 0; i < csvParser->getRows(); i++) {
            for (int j = 0; j < csvParser->getCols(); j++) {
                CCString *string = CCString::create(csvParser->getData(i, j));
                if (i == 0) {
                    keys->addObject(string);
                } else {
                    if (j==0) {
                        dictionary = CCDictionary::create();
                    }
                    CCString *strKey = (CCString *)keys->objectAtIndex(j);
                    dictionary->setObject(string, strKey->getCString());
                    if (j== csvParser->getCols()-1) {
                        dataArray->addObject(dictionary);
                    }
                }
            }
        }
    //
    //        CCArray *allKeys = dictionary->allKeys();
    //        for (int i = 0; i < allKeys->count(); i++) {
    //            CCString *key = (CCString *)allKeys->objectAtIndex(i);
    //            cout<<"key=" + string(key->getCString())<<endl;
    //        }
    //
    //        CCDictionary *dict = NULL;
    //        CCObject *object = NULL;
    //        CCDictElement *dElement = NULL;
    //        CCARRAY_FOREACH(dataArray, object)
    //        {
    //            dict = (CCDictionary *)object;
    //
    //            CCDICT_FOREACH(dict, dElement)
    //            {
    //                string key = dElement->getStrKey();
    //                CCString *value = (CCString *)dElement->getObject();
    //                cout<<"key="+key + " ------ value=" + value->getCString()<<endl;
    //            }
    //        }
    //        delete csvParser;
}

void GridElementProperty::saveToDictionary(CCDictionary *dict)
{
    stringstream strStream;
    strStream << mIndex.rIndex << "_" << mIndex.vIndex;
    
    CCDictionary *gridDict = new CCDictionary();
    
    gridDict->setObject(DRUtility::getCCStringWithInt(mType), "mType");
    gridDict->setObject(DRUtility::getCCStringWithInt(mID), "mID");
    gridDict->setObject(DRUtility::getCCStringWithInt(mIndex.rIndex), "rIndex");
    gridDict->setObject(DRUtility::getCCStringWithInt(mIndex.vIndex), "vIndex");
    dict->setObject(gridDict, strStream.str());
    gridDict->autorelease();
}

bool GridElementProperty::canbeDestroyed()
{
    return mMonsterProperty.mLife <= 0;
}
