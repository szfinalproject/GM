#pragma once
#ifndef __GAMEMENU_SCENE_H__
#define __GAMEMENU_SCENE_H__

#include "cocos2d.h"
//#include "MainGame.h"
#include "Score.h"
USING_NS_CC;

class GameMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void menuContinue(cocos2d::Ref* pSender);
	void menuContinue2(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameMenu);
};

#endif  //__GAMEMENU_SCENE_H__