#pragma once
#ifndef __GAMEPAUSE_SCENE_H__
#define __GAMEPAUSE_SCENE_H__

#include "Store.h"
#include "WetherToStartAgain.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace CocosDenshion;
USING_NS_CC;

class GamePause : public cocos2d::LayerColor
{
	Size visibleSize;
	Vec2 origin;
	MenuItemImage* goOnButton;
	Menu* menu;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	//void continueGame(cocos2d::Ref* pSender);
	// a selector callback
	void goOn(Ref*pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(GamePause);
};

#endif

