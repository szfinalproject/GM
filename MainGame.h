#pragma once

#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#include "cocos2d.h"
#include <iostream>
#include "SimpleAudioEngine.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "string"
#include "network\SocketIO.h"
#include "json\rapidjson.h"
using namespace cocos2d::network;

USING_NS_CC;
using namespace std;



enum ObjectType
{
	small_stone = 0,
	big_stone,
	small_gold,
	middle_gold,
	big_gold,
	diamond,
	wallet,
	pig
};

class Rope1 : public CCSprite
{
private:

	float Rope1Height;
	float Rope1Width;
	float initRope1Height;
	bool _isRope1Changing;
	int addedscore;
	int random_objtag;
	Layer* _layer;
public:

	Rope1() {
		CCSprite::initWithFile("rope.jpg");
		addedscore = 0;
		random_objtag = 0;
	};

	void runRope1ShakeClaw();
	void runRope1Throw(float);
	void addRope1Height(float);
	void reduceRope1Height(float);
	void runRope1Pull(float);
	void stopRope1ShakeAction();
	void addObjectToRope1(std::string str, CCSprite* anchor);
	void set_Rope1Height(float size);
	void set_Rope1Width(float size);
	bool get_isRope1Changing();
	void set_isRope1Changing(bool TOF);
	void getInitRope1Height();
	void set_addedscore(int score);
	float get_Rope1Height();
	float get_Rope1Width();
	int getRope1_random_objtag();
	void reset_random_objtag();
	void walletRope1_catched();
	void set_p(CCLayer* layer);
};
class MainGame : public cocos2d::Layer,public SocketIO::SIODelegate
{//socket
	
	SIOClient* _sioClient;
public:
	

	static cocos2d::Scene* createScene();
	virtual bool init();
	void playObjectMusic(int music_tag);
	void menuCloseCallback(cocos2d::Ref* pSender);
	void use_crump(Rope1* rope);
	void _spriteMoveFinished(cocos2d::CCNode *sender);
	void addObject(std::string type, int number);
	void PLAYMusic(Ref* psender);
	// implement the "static create()" method manually
	CREATE_FUNC(MainGame);
	//rewrite the functions of SIOdelegate
	virtual void onConnect(SIOClient *client);
	virtual void onMessage(SIOClient *client,const string& data);//data
	virtual void onClose(SIOClient *client);
	virtual void onError(SIOClient *client,const string& data);//data
	virtual void callClientEvent(SIOClient *client,const string& data);
	
	//server CallBack Func
};



class object :public cocos2d::CCSprite {
public:
	//object(ObjectType object_type, bool isCatched);
	//~object() {}  //destructor
	static object* create(std::string type, bool isCatched);
	bool init(std::string type, bool isCatched);
	void makePosition(ObjectType object_type, object* _object);
	void Scale(object* _object, ObjectType _objectType);
	void setObjectAsPhysicsBody(object* _object);
	void virtual setName(std::string str);
	virtual const std::string& getName() const;
	
protected:
	int weight; //重量
	int score;  //金币
	string type;//种类
	bool isCatched;//状态
};










#endif  __MAINGAME_SCENE_H__
