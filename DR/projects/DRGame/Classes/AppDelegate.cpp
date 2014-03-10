#include "AppDelegate.h"
#include "MainGameScene.h"
#include "MainGameController.h"
#include "DRUtility.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    // Set the design resolution
    if (DRUtility::isiPadAdaptation()) {
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(768,1075, kResolutionExactFit);
    } else {
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(720,1224,  kResolutionExactFit);
    }
    
    //create scene
    MainGameController *controller=MainGameController::create() ;
    if (controller->getScene()) {
        pDirector->runWithScene(controller->getScene());
    }
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
