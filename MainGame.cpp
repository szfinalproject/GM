#pragma once

#include "HelloWorldScene.h"
#include "math.h"
#include <vector>
#include "cocos2d.h"
#include <iostream>
#include "SimpleAudioEngine.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"

#define WORLDTAG 1000

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

bool isMusicPlayed = true;
vector<Vec2> obj_position;
int score = 0;
CCLabelTTF * totalScoreLB;
CCLabelTTF * crumpLB;
CCLabelTTF * waterLB;
//炸弹数目
int crump_number=30;
//加速水数目
int water_number=0;

Scene* MainGame::createScene()
{
	//设置物理世界
	auto scene = Scene::createWithPhysics();
	PhysicsWorld *world = scene->getPhysicsWorld();
	world->setGravity(Vec2::ZERO);

	// 'layer' is an autorelease object
	auto layer = MainGame::create();

	//放置绳子


	
	//设置一个有边界的刚体（屏幕）
	Size size = Director::getInstance()->getWinSize();

	PhysicsBody *body = PhysicsBody::createEdgeBox(size);
	body->setCategoryBitmask(10);
	body->setCollisionBitmask(10);
	body->setContactTestBitmask(10);

	Node *node = Node::create();
	node->setPosition(size / 2);//默认当前屏幕尺寸
	node->setPhysicsBody(body);
	node->setTag(WORLDTAG);
	scene->addChild(node);

	scene->addChild(layer);
	
	return scene;
}


bool MainGame::init()
{
	if (!Layer::init())
	{
		return false;

	}
	
	auto visibleSize = Director::sharedDirector()->getWinSize();
    CCSprite* background = CCSprite::create("BG_3.jpg");
	
	Size bgSize=background->getContentSize();
	background->setScale(visibleSize.width/bgSize.width,visibleSize.height / bgSize.height);
	background->setPosition(visibleSize.width*0.5,visibleSize.height*0.5);
	this->addChild(background);
	
	SimpleAudioEngine::getInstance()->playBackgroundMusic("backgroundMusic.wav", true);

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	obj_position = { Vec2(0.1,0.3),Vec2(0.3,0.3),Vec2(0.5,0.3),Vec2(0.7,0.3),Vec2(0.9,0.3),Vec2(0.1,0.4),Vec2(0.3,0.4),Vec2(0.5,0.4),Vec2(0.7,0.4),Vec2(0.9,0.4),Vec2(0.1,0.5),Vec2(0.3,0.5),Vec2(0.5,0.5),Vec2(0.7,0.5) };

	char str[50] = {'\0'};
	sprintf(str, "%d", score);

	totalScoreLB = CCLabelTTF::create(str, "Zapfino", 15);
	totalScoreLB->setPosition(CCPointMake(visibleSize.width*0.8 , visibleSize.height*0.9));
	this->addChild(totalScoreLB);
	totalScoreLB->setColor(ccc3(200, 20, 255));

	//炸弹图标


	CCSprite* crumplabel = CCSprite::create("crumplabel.png");
	crumplabel->setPosition(CCPointMake(visibleSize.width*0.75, visibleSize.height*0.8));
	this->addChild(crumplabel);
	
	char str_crump[10] = { '\0' };
	sprintf(str_crump, "%d", crump_number);
	crumpLB = CCLabelTTF::create(str_crump, "Zapfino", 15);
	crumpLB->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.8));
	this->addChild(crumpLB);
	//加速水图标


//暂时设置图标大小
	Size size1 =crumplabel->getContentSize();
	
	float scaleX1 = (float)size1.width*0.2f / (float)size1.width;
	float scaleY1 = (float)size1.height*0.2f / (float)size1.height;
	crumplabel->setScale(scaleX1, scaleY1);
	
	//背景音乐
	//播放选项
	CCMenuItemImage *musicoff = CCMenuItemImage::create("Music_off.png","Music_off.png");
	CCMenuItemImage *musicon = CCMenuItemImage::create("Music_on.png", "Music_on.png");
	CCMenuItemToggle* playMusic = CCMenuItemToggle::createWithTarget(this,menu_selector(MainGame::PLAYMusic),musicon, musicoff, NULL);
	



	CCMenu* musicMenu = CCMenu::create(playMusic, NULL);
	musicMenu->setPosition(Vec2(visibleSize.width*0.9, visibleSize.height*0.9));
	this->addChild(musicMenu);
	//获取绳和钩子的长和宽
	Rope1* rope = new Rope1();
	rope->set_p(this);
	rope->set_Rope1Height(rope->getContentSize().height);
	rope->set_Rope1Width(rope->getContentSize().width);
	rope->getInitRope1Height();
	//放置绳子

	rope->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.7));
	rope->setAnchorPoint(Vec2(0.3, 1));
	this->addChild(rope,10);
	CCSprite* anchor = CCSprite::create("anchor.png");
	rope->addChild(anchor);
	anchor->setName("anchor");
	rope->set_isRope1Changing(false);
	rope->runRope1ShakeClaw();//绳子摆动
	PhysicsBody *body = PhysicsBody::createEdgeBox(Size(anchor->getContentSize()));
	body->setCategoryBitmask(10);
	body->setCollisionBitmask(10);
	body->setContactTestBitmask(10);
	anchor->setPhysicsBody(body);
	//将锚设置为刚体

    //添加矿工
	
	CCSprite* miner = CCSprite::create("Miner_1.png");
	miner->setName("Miner");
	miner->setPosition(visibleSize.width*0.5, visibleSize.height *0.73);
	this->addChild(miner);
   


	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			if (!(rope->get_isRope1Changing()))
			{
				rope->stopRope1ShakeAction();
			rope->runRope1Throw(1.0);
			
			}
			return true;

		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//碰撞检测
	auto physicListener = EventListenerPhysicsContact::create();
	physicListener->onContactBegin = [=](PhysicsContact &contact)
	{   float weight = 70.0;
	    int addedscore = 0;
	auto sth = contact.getShapeB()->getBody()->getNode();
	if (sth->getTag() != WORLDTAG)
	{
		//if (_sioClient != nullptr)
			//_sioClient->emit("callServerEvent", "{\"message\":\"what?\"}");
		int music_tag = 0;
		string name = sth->getName();
		if (name == "small_stone")
		{
			weight = 900;
			rope->set_addedscore(11);
			music_tag = 1;
		}
		if (name == "big_stone")
		{
			weight = 1500;
			rope->set_addedscore(20);
			music_tag = 1;
		}
		if (name == "small_gold")
		{
			weight = 200;
			rope->set_addedscore(50);
			music_tag = 2;
		}
		if (name == "middle_gold")
		{
			weight = 1000;
			rope->set_addedscore(100);
			music_tag = 2;
		}
		if (name == "big_gold")
		{
			weight = 1200;
			rope->set_addedscore(500);
			music_tag = 3;
		}
		if (name == "diamond")
		{
			weight = 200.0;
			rope->set_addedscore(200);
			music_tag = 3;
		}
		if (name == "wallet")
		{
			weight = 100.0;
			rope->walletRope1_catched();
			music_tag = 2;
		}
     	if (name == "pig")
		{
			weight = 60.0;
			rope->set_addedscore(500);
			music_tag = 1;
		}
		rope->addObjectToRope1(name, anchor);//新建
		sth->removeFromParent();//移除
		if(isMusicPlayed)
		playObjectMusic(music_tag);
	}
	weight *= water_number == 0 ? 1 : 0.2;
	rope->runRope1Pull(weight);



	//加速水
	
	

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicListener, this);
	auto Presslistener = EventListenerKeyboard::create();
	Presslistener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW)
		{

			//判断绳子上是否有物体
			if (!anchor->getChildren().empty() && crump_number != 0)
			{
				rope->reset_random_objtag();
				rope->set_addedscore(0);
				this->use_crump(rope);

				rope->runRope1Pull(50.0);
			}
		}




	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Presslistener, this);
	

	//添加物体



	addObject("small_stone", 1);
	addObject("big_stone", 1);
	addObject("diamond", 1);
    addObject("wallet", 5);
	addObject("small_gold",2);
	addObject("middle_gold", 2);
	addObject("big_gold", 2);
	addObject("pig", 1);
	auto things=this->getChildren();
	auto boomthing = *(things.end() - 3);
	boomthing->removeFromParent();
	
	CCSprite* TNT = CCSprite::create("tnt.png");
	
	CCAnimation *TNTboom = CCAnimation::create();
	for (int i = 1; i <= 10; i++)
	{
		char name[50] = { '\0' };
		sprintf(name, "TNT_%d.png", i);
		TNTboom->addSpriteFrameWithFileName(name);
	}
	TNTboom->setDelayPerUnit(0.1);
	CCAnimate *TNTboomaction = CCAnimate::create(TNTboom);
	CCFiniteTimeAction *boomDone = CCCallFuncN::create(this, callfuncN_selector(MainGame::_spriteMoveFinished));
	TNT->runAction(CCSequence::create(TNTboomaction, boomDone, NULL));

	if (isMusicPlayed)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("boom.mp3", false);

	return true;
}
inline void MainGame::addObject(std::string type, int number)
{

	for (int i = 0; i < number; ++i)
	{
object* sth = object::create(type, false);
		if (type == "pig")
		{
			this->addChild(sth);
			
		}
			
		else
		{
			this->addChild(sth);
		}
	}

}



void MainGame::_spriteMoveFinished(cocos2d::CCNode *sender) {
	CCSprite *sprite = (CCSprite *)sender;
	this->removeChild(sprite, true);
}

inline void object::makePosition(ObjectType object_type, object* _object)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	switch (object_type)
	{
	case pig:
	{Vec2 _pos(winSize.width*0.2, winSize.height*0.2);
	this->setPosition(_pos);
	
	}
	break;
	default:
	{
	Vec2 _pos = *(obj_position.end() - 1);
	this->setPosition(CCPointMake(_pos.x*winSize.width, _pos.y*winSize.height));
	obj_position.pop_back();
	}
	break;
	}
}

inline object* object::create(std::string type, bool isCatched)
{
	object* _object = new object();
	_object->init(type, isCatched);
	
	return _object;
}

bool object::init(std::string type, bool isCatched)
{
	ObjectType object_type = small_stone;
	if (type == "small_stone")
		object_type = small_stone;
	else if (type == "big_stone")
		object_type = big_stone;
	else if (type == "small_gold")
		object_type = small_gold;
	else if (type == "middle_gold")
		object_type = middle_gold;
	else if (type == "big_gold")
		object_type = big_gold;
	else if (type == "diamond")
		object_type = diamond;
	else if (type == "wallet")
		object_type = wallet;
	else if (type == "pig")
		object_type = pig;
	switch (object_type)
	{
	case small_stone:
	{this->initWithFile("small_stone.png");
	
	setName("small_stone");
	if (!isCatched)
	{
		this->makePosition(small_stone, this);
		setObjectAsPhysicsBody(this);
		
	}
	}
	break;
	case big_stone:
	{this->initWithFile("big_stone.png");
	Scale(this,big_stone);
	setName("big_stone");
	if (!isCatched)
	{
		this->makePosition(big_stone, this);
		setObjectAsPhysicsBody(this);

	}
	}
	break;
	case small_gold:
	{this->initWithFile("small_gold.png");
	Scale(this,small_gold);
	setName("small_gold");
	if (!isCatched)
	{
		this->makePosition(small_gold, this);
		setObjectAsPhysicsBody(this);
		
	}
	}
	break;
	case middle_gold:
	{this->initWithFile("middle_gold.png");
	//Scale(this);
	setName("middle_gold");
	if (!isCatched)
	{
		this->makePosition(middle_gold, this);
		setObjectAsPhysicsBody(this);

	}
	}
	break;
	case big_gold:
	{this->initWithFile("big_gold.png");
	Scale(this,big_gold);
	setName("big_gold");
	if (!isCatched)
	{
		this->makePosition(big_gold, this);
		setObjectAsPhysicsBody(this);

	}
	}
	break;
	case diamond:
	{this->initWithFile("Diamond.png");
	//Scale(this);
	setName("diamond");
	if (!isCatched)
	{
		this->makePosition(diamond, this);
		setObjectAsPhysicsBody(this);
		
	}
	}
	break;
	case wallet:
	{this->initWithFile("Wallet.png");
	
	setName("wallet");
	if (!isCatched)
	{
		this->makePosition(wallet, this);
		setObjectAsPhysicsBody(this);
	
	}
	}
	break;
	case pig:
	{this->initWithFile("A2f_0.png");
	setName("pig");
	this->makePosition(pig, this);
	if (!isCatched)
	{
	
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		setObjectAsPhysicsBody(this);
		
			CCAnimation *animation1 = CCAnimation::create();
			for (int i = 0; i < 6; i++)
			{
				char name[50] = { 0 };
				sprintf(name, "A2f_%d.png", i);
				animation1->addSpriteFrameWithFileName(name);
			}
			animation1->setDelayPerUnit(0.1);
			animation1->setRestoreOriginalFrame(true); // 播放完之后返回到第一帧
			CCAnimate *action1 = CCAnimate::create(animation1);
			Repeat* _action1 = Repeat::create(action1, 20);
			CCFiniteTimeAction *actionmove1 = CCMoveTo::create(12.0, CCPointMake(winSize.width*0.8, this->getPosition().y));
			

			CCAnimation *animation2 = CCAnimation::create();
			for (int i = 0; i < 6; i++)
			{
				char name[50] = { 0 };
				sprintf(name, "B2f_%d.png", i);
				animation2->addSpriteFrameWithFileName(name);
			}
			animation2->setDelayPerUnit(0.1);
			animation2->setRestoreOriginalFrame(true); // 播放完之后返回到第一帧
			CCAnimate *action2 = CCAnimate::create(animation2);
			Repeat* _action2=Repeat::create(action2,20);
			CCFiniteTimeAction *actionmove2 = CCMoveTo::create(12.0, CCPointMake(winSize.width*0.2, this->getPosition().y));
			
			this->runAction(RepeatForever::create(CCSequence::create(actionmove1, actionmove2,NULL)));
			this->runAction(RepeatForever::create(CCSequence::create(_action1,_action2,NULL)));  // 运行精灵对象
		};
		

	
	}
	break;
	default:
		break;
	}
	return true;
}




inline void object::Scale(object* _object,ObjectType _objectType)
{
	float scale = 0;

	Size size = _object->getContentSize();
	switch (_objectType)
	{case big_stone:
		scale = 2.0;
		break;
	case middle_gold:
		scale = 0.7;
		break;
	case big_gold:
		scale = 1.5;
		break;
	case small_gold:
		scale = 0.5;
		break;
	}
	float scaleX = (float)size.width*scale / (float)size.width;
	float scaleY = (float)size.height*scale/ (float)size.height;
	_object->setScale(scaleX, scaleY);
	}


inline void object::setObjectAsPhysicsBody(object* _object)
{
	Size objectSize = _object->getContentSize();
	auto body = PhysicsBody::createBox(objectSize);
	body->setCategoryBitmask(10);
	body->setCollisionBitmask(10);
	body->setContactTestBitmask(10);
	_object->setPhysicsBody(body);
}//将物体设置为刚体 


void object::setName(std::string str)
{
	this->type = str;
}
const std::string& object::getName() const
{
	return this->type;
}


inline void Rope1::addObjectToRope1(std::string str, CCSprite* anchor)
{

	object* new_object = object::create(str, true);
	anchor->addChild(new_object);
	auto anchor_size=anchor->getContentSize();
	new_object->setPosition(Vec2(0.5*anchor_size.width, 0.5*anchor_size.height));
	
}

void Rope1::runRope1ShakeClaw()
{
	this->setRotation(0);
	auto seq1 = Sequence::create(RotateBy::create(1.2, -80), RotateBy::create(2.4, 160), RotateBy::create(1.2, -80), nullptr);
	this->runAction(RepeatForever::create(seq1));
}//绳子摆动

void Rope1::stopRope1ShakeAction()
{
	this->stopAllActions();
}//绳子停止运动

void Rope1::runRope1Throw(float judge_time)
{
	_isRope1Changing = true;
	schedule(CC_SCHEDULE_SELECTOR(Rope1::addRope1Height), 0.007*judge_time);
}//丢绳子

void Rope1::addRope1Height(float)
{
	Rope1Height += 1;
	this->setContentSize(Size(Rope1Width, Rope1Height));

}//绳子伸长




void Rope1::runRope1Pull(float weight)
{
	float time = weight*0.0001;
	auto miner = _layer->getChildByName("Miner");
	CCAnimation *animation_miner = CCAnimation::create();
	for (int i = 1; i <= 4; i++)
	{
		char name[30] = { '\0' };
		sprintf(name, "Miner_%d.png", i);
		animation_miner->addSpriteFrameWithFileName(name);
	}
	animation_miner->setDelayPerUnit(0.3);
	animation_miner->setRestoreOriginalFrame(true); // 播放完之后返回到第一帧
	CCAnimate *action_miner = CCAnimate::create(animation_miner);
	miner->runAction(RepeatForever::create(action_miner));
	schedule(CC_SCHEDULE_SELECTOR(Rope1::reduceRope1Height), time);
	unschedule(CC_SCHEDULE_SELECTOR(Rope1::addRope1Height));
}//消除绳子的刚体性质


void Rope1::reduceRope1Height(float)//
{    
	auto visibleSize = Director::sharedDirector()->getWinSize();
	Rope1Height -= 1;
	unsigned int effect_id=0;
	if(isMusicPlayed)
	effect_id=CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ropePull.wav", true);


	if (Rope1Height <= 20)
	{
		auto miner = _layer->getChildByName("Miner");
		miner->stopAllActions();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseEffect(effect_id);
		unschedule(CC_SCHEDULE_SELECTOR(Rope1::reduceRope1Height));//停止调用
		Rope1Height = initRope1Height;
		_isRope1Changing = false;
		auto anchor = this->getChildByName("anchor");
		anchor->removeAllChildren();
		this->runRope1ShakeClaw();
		switch (this->getRope1_random_objtag())
		{
		case 1://add crump
		{
			//改变图标
			crump_number++;
			char str_2[50] = { '\0' };
			sprintf(str_2, "%d", crump_number);
			crumpLB->setString(str_2);
			//执行动画
			CCSprite* get_crump = CCSprite::create("crump.png");
			_layer->addChild(get_crump);
			get_crump->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
			CCFiniteTimeAction *move = CCMoveTo::create(0.5, CCPointMake(visibleSize.width*0.75, visibleSize.height*0.8));
			CCFiniteTimeAction *moveDone = CCCallFuncN::create(_layer, callfuncN_selector(MainGame::_spriteMoveFinished));
			get_crump->runAction(CCSequence::create(move, moveDone, NULL));


		}
		break;
		case 2://add water
		{//
			water_number++;
			if (water_number != 0)

			{
				CCSprite* waterlabel = CCSprite::create("waterlabel.png");
				waterlabel->setPosition(Vec2(visibleSize.width*0.75, visibleSize.height*0.75));
				_layer->addChild(waterlabel);
				Size size2 = waterlabel->getContentSize();
				float scaleX2 = (float)size2.width*0.1f / (float)size2.width;
				float scaleY2 = (float)size2.height*0.1f / (float)size2.height;
				waterlabel->setScale(scaleX2, scaleY2);
			}

				CCSprite* get_water = CCSprite::create("waterlabel.png");
				_layer->addChild(get_water);
				get_water->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
				CCFiniteTimeAction *move = CCMoveTo::create(0.5, CCPointMake(visibleSize.width*0.75, visibleSize.height*0.8));
				CCFiniteTimeAction *moveDone = CCCallFuncN::create(_layer, callfuncN_selector(MainGame::_spriteMoveFinished));
				get_water->runAction(CCSequence::create(move, moveDone, NULL));

			
		}
			break;
		case 3://add money
		{   int random_score = 0;
		random_score = rand() % 200 + 1;
		this->set_addedscore(random_score);
		}
		break;
		default:
			break;
		}
		if(addedscore!=0&&isMusicPlayed)
		SimpleAudioEngine::getInstance()->playEffect("addMoney.mp3", false);
		score += addedscore;
		addedscore = 0;
		char str_2[50] = { '\0' };
		sprintf(str_2, "%d", score);
		totalScoreLB->setString(str_2);
		
		random_objtag = 0;
		}
		this->setContentSize(Size(Rope1Width, Rope1Height));
	}
//回收绳子




void Rope1::set_Rope1Height(float size)
{
	Rope1Height = size;
}

void Rope1::set_Rope1Width(float size)
{
	Rope1Width = size;
}

void Rope1::getInitRope1Height()
{
	initRope1Height = Rope1Height;
}
void Rope1::set_isRope1Changing(bool TOF)
{
	_isRope1Changing = TOF;
}
bool Rope1::get_isRope1Changing()
{
	return _isRope1Changing;
}
float Rope1::get_Rope1Height()
{
	return Rope1Height;
}

float Rope1::get_Rope1Width()
{
	return Rope1Width;
}

void Rope1::set_addedscore(int score)
{
	addedscore = score;
}
void Rope1::walletRope1_catched()
{

	srand((unsigned)time(NULL));
	random_objtag = rand() % 3+1;
	
}
 
int Rope1::getRope1_random_objtag()
{
	return random_objtag;
}
void Rope1::set_p(CCLayer* layer)
{
	_layer = layer;
}

void Rope1::reset_random_objtag()
{
	random_objtag = 0;
}

void MainGame::use_crump(Rope1* rope)
{
	// 移到指定位置
	crump_number -= 1;
	char curnum_crump[10] = { '\0' };
	if (crump_number < 1)
		crump_number = 0;
	sprintf(curnum_crump, "%d", crump_number);
	crumpLB->setString(curnum_crump);
	rope->unschedule(CC_SCHEDULE_SELECTOR(Rope1::reduceRope1Height));
	auto anchor = rope->getChildByName("anchor");
	auto the_object = *(anchor->getChildren().begin());


	//将相对于绳子坐标转换到世界坐标下
	CCPoint object_position = rope->convertToWorldSpace(the_object->getPosition());

	CCSprite* crump = CCSprite::create();
	crump->initWithFile("crump.png");
	this->addChild(crump, 4);

	crump->setPosition(rope->getPosition());
	anchor->removeAllChildren();

	CCFiniteTimeAction *crumpmove = CCMoveTo::create(0.1, object_position);
	
	//爆炸效果
	CCAnimation *boom = CCAnimation::create();
	for (int i = 1; i <= 7; i++)
	{
		char name[50] = { '\0' };
		sprintf(name, "explosion%d.png", i);
		boom->addSpriteFrameWithFileName(name);
	}
	boom->setDelayPerUnit(0.1);
	CCAnimate *boomaction = CCAnimate::create(boom);
	CCFiniteTimeAction *_removeCrump = CCCallFuncN::create(this, callfuncN_selector(MainGame::_spriteMoveFinished));
	crump->runAction(CCSequence::create(crumpmove,boomaction, _removeCrump, NULL));
    if(isMusicPlayed)
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("boom.mp3", false);

}

void MainGame::PLAYMusic(Ref* psender)
{
	MenuItem* menuitem = (MenuItem*)psender;

	if (isMusicPlayed)
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		SimpleAudioEngine::getInstance()->pauseAllEffects();
	}
	else
	{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		SimpleAudioEngine::getInstance()->resumeAllEffects();
	}
	isMusicPlayed = !(isMusicPlayed);
}

void MainGame:: playObjectMusic(int music_tag)
{
	switch (music_tag)
	{
	case 1:
	{CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("object1.wav", false);

	}
	break;
	case 2:
	{CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("object2.mp3", false);
	}
	break;
	case 3:
	{CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("object3.mp3", false);
	}
	break;
	}
}

