#pragma once
#ifndef __CONGRATULATION_SCENE_H__
#define __CONGRATULATION_SCENE_H__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameMenu.h"
USING_NS_CC;

class Congratulation : public cocos2d::Layer
{

public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

	void menuContinueCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(Congratulation);
};
#endif // __CONGRATULATION_SCENE_H__