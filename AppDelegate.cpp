#include "AppDelegate.h"
USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
	loadingSoundThread = new std::thread(&AppDelegate::loadingSound, this);
}

AppDelegate::~AppDelegate() 
{
	loadingSoundThread->join();
	CC_SAFE_DELETE(loadingSoundThread);
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Angry", cocos2d::Rect(0, 0,largeResolutionSize.width, largeResolutionSize.height));
#else
        glview = GLViewImpl::create("Angry");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution 设计分配率
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = MainGame::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
	//CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
	//CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::loadingSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("backgroundMusic.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("ropePull.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("object1.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Object.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("object3.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("addmoney.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pity.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("TNT_long.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Stage_2.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pass.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("boom.mp3");

}
