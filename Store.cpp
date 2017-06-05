
/*??????????????????????????????????????????????????
#include "Store.h"
#include "SimpleAudioEngine.h"
#include "SetObject.h"
#include "Score.h"
#include <iostream>
USING_NS_CC;
using namespace std;
extern int crump_number;
extern int level;
extern Score score;

Scene* Store::createScene()
{
// 'scene' is an autorelease object

//设置物理世界
auto scene = Scene::create();
// 'layer' is an autorelease object
auto layer = Store::create();

// add layer as a child to scene
scene->addChild(layer);

// return the scene
return scene;
}

// on "init" you need to initialize your instance

bool Store::init()
{
//////////////////////////////
// 1. super init first
if (!Layer::init())
{
return false;
}

auto visibleSize = Director::getInstance()->getVisibleSize();
Vec2 origin = Director::getInstance()->getVisibleOrigin();

/////////////////////////////
// 2. add a menu item with "X" image, which is clicked to quit the program
//    you may modify it.

// add a "close" icon to exit the progress. it's an autorelease object

auto closeItem = MenuItemImage::create(
"CloseNormal.png",
"CloseSelected.png",
CC_CALLBACK_1(Store::menuCloseCallback, this));

closeItem->setPosition(Vec2(origin.x + visibleSize.width / 1.5, visibleSize.height / 3 + origin.y));


auto crump = MenuItemImage::create(
	"crumplabel.jpg",
	"crumplabel.jpg",
	CC_CALLBACK_0(Store::addCrumpNumber, this));

crump->setPosition(Vec2(origin.x + visibleSize.width / 1.8, visibleSize.height / 3 + origin.y));

auto oncontinue = MenuItemImage::create(
	"continue.jpg",
	"continue.jpg",
	CC_CALLBACK_1(Store::menuContinueCallback, this));

oncontinue->setPosition(Vec2(origin.x + visibleSize.width / 1.5, visibleSize.height / 2 + origin.y));

// create menu, it's an autorelease object
auto menu1 = Menu::create(closeItem, NULL);
menu1->setPosition(Vec2::ZERO);
this->addChild(menu1, 1);

auto menu2 = Menu::create(oncontinue, NULL);
menu2->setPosition(Vec2::ZERO);
this->addChild(menu2, 2);

menu3 = Menu::create(crump, NULL);
menu3->setPosition(Vec2::ZERO);
this->addChild(menu3, 3);

// add "Store" splash screen"
auto sprite1 = Sprite::create("Store.jpg");                                                  //改为自己的图片

// position the sprite on the center of the screen
sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
Size mywinsize = Director::getInstance()->getWinSize();
float winw = mywinsize.width; //获取屏幕宽度
float winh = mywinsize.height;//获取屏幕高度
float spx = sprite1->getTextureRect().getMaxX();
float spy = sprite1->getTextureRect().getMaxY();
sprite1->setScaleX(winw / spx); //设置精灵宽度缩放比例
sprite1->setScaleY(winh / spy);

// add the sprite as a child to this layer
this->addChild(sprite1, 0);

char* price = new char[50];
int prc = 0;
	switch (level)
	{
	case 1:
		prc = 80;
		break;
	case 2:
		prc = 180;
		break;
	case 3:
		prc = 280;
		break;
	}
	sprintf(price, "%d", prc);
	label = Label::createWithSystemFont(price, "Arial", 20);
	label->setPosition(Vec2(origin.x + visibleSize.width / 1.8, visibleSize.height / 5.5 + origin.y));
	label->setColor(Color3B::GREEN);
	this->addChild(label);

return true;
}
void Store::addCrumpNumber()
{
		crump_number++;
		switch (level)
		{
		case 1:
			*(score.getScore()) -= 80;
			break;
		case 2:
			*(score.getScore()) -= 180;
			break;
		case 3:
			*(score.getScore()) -= 280;
			break;
		}
	menu3->removeFromParentAndCleanup(true);
	label->removeFromParentAndCleanup(true);
}

void Store::menuContinueCallback(Ref* pSender)
{
	auto director = Director::getInstance();
	CCScene *scene = SetObject::createScene();
	auto transition = TransitionCrossFade::create(0.5f, scene);
	director->replaceScene(transition);
}
void Store::menuCloseCallback(Ref* pSender)
{
//Close the cocos2d-x game scene and quit the application

Director::getInstance()->end();


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif

/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

//EventCustom customEndEvent("game_scene_close_event");
//_eventDispatcher->dispatchEvent(&customEndEvent);

/*??????????????????????????????????????????????????????????
}

?????????????????????????????????????????????*/