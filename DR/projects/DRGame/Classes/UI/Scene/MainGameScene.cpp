#include "MainGameScene.h"
#include "BaseController.h"
#include "MainGameGridLayer.h"

USING_NS_CC;

void testDataMethod();

MainGameScene::MainGameScene():
    m_gridLayer(NULL),
    m_statusBar(NULL),
    m_toolBar(NULL)
{
    LOG_TRACE
}

MainGameScene::~MainGameScene()
{
    CC_SAFE_DELETE(m_gridLayer);
}

MainGameScene *MainGameScene::create(BaseController *pDelegate)
{
    MainGameScene *scene=new MainGameScene();
    do {
        CC_BREAK_IF(!scene || !(scene->initWith(pDelegate)));
        scene->autorelease();
        return scene;
    } while (0);
    
    CC_SAFE_DELETE(scene);
    return NULL;
}

bool MainGameScene::initWith(BaseController *pDelegate)
{
	bool tRet = false;
	do{
        CC_BREAK_IF(!init());
		CC_BREAK_IF(!pDelegate);
		m_delegate=pDelegate;
        
        this->constructUI();
        
		tRet = true;
	}while(0);
    
	return tRet;
}

void MainGameScene::constructUI()
{
    do{
        m_gridLayer=new MainGameGridLayer();
		CC_BREAK_IF(!m_gridLayer);
		m_gridLayer->initWithDelegate(m_delegate);
		addChild(m_gridLayer);
        
        /*
		m_statusBar=CCLayer::create();
		CC_BREAK_IF(!m_statusBar);
		addChild(m_statusBar);

		m_toolBar=CCLayer::create();
		CC_BREAK_IF(!m_toolBar);
		addChild(m_toolBar);

		CCLayerColor *statusInfoContainer=CCLayerColor::create(ccc4(256, 0, 0, 256));
        statusInfoContainer->setContentSize(CCSizeMake(WIN_SIZE.width, 80.0));
		statusInfoContainer->setPosition(CCPointZero);
		m_statusBar->addChild(statusInfoContainer);

		CCLayerColor *toolContainer=CCLayerColor::create(ccc4(0, 256, 0, 256));
		toolContainer->setContentSize(CCSizeMake(WIN_SIZE.width,80.0));
		toolContainer->setPosition(ccp(0,WIN_SIZE.height-80));
		m_toolBar->addChild(statusInfoContainer);

		//status bar
		CCLabelTTF *coinLabel=NULL;
		CCLabelTTF *roundLabel=NULL;
		CCLabelTTF *scoreLabel=NULL;
		CCLabelTTF *killdMonsterLabel=NULL;
		CCLabelTTF *healthLabel=NULL;

		CCSprite *baseDamageIcon=NULL;
		CCSprite *shieldIcon=NULL;
		CCSprite *weaponDamageIcon=NULL;
		CCLabelTTF *baseDamageLabel=NULL;
		CCLabelTTF *shieldLabel=NULL;
		CCLabelTTF *weaponDamageLabel=NULL;

		//tool bar

         */
        
//        testDataMethod();
    }while(0);
}

MainGameGridLayer *MainGameScene::getGridLayer()
{
    LOG_TRACE
    do{
        CC_BREAK_IF(m_gridLayer);
        CCLog("m_gridLayer=null");
        return NULL;
    }while(0);
    
    return m_gridLayer;
}

#include "CSVParser.h"

void testDataMethod(void)
{
    printf("testDataMethod");
    
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
//        cout<<"\n"<<endl;
    }
    

    
//    for (int i = 0; i < dictionary->count(); i++) {
//        cout<<dictionary->objectForKey("") <<endl;
//    }
    
//    dictionary->set
    delete csvParser;
}
