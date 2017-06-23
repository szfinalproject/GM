
//#include "AndriodGame.h"
#include "MainGame.h"
#include "GameMenu.h"

USING_NS_CC;
using namespace std;
extern Score score;
extern int water_number;
extern int crump_number;
Scene* GameMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}
bool GameMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	*(score.getScore()) = 0;
	water_number = 0;
	crump_number = 0;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto continueItem = MenuItemImage::create(
		"single.png",
		"single_dark.png",
		CC_CALLBACK_1(GameMenu::menuContinue, this));

	continueItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2.5 ));

	auto menu2 = Menu::create(continueItem, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 19);

	auto continueItem2 = MenuItemImage::create(
		"Double.png",
		"double_dark.png",
		CC_CALLBACK_1(GameMenu::menuContinue2, this));

	continueItem2->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 4 ));

	auto menu3 = Menu::create(continueItem2, NULL);
	menu3->setPosition(Vec2::ZERO);
	this->addChild(menu3, 19);

	auto close = MenuItemImage::create(
		"MenuClose.png",
		"MenuClose_dark.png",
		CC_CALLBACK_1(GameMenu::menuCloseCallback, this));

	close->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 4));

	auto menu4 = Menu::create(close, NULL);
	menu4->setPosition(Vec2::ZERO);
	//	this->addChild(menu4, 19);

	CCSprite* tong = CCSprite::create("tong.png");
	addChild(tong, 20);
	tong->setPosition(Vec2(visibleSize.width*0.35, visibleSize.height + 100));
	CCFiniteTimeAction *move1 = CCMoveTo::create(0.5, Vec2(visibleSize.width*0.35, visibleSize.height*0.8));
	tong->runAction(CCSequence::create(move1, NULL));

	CCSprite* ji = CCSprite::create("ji.png");
	addChild(ji,20);
	ji->setPosition(Vec2(visibleSize.width*0.45, visibleSize.height+100));
	CCFiniteTimeAction *move2 = CCMoveTo::create(0.5, Vec2(visibleSize.width*0.45, visibleSize.height*0.8));
	ji->runAction(CCSequence::create(move2, NULL));

	CCSprite* kuang = CCSprite::create("kuang.png");
	addChild(kuang, 20);
	kuang->setPosition(Vec2(visibleSize.width*0.55, visibleSize.height + 100));
	CCFiniteTimeAction *move3 = CCMoveTo::create(0.5, Vec2(visibleSize.width*0.55, visibleSize.height*0.8));
	kuang->runAction(CCSequence::create(move3, NULL));

	CCSprite* gong = CCSprite::create("gong.png");
	addChild(gong, 20);
	gong->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height + 100));
	CCFiniteTimeAction *move4 = CCMoveTo::create(0.5, Vec2(visibleSize.width*0.65, visibleSize.height*0.8));
	gong->runAction(CCSequence::create(move4, NULL));
	// add "GameMenu" splash screen"
	auto sprite1 = Sprite::create("StartSCENE.jpg");
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
	this->addChild(sprite1, 0);//改为自己的图片
    return true;


}

void GameMenu::menuContinue(Ref* pSender)
{
	*(score.getSD()) = 1;
	auto director = Director::getInstance();
	CCScene *scene = MainGame::createScene();
	auto transition = TransitionCrossFade::create(0.5f, scene);
	director->replaceScene(transition);
}

void GameMenu::menuContinue2(Ref* pSender)
{
	*(score.getSD()) = 0;
	auto director = Director::getInstance();
	CCScene *scene = MainGame::createScene();
	auto transition = TransitionCrossFade::create(0.5f, scene);
	director->replaceScene(transition);
}
void GameMenu::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}
