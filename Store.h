#pragma once
#ifndef __STORE_SCENE_H__
#define __STORE_SCENE_H__
#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MainGame.h"
#include "Score.h"
#include <iostream>
USING_NS_CC;
using namespace std;
class Store : public cocos2d::Layer
{
	int touchtime = 0;
	Menu* menu3;
	
public:
	static cocos2d::Scene* createScene();
	Label* label;
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	void menuContinueCallback(cocos2d::Ref* pSender);

	void addCrumpNumber();

	void removeCrumpLabel(CCNode *sender);
	// implement the "static create()" method manually
	CREATE_FUNC(Store);
};

#endif // __STORE_SCENE_H__
