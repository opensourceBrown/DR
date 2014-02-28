//
//  Utility.cpp
//  DRGame
//
//  Created by Magic Song on 14-2-20.
//
//

#include "DRUtility.h"
#include "XMLParser.h"
#include "CSVParser.h"

using namespace cocos2d;

string DRUtility::getFileByName(string pFileName)
{
    //第一先获取文件的路径
    
    string path = CCFileUtils::sharedFileUtils()->getWritablePath() + pFileName;
    CCLOG("path = %s",path.c_str());
    
    //创建一个文件指针
    FILE* file = fopen(path.c_str(), "r");
    
    if (file) {
        char* buf;  //要获取的字符串
        int len;    //获取的长度
        /*获取长度*/
        fseek(file, 0, SEEK_END);   //移到尾部
        len = ftell(file);          //提取长度
        rewind(file);               //回归原位
        CCLOG("count the file content len = %d",len);
        //分配buf空间
        buf = (char*)malloc(sizeof(char) * len + 1);
        if (!buf) {
            CCLOG("malloc space is not enough.");
            return NULL;
        }
        
        //读取文件
        //读取进的buf，单位大小，长度，文件指针
        int rLen = fread(buf, sizeof(char), len, file);
        buf[rLen] = '\0';
        CCLOG("has read Length = %d",rLen);
        CCLOG("has read content = %s",buf);
        
        string result = buf;
        fclose(file);
        free(buf);
        return result;
    }
    else
        CCLOG("open file error.");
    
    return NULL;
}

bool DRUtility::saveFile(char *pContent, string pFileName)
{
    //第一获取储存的文件路径
    string path = CCFileUtils::sharedFileUtils()->getWritablePath() + pFileName;
    CCLOG("wanna save file path = %s",path.c_str());
    
    //创建一个文件指针
    //路径、模式
    FILE* file = fopen(path.c_str(), "w");
    if (file) {
        fputs(pContent, file);
        fclose(file);
    }
    else
        CCLOG("save file error.");
    
    return false;
}

CCDictionary* DRUtility::loadDictFromEncFile(char* fileName)
{
	if (!fileName)
	{
		return NULL;
	}
    
	CCDictionary* dict = NULL;
    
    XMLParser* parser = new XMLParser;
    dict = parser->dictionaryWithXmlData(fileName);
    delete(parser);
    
	return dict;
}

CCString* DRUtility::getCCStringWithInt(int intValue)
{
    CCString *strObjID = new CCString();
    strObjID->autorelease();
    strObjID->initWithFormat("%d", intValue);
    return strObjID;
}

CCArray * DRUtility::readCSVFileWithName(const char *fileName)
{
    cout<<fileName;
    CSVParser *csvParser = new CSVParser();
    csvParser->openFile(fileName);
    
    CCArray      *dataArray = CCArray::create();
    CCArray      *keys = CCArray::create();
    CCDictionary *dictionary;
    string strLine = "";
    
    for (int i = 0; i < csvParser->getCols(); i++) {
        for (int j = 0; j < csvParser->getRows(); j++) {
            CCString *string = CCString::create(csvParser->getData(j, i));
            if (i == 0) {
                keys->addObject(string);
            } else {
                if (i==1) {
                    dictionary = CCDictionary::create();
                }
                CCString *strKey = (CCString *)keys->objectAtIndex(j);
                dictionary->setObject(string, strKey->getCString());
                if (i== csvParser->getCols()-1) {
                    dataArray->addObject(dictionary);
                }
            }
        }
    }

    CCArray *allKeys = dictionary->allKeys();
    for (int i = 0; i < allKeys->count(); i++) {
        CCString *key = (CCString *)allKeys->objectAtIndex(i);
        cout<<"key=" + string(key->getCString())<<endl;
    }

    CCDictionary *dict = NULL;
    CCObject *object = NULL;
    CCDictElement *dElement = NULL;
    CCARRAY_FOREACH(dataArray, object)
    {
        dict = (CCDictionary *)object;

        CCDICT_FOREACH(dict, dElement)
        {
            string key = dElement->getStrKey();
            CCString *value = (CCString *)dElement->getObject();
            cout<<"key="+key + " ------ value=" + value->getCString()<<endl;
        }
    }
    delete csvParser;
    
    return dataArray;
}
