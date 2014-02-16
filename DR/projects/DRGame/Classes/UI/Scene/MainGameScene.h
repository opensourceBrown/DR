#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "cocos2d.h"
#include "BaseScene.h"

class MainGameGridLayer;
class BaseController;
class BaseScene;
class MainGameController;
class MainGameScene : public BaseScene
{
public:
    MainGameScene();
    virtual ~MainGameScene();
    
    bool initWithDelegate(MainGameController *pDelegate);
    
    void constructUI();
    MainGameGridLayer *getGridLayer(){return m_gridLayer;}
    CCLayer *getStatusLayer(){return m_statusBar;}
    CCLayer *getToolBar(){return m_toolBar;}
    
private:
    MainGameController  *m_delegate;
    
    MainGameGridLayer   *m_gridLayer;
    CCLayer             *m_statusBar;
    CCLayer             *m_toolBar;
};

#endif
