//
//  CSVParser.h
//  DRGame
//
//  Created by magic on 14-2-20.
//
//

#ifndef __DRGame__CSVParser__
#define __DRGame__CSVParser__

#include <iostream>
#include "cocos2d.h"
#include <vector>
using namespace std;
USING_NS_CC;

class CSVParser
{
public:
    //    CCSVParse(void);
    ~CSVParser(void);
    CSVParser(istream& fin=cin, string sep=","):
    fieldsep(sep),
    cols(0)
    {
        
    }
    
    //用以存储数据
    std::vector<std::vector<std::string> > data;
    bool openFile(string fileName);
    const char* getData(unsigned int rows, unsigned int cols);
    string  getStringData(unsigned int rows, unsigned int cols);
    int findColsData(int cols, const char* value);
    
    inline int getCols(){return cols;}
    inline int getRows(){return data.size();}
    
private:
    string        fieldsep;
    int            cols;
    
    void StringSplit(const string& str, vector<string>& tokens, const char* delimiters);
    void split(vector<string>& field, string line);
    int advplain(const string& line, string& fld, int);
    int advquoted(const string& line, string& fld, int);
    
    
};

#endif /* defined(__DRGame__CSVParser__) */
