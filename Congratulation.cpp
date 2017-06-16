
#include "Congratulation.h"
USING_NS_CC;

Scene* Congratulation::createScene()
{
	// 'scene' is an autorelease object

	//设置物理世界
	auto scene = Scene::createWithPhysics();

	PhysicsWorld *world = scene->getPhysicsWorld();
	//将重力设为零
	world->setGravity(Vec2::ZERO);

	// 'layer' is an autorelease object
	auto layer = Congratulation::create();



	// add layer as a child to scene
	scene->addChild(layer);



	// return the scene
	return scene;
}

// on "init" you need to initialize your instance


bool Congratulation::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto continueItem = MenuItemImage::create(
		"restart.png",
		"restart_dark.png",
		CC_CALLBACK_1(Congratulation::menuContinueCallback, this));

	continueItem->setPosition(Vec2(origin.x + visibleSize.width / 1.8, visibleSize.height / 3 + origin.y));

	auto menu2 = Menu::create(continueItem, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 1);

	// add "Congratulation" splash screen"
	auto sprite1 = Sprite::create("congratulations.png");                                                  //改为自己的图片

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


	return true;


}

void Congratulation::menuContinueCallback(Ref* pSender)
{
	auto director = Director::getInstance();
	CCScene *scene = GameMenu::createScene();
	auto transition = TransitionCrossFade::create(0.5f, scene);
	director->replaceScene(transition);
}
void Congratulation::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application

	Director::getInstance()->end();


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);

}