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
    
    static MainGameScene *create(BaseController *pDelegate);
    
    MainGameGridLayer *getGridLayer();
    CCLayer *getStatusLayer(){return m_statusBar;}
    CCLayer *getToolBar(){return m_toolBar;}
    
    
    
private:
    virtual bool initWith(BaseController *pDelegate);
    void constructUI();
    
private:
    
    MainGameGridLayer   *m_gridLayer;
    CCLayer             *m_statusBar;
    CCLayer             *m_toolBar;
    
};

#endif
