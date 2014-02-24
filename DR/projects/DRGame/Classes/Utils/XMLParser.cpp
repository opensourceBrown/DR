//
//  XMLParser.cpp
//  DRGame
//
//  Created by magic on 14-2-23.
//
//

#include "XMLParser.h"

USING_NS_CC;

CCDictionary* XMLParser::dictionaryWithXmlData(const char* pXMLData)
{
	if (!pXMLData)
	{
		return NULL;
	}
    
	m_eResultType = SAX_RESULT_DICT;
	CCSAXParser parser;
    
	if (false == parser.init("UTF-8"))
	{
		return NULL;
	}
	parser.setDelegator(this);
	
	parser.parse(pXMLData, strlen(pXMLData));
    
    CCDictionary *ret = m_pRootDict;
    m_pRootDict = NULL;
    if (ret != NULL) {
        ret->autorelease();
    }
    
	return ret;
}

CCArray* XMLParser::arrayWithXmlData(const char* pXMLData)
{
	if (!pXMLData)
	{
		return NULL;
	}
    
	m_eResultType = SAX_RESULT_ARRAY;
	CCSAXParser parser;
    
	if (false == parser.init("UTF-8"))
	{
		return NULL;
	}
	parser.setDelegator(this);
    
	parser.parse(pXMLData, strlen(pXMLData));
    
    CCArray *ret = m_pRootArray;
    m_pRootArray = NULL;
    if (ret != NULL) {
        ret->autorelease();
    }
    
	return ret;
}

CCDictionary* XMLParser::dictionaryWithContentsOfFile(const char *pFileName)
{
	if (!pFileName)
	{
		return NULL;
	}
    
	m_eResultType = SAX_RESULT_DICT;
	CCSAXParser parser;
    
	if (false == parser.init("UTF-8"))
	{
		return NULL;
	}
	parser.setDelegator(this);
    
	parser.parse(pFileName);
    
    CCDictionary *ret = m_pRootDict;
    m_pRootDict = NULL;
    if (ret != NULL) {
        ret->autorelease();
    }
    
	return ret;
}

CCArray* XMLParser::arrayWithContentsOfFile(const char* pFileName)
{
	if (!pFileName)
	{
		return NULL;
	}
    
	m_eResultType = SAX_RESULT_ARRAY;
	CCSAXParser parser;
    
	if (false == parser.init("UTF-8"))
	{
		return NULL;
	}
	parser.setDelegator(this);
    
	parser.parse(pFileName);
    
    CCArray *ret = m_pRootArray;
    m_pRootArray = NULL;
    if (ret != NULL) {
        ret->autorelease();
    }
    
	return ret;
}

XMLParser::XMLParser()
: m_eResultType(SAX_RESULT_NONE),
m_pRootArray(NULL),
m_pRootDict(NULL),
m_pCurDict(NULL),
m_tState(SAX_NONE),
m_pArray(NULL)
{
}

XMLParser::~XMLParser()
{
}

void XMLParser::startElement(void *ctx, const char *name, const char **atts)
{
	CC_UNUSED_PARAM(ctx);
	CC_UNUSED_PARAM(atts);
	std::string sName((char*)name);
	if( sName == "dict" )
	{
		m_pCurDict = new CCDictionary();
		if(m_eResultType == SAX_RESULT_DICT && m_pRootDict == NULL)
		{
			// Because it will call m_pCurDict->release() later, so retain here.
			m_pRootDict = m_pCurDict;
			m_pRootDict->retain();
		}
		m_tState = SAX_DICT;
        
		CCSAXState preState = SAX_NONE;
		if (! m_tStateStack.empty())
		{
			preState = m_tStateStack.top();
		}
        
		if (SAX_ARRAY == preState)
		{
			// add the dictionary into the array
			m_pArray->addObject(m_pCurDict);
		}
		else if (SAX_DICT == preState)
		{
			// add the dictionary into the pre dictionary
			CCAssert(! m_tDictStack.empty(), "The state is wrong!");
			CCDictionary* pPreDict = m_tDictStack.top();
			pPreDict->setObject(m_pCurDict, m_sCurKey.c_str());
		}
        
		m_pCurDict->release();
        
		// record the dict state
		m_tStateStack.push(m_tState);
		m_tDictStack.push(m_pCurDict);
	}
	else if(sName == "key")
	{
		m_tState = SAX_KEY;
	}
	else if(sName == "integer")
	{
		m_tState = SAX_INT;
	}
	else if(sName == "real")
	{
		m_tState = SAX_REAL;
	}
	else if(sName == "string")
	{
		m_tState = SAX_STRING;
	}
	else if (sName == "array")
	{
		m_tState = SAX_ARRAY;
		m_pArray = new CCArray();
		if (m_eResultType == SAX_RESULT_ARRAY && m_pRootArray == NULL)
		{
			m_pRootArray = m_pArray;
			m_pRootArray->retain();
		}
		CCSAXState preState = SAX_NONE;
		if (! m_tStateStack.empty())
		{
			preState = m_tStateStack.top();
		}
        
		if (preState == SAX_DICT)
		{
			m_pCurDict->setObject(m_pArray, m_sCurKey.c_str());
		}
		else if (preState == SAX_ARRAY)
		{
			CCAssert(! m_tArrayStack.empty(), "The state is wrong!");
			CCArray* pPreArray = m_tArrayStack.top();
			pPreArray->addObject(m_pArray);
		}
		m_pArray->release();
		// record the array state
		m_tStateStack.push(m_tState);
		m_tArrayStack.push(m_pArray);
	}
	else
	{
		m_tState = SAX_NONE;
	}
}

void XMLParser::endElement(void *ctx, const char *name)
{
	CC_UNUSED_PARAM(ctx);
	CCSAXState curState = m_tStateStack.empty() ? SAX_DICT : m_tStateStack.top();
	std::string sName((char*)name);
	if( sName == "dict" )
	{
		m_tStateStack.pop();
		m_tDictStack.pop();
		if ( !m_tDictStack.empty())
		{
			m_pCurDict = m_tDictStack.top();
		}
	}
	else if (sName == "array")
	{
		m_tStateStack.pop();
		m_tArrayStack.pop();
		if (! m_tArrayStack.empty())
		{
			m_pArray = m_tArrayStack.top();
		}
	}
	else if (sName == "true")
	{
		CCString *str = new CCString("1");
		if (SAX_ARRAY == curState)
		{
			m_pArray->addObject(str);
		}
		else if (SAX_DICT == curState)
		{
			m_pCurDict->setObject(str, m_sCurKey.c_str());
		}
		str->release();
	}
	else if (sName == "false")
	{
		CCString *str = new CCString("0");
		if (SAX_ARRAY == curState)
		{
			m_pArray->addObject(str);
		}
		else if (SAX_DICT == curState)
		{
			m_pCurDict->setObject(str, m_sCurKey.c_str());
		}
		str->release();
	}
	else if (sName == "string" || sName == "integer" || sName == "real")
	{
		CCString* pStrValue = new CCString(m_sCurValue);
        
		if (SAX_ARRAY == curState)
		{
			m_pArray->addObject(pStrValue);
		}
		else if (SAX_DICT == curState)
		{
			m_pCurDict->setObject(pStrValue, m_sCurKey.c_str());
		}
        
		pStrValue->release();
		m_sCurValue.clear();
	}
    
	m_tState = SAX_NONE;
}

void XMLParser::textHandler(void *ctx, const char *ch, int len)
{
	CC_UNUSED_PARAM(ctx);
	if (m_tState == SAX_NONE)
	{
		return;
	}
    
	CCSAXState curState = m_tStateStack.empty() ? SAX_DICT : m_tStateStack.top();
	CCString *pText = new CCString(std::string((char*)ch,0,len));
    
	switch(m_tState)
	{
        case SAX_KEY:
            m_sCurKey = pText->getCString();
            break;
        case SAX_INT:
        case SAX_REAL:
        case SAX_STRING:
		{
			if (curState == SAX_DICT)
			{
				CCAssert(!m_sCurKey.empty(), "key not found : <integer/real>");
			}
            
			m_sCurValue.append(pText->getCString());
		}
            break;
        default:
            break;
	}
	pText->release();
}