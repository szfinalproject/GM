#include "GamePause.h"

Scene* GamePause::createScene()
{
	auto scene = Scene::create();
	auto layer = GamePause::create();
	scene->addChild(layer);
	return scene;
}
bool GamePause::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 150)))
	{
		return false;
	}
    visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	goOnButton = MenuItemImage::create(
		"Pause_off.png",
		"Pause_off.png",
		CC_CALLBACK_1(GamePause::goOn, this));

	Size size2 = goOnButton->getContentSize();
	float scaleX2 = (float)size2.width*0.5f / (float)size2.width;
	float scaleY2 = (float)size2.height*0.5f / (float)size2.height;
	goOnButton->setScale(scaleX2, scaleY2);
	goOnButton->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.97));
	menu = Menu::create(goOnButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 10);
	return true;
}
void GamePause::goOn(Ref*pSender)
{
	_eventDispatcher->dispatchCustomEvent("goOnGame");
}

