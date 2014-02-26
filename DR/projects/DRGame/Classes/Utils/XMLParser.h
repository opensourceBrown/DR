//
//  XMLParser.h
//  DRGame
//
//  Created by magic on 14-2-23.
//
//

#ifndef __DRGame__XMLParser__
#define __DRGame__XMLParser__

#include "cocos2d.h"
#include <stack>

class XMLParser : public cocos2d::CCSAXDelegator
{
	typedef enum
	{
		SAX_NONE = 0,
		SAX_KEY,
		SAX_DICT,
		SAX_INT,
		SAX_REAL,
		SAX_STRING,
		SAX_ARRAY
	}CCSAXState;
    
	typedef enum
	{
		SAX_RESULT_NONE = 0,
		SAX_RESULT_DICT,
		SAX_RESULT_ARRAY
	}CCSAXResult;
    
public:
	XMLParser();
	~XMLParser();
    
	cocos2d::CCDictionary* dictionaryWithXmlData(const char* pXMLData);
	cocos2d::CCArray* arrayWithXmlData(const char* pXMLData);
    
	cocos2d::CCDictionary* dictionaryWithContentsOfFile(const char *pFileName);
	cocos2d::CCArray* arrayWithContentsOfFile(const char* pFileName);
    
private:
	CCSAXResult m_eResultType;
	cocos2d::CCArray* m_pRootArray;
	cocos2d::CCDictionary *m_pRootDict;
	cocos2d::CCDictionary *m_pCurDict;
	std::stack<cocos2d::CCDictionary*> m_tDictStack;
	std::string m_sCurKey;   ///< parsed key
	std::string m_sCurValue; // parsed value
	CCSAXState m_tState;
	cocos2d::CCArray* m_pArray;
    
	std::stack<cocos2d::CCArray*> m_tArrayStack;
	std::stack<CCSAXState>  m_tStateStack;
    
private:
	void startElement(void *ctx, const char *name, const char **atts);
	void endElement(void *ctx, const char *name);
	void textHandler(void *ctx, const char *ch, int len);
};

#endif  // __XML_PARSER_H__
