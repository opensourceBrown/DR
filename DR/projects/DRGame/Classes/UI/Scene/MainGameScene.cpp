#include "MainGameScene.h"
#include "BaseController.h"
#include "MainGameGridLayer.h"
#include "DataMangager.h"
#include "DRUtility.h"
#include "MainGameStatusBar.h"
#include "MainGameToolBar.h"

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
    CC_SAFE_DELETE(m_statusBar);
    CC_SAFE_DELETE(m_toolBar);
}

MainGameScene *MainGameScene::create(BaseController *pDelegate)
{
    MainGameScene *scene=new MainGameScene();
    do {
        CC_BREAK_IF(!scene || !(scene->initWith(pDelegate)));
        //scene->autorelease();
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
        m_gridLayer=MainGameGridLayer::create();
		CC_BREAK_IF(!m_gridLayer);
        m_gridLayer->retain();
		m_gridLayer->setDelegate(m_delegate);
		addChild(m_gridLayer);
        
		m_statusBar=MainGameStatusBar::create();
		CC_BREAK_IF(!m_statusBar);
        m_statusBar->retain();
		m_statusBar->setDelegate(m_delegate);
		addChild(m_statusBar);

		m_toolBar=MainGameToolBar::create();
		CC_BREAK_IF(!m_toolBar);
        m_toolBar->retain();
		m_toolBar->setDelegate(m_delegate);
		addChild(m_toolBar);
        
        testDataMethod();
    }while(0);
}

MainGameGridLayer *MainGameScene::getGridLayer()
{
    LOG_TRACE
    CCAssert(m_gridLayer, "m_gridLayer is null");
    
    return m_gridLayer;
}

MainGameStatusBar *MainGameScene::getStatusLayer()
{
    LOG_TRACE
    CCAssert(m_statusBar, "status bar is null");
    return m_statusBar;
}

MainGameToolBar *MainGameScene::getToolBar()
{
    LOG_TRACE
    CCAssert(m_toolBar, "tool bar is null");
    return m_toolBar;
}

#include "CSVParser.h"

void testDataMethod(void)
{
    printf("testDataMethod");
    
    /**
     *  plist read and write
     */
    {
//        CCDictionary *rDict = DataManager::sharedInstance()->getGridElements();
//        for(int i=0;i<GRID_ROW;i++){
//			for(int j=0;j<GRID_VOLUME;j++){
//                GridElementProperty *gridEProperty = new GridElementProperty();
//                gridEProperty->autorelease();
//                gridEProperty->init();
//                
//                //test
//                gridEProperty->mIndex.rIndex=i;
//                gridEProperty->mIndex.vIndex=j;
//                gridEProperty->mType=kElementType_Sword;
//                gridEProperty->mID=i*10+j;
//                
//                gridEProperty->saveToDictionary(rDict); //the Dict value is the property of GridElementProperty
//            }
//        }
//        DataManager::sharedInstance()->saveGridElements();
        
    }
    
    /**
     *  CSV test
     */
//    {
//        CSVParser *csvParser = new CSVParser();
//        csvParser->openFile("testdata.csv");
//        
//        CCArray      *dataArray = CCArray::create();
//        CCArray      *keys = CCArray::create();
//        CCDictionary *dictionary;
//        string strLine = "";
//        for (int i = 0; i < csvParser->getRows(); i++) {
//            for (int j = 0; j < csvParser->getCols(); j++) {
//                CCString *string = CCString::create(csvParser->getData(i, j));
//                if (i == 0) {
//                    keys->addObject(string);
//                } else {
//                    if (j==0) {
//                        dictionary = CCDictionary::create();
//                    }
//                    CCString *strKey = (CCString *)keys->objectAtIndex(j);
//                    dictionary->setObject(string, strKey->getCString());
//                    if (j== csvParser->getCols()-1) {
//                        dataArray->addObject(dictionary);
//                    }
//                }
//            }
//        }
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
//        
//        delete csvParser;
//    }
}
