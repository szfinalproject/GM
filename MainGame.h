#pragma once
#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__
#include "math.h"
#include <vector>
#include "cocos2d.h"
#include <iostream>
#include "SimpleAudioEngine.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "Store.h"
#include "WetherToStartAgain.h"
#include "Score.h"
#include "Congratulation.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;
using namespace CocosDenshion;

class GamePause;
enum ObjectType
{
	small_stone = 0,
	big_stone,
	small_gold,
	middle_gold,
	big_gold,
	diamond,
	wallet,
	TNT,
	TNT2,
	pig
};

class Rope1: public CCSprite
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

	void reduceRope2Height(float);
	void runRope2Pull(float);
};
		
class MainGame:public cocos2d::Layer
		{
			GamePause* gamepause;
		public:

			
			static cocos2d::Scene* createScene();
			virtual bool init();
			void playObjectMusic(int music_tag);
			void use_crump(Rope1* rope);
			void use_crump2(Rope1* rope);
			void _spriteMoveFinished(cocos2d::CCNode *sender);
			void addObject(std::string type, int number);
			//void PLAYMusic(Ref* psender);
			void TNTboom(CCPoint Position);
		   //void loadingCallBack(Texture2D* texture);
			~MainGame();
			// implement the "static create()" method manually
			CREATE_FUNC(MainGame);
			
		};
				   class object:public cocos2d::CCSprite
				   {
				   public:
					   static object* create(std::string type, bool isCatched);
					   bool init(std::string type, bool isCatched);
					   void makePosition(ObjectType object_type, object* _object);
					   void Scale(object* _object, ObjectType _objectType);
					   void setObjectAsPhysicsBody(object* _object);
					   void virtual setName(std::string str);
					   virtual const std::string&getName() const;

				   protected:
					   int weight; //重量
					   int score;  //金币
					   string type;//种类
					   bool isCatched;//状态
				   };

  class TimeSchedule1 : public cocos2d::Node
				   {
				   public:
					   TimeSchedule1();

					   virtual ~TimeSchedule1();

					   static TimeSchedule1* createTimer(float time);

					   void update(float delta);

					   bool init(float time);

				   private:
					   Label* label;
					   float pTime;

				   };
#endif  //__MAINGAME_SCENE_H__
  
  







