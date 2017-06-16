#pragma once
#ifndef __WETHERTOSTARTAGAIN_SCENE_H__
#define __WETHERTOSTARTAGAIN_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameMenu.h"
USING_NS_CC;

class WetherToStartAgain : public cocos2d::Layer
{

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	void menuContinueCallback(cocos2d::Ref* pSender);


	// implement the "static create()" method manually
	CREATE_FUNC(WetherToStartAgain);
};

#endif // __WETHERTOSTARTAGAIN_SCENE_H__
