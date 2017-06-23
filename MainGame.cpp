#pragma once
#include "MainGame.h"
#include "GamePause.h"
#define WORLDTAG 1000
#define anchor1_TAG 100
#define anchor2_TAG 200

bool isMusicPlayed = true;
vector<Vec2> obj_position;

CCLabelTTF * totalScoreLB;
CCLabelTTF * crumpLB;
CCLabelTTF * waterLB;
//炸弹数目
int crump_number = 0;
//加速水数目
int water_number = 0;
int target_score = 0;
Score score;
int level = 0;
int nST = 0;
int nSG = 0;
int nD = 0;
int nBT = 0;
int nW = 0;
int nBG = 0;
int nMG = 0;
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
	nST = 0;
	nSG = 0;
	nD = 0;
	nBT = 0;
	nW = 0;
	nBG = 0;
	nMG = 0;
	isMusicPlayed=true;
	SimpleAudioEngine::getInstance()->playBackgroundMusic("backgroundMusic.wav", true);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	level++;
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameObjects.plist", "gameObjects.png");
	if (level == 1)    *(score.getScore()) = 0;
	//设置背景
	char background[10] = { '\0' };
	sprintf(background, "BG%d.png", level%3);
	auto sprite1 = Sprite::create(background);
	// position the sprite on the center of the screen
	//	sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//Size mywinsize = Director::getInstance()->getWinSize();
	//float winw = mywinsize.width; //获取屏幕宽度
	//float winh = mywinsize.height;//获取屏幕高度
	//float spx = sprite1->getTextureRect().getMaxX();
	//float spy = sprite1->getTextureRect().getMaxY();
	//sprite1->setScaleX(winw / spx); //设置精灵宽度缩放比例
	//sprite1->setScaleY(winh / spy);
	 //add the sprite as a child to this layer
	//this->addChild(sprite1, 0);//改为自己的图片
	
	auto visibleSize2 = Director::sharedDirector()->getWinSize();
	Size bgSize = sprite1->getContentSize();
	sprite1->setScale(visibleSize2.width / bgSize.width, visibleSize2.height / bgSize.height);
	sprite1->setPosition(visibleSize2.width*0.5, visibleSize2.height*0.5);
	this->addChild(sprite1);
	

	auto score_picture = Sprite::create("score.png");
	score_picture->setPosition(Vec2((visibleSize.width)*0.08f, (visibleSize.height)*0.95f));
	addChild(score_picture);
	Size size4 = score_picture->getContentSize();

	float scaleX4 = (float)size4.width*1.5f / (float)size4.width;
	float scaleY4 = (float)size4.height*1.5f / (float)size4.height;
	score_picture->setScale(scaleX4, scaleY4);

	char str[50] = { '\0' };
	sprintf(str, "%d", score);
	totalScoreLB = CCLabelTTF::create(str, "Zapfino", 13);
	//score_picture->addChild(totalScoreLB);
	//totalScoreLB->setAnchorPoint(Vec2(0.5, 1));
	totalScoreLB->setPosition((visibleSize.width)*0.087, (visibleSize.height));
	totalScoreLB->setColor(Color3B::BLACK);
	this->addChild(totalScoreLB);
	//totalScoreLB->setColor(ccc3(200, 20, 255));

	char* target = new char[6];

	switch (level)
	{
	case 1:
		target_score = 650;
		break;
	case 2:
		target_score = 1195;
		break;
	case 3:
		target_score = 2010;
		break;
	case 4:
		target_score = 3095;
		break;
	case 5:
		target_score = 4450;
		break;
	}
	sprintf(target, "%d", target_score);
	auto label = Label::createWithSystemFont(target, "Arial", 13);
	label->setPosition(Vec2((visibleSize.width)*0.087, (visibleSize.height)*0.927));
	label->setColor(Color3B::BLACK);
	this->addChild(label);

	//倒计时装置60s
	TimeSchedule1 * m_timer = TimeSchedule1::createTimer(*(score.getSD()) == 1 ? 60 : 40);
	m_timer->setPosition(Vec2((visibleSize.width)*0.925, (visibleSize.height)*0.894));
	this->addChild(m_timer, 10);

	auto leveltime = Sprite::create("level-time.png");
	leveltime->setPosition(Vec2((visibleSize.width)*0.92, (visibleSize.height)*0.95));
	Size size5 = leveltime->getContentSize();

	float scaleX5 = (float)size5.width*1.7f / (float)size5.width;
	float scaleY5 = (float)size5.height*1.7f / (float)size5.height;
	leveltime->setScale(scaleX5, scaleY5);
	leveltime->setScale(scaleX5, scaleY5);
	addChild(leveltime, 6);

	char str_level[3] = { '\0' };
	sprintf(str_level, "%d", level);
	auto slevel = CCLabelTTF::create(str_level, "Zapfino", 11);
	slevel->setPosition(Vec2((visibleSize.width)*0.925, (visibleSize.height)*0.973));
	slevel->setColor(Color3B::BLACK);
	this->addChild(slevel, 7);
	//设置暂停装置
	Button* pauseButton = Button::create("Pause_on.png", "Pause_off.png");
	pauseButton->setPosition(Vec2((visibleSize.width)*0.8, (visibleSize.height)*0.97));
	pauseButton->addTouchEventListener([=](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			CCDirector::sharedDirector()->pause();
			gamepause = GamePause::create();
			addChild(gamepause, 20);
		}

	});

	Size size2 = pauseButton->getContentSize();
	float scaleX2 = (float)size2.width*0.5f / (float)size2.width;
	float scaleY2 = (float)size2.height*0.5f / (float)size2.height;
	pauseButton->setScale(scaleX2, scaleY2);
	addChild(pauseButton);
	//恢复游戏监听事件
	_eventDispatcher->addCustomEventListener("goOnGame", [=](EventCustom*evn) {
		CCDirector::sharedDirector()->resume();
		gamepause->removeFromParentAndCleanup(true);
	});
	//waterlabel
	if (water_number != 0)
	{
		CCSprite* WATER = CCSprite::create("waterlabel.png");
		this->addChild(WATER);
		WATER->setPosition(Vec2((visibleSize.width)*0.7, (visibleSize.height)*0.88));
	}
	//炸弹图标
	CCSprite* crumplabel = CCSprite::create("crumplabel.png");
	crumplabel->setPosition(Vec2((visibleSize.width)*0.7, (visibleSize.height)*0.97));
	this->addChild(crumplabel);

	char str_crump[10] = { '\0' };
	sprintf(str_crump, "%d", crump_number);
	crumpLB = CCLabelTTF::create(str_crump, "Zapfino", 15);
	crumpLB->setPosition(Vec2((visibleSize.width)*0.75, (visibleSize.height)*0.97));
	this->addChild(crumpLB);
	//炸弹图标
	Size size1 = crumplabel->getContentSize();

	float scaleX1 = (float)size1.width*0.4f / (float)size1.width;
	float scaleY1 = (float)size1.height*0.4f / (float)size1.height;
	crumplabel->setScale(scaleX1, scaleY1);

	
	//背景音乐
	//播放选项
	Button* music = Button::create("Music_on.png", "Music_off.png");
	music->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.88));
	addChild(music);
	music->addTouchEventListener([=](Ref*pSender, Widget::TouchEventType type)
	{  
		if (type == Widget::TouchEventType::ENDED)
		{
		
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

	});
	
	//**************暂时设置图标大小****************************
	size1 = music->getContentSize();
	scaleX1 = (float)size1.width*0.5f / (float)size1.width;
	scaleY1 = (float)size1.height*0.5f / (float)size1.height;
	music->setScale(scaleX1, scaleY1);
	
	//获取绳和钩子的长和宽
	Rope1* rope = new Rope1();
	rope->set_p(this);
	rope->set_Rope1Height(rope->getContentSize().height);
	rope->set_Rope1Width(rope->getContentSize().width);
	rope->getInitRope1Height();
	//放置绳子

	if (*(score.getSD()) == 1)  rope->setPosition(Vec2((visibleSize.width)*0.5, (visibleSize.height)*0.9));
	else rope->setPosition(Vec2((visibleSize.width)*0.6, (visibleSize.height)*0.9));
	rope->setAnchorPoint(Vec2(0.3, 1));
	this->addChild(rope, 10);
	CCSprite* anchor = CCSprite::create("anchor.png");
	rope->addChild(anchor);
	anchor->setName("anchor");
	anchor->setTag(anchor1_TAG);
	anchor->setAnchorPoint(Vec2(0.5, 1));
	rope->set_isRope1Changing(false);
	rope->runRope1ShakeClaw();//绳子摆动
	PhysicsBody *body = PhysicsBody::createEdgeBox(Size(anchor->getContentSize()));
	body->setCategoryBitmask(10);
	body->setCollisionBitmask(10);
	body->setContactTestBitmask(10);
	anchor->setPhysicsBody(body);

	//添加矿工
	CCSprite* miner = CCSprite::create("Miner_1.png");
	miner->setName("Miner");
	if (*(score.getSD()) == 0) miner->setPosition((visibleSize.width)*0.6, (visibleSize.height) *0.93);
	else miner->setPosition((visibleSize.width)*0.5, (visibleSize.height) *0.93);
	this->addChild(miner);

	CCSprite* miner2 = CCSprite::create("Miner_1.png");
	miner2->setName("Miner2");
	miner2->setPosition((visibleSize.width)*0.4, (visibleSize.height) *0.93);
	//放置第二个绳子
	Rope1* rope2 = new Rope1();
	rope2->set_p(this);
	rope2->set_Rope1Height(rope2->getContentSize().height);
	rope2->set_Rope1Width(rope2->getContentSize().width);
	rope2->getInitRope1Height();
	//放置绳子

	rope2->setPosition(Vec2((visibleSize.width)*0.4, (visibleSize.height)*0.9));
	rope2->setAnchorPoint(Vec2(0.3, 1));
	CCSprite* anchor2 = CCSprite::create("anchor.png");
	anchor2->setName("anchor2");
	anchor2->setTag(anchor2_TAG);
	anchor2->setAnchorPoint(Vec2(0.5, 1));
	rope2->set_isRope1Changing(false);
	rope2->runRope1ShakeClaw();//绳子摆动
	PhysicsBody *body2 = PhysicsBody::createEdgeBox(Size(anchor2->getContentSize()));
	body2->setCategoryBitmask(10);
	body2->setCollisionBitmask(10);
	body2->setContactTestBitmask(10);
	anchor2->setPhysicsBody(body2);

	if (*(score.getSD()) == 0) {

		this->addChild(miner2);
		this->addChild(rope2);
		rope2->addChild(anchor2);
		//将锚设置为刚体

		//设置第二个绳子的各种动作

		auto listener2 = EventListenerKeyboard::create();
		listener2->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event)
		{
			if (keycode == EventKeyboard::KeyCode::KEY_S)
			{
				if (!(rope2->get_isRope1Changing()))
				{
					rope2->stopRope1ShakeAction();
					rope2->runRope1Throw(1.0);
				}


			}
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
		auto Presslistener2 = EventListenerKeyboard::create();
		Presslistener2->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event)
		{
			if (keycode == EventKeyboard::KeyCode::KEY_W)
			{

				//判断绳子上是否有物体
				if (!anchor2->getChildren().empty() && crump_number != 0)
				{
					rope2->reset_random_objtag();
					rope2->set_addedscore(0);
					this->use_crump2(rope2);

					rope2->runRope2Pull(50.0);
				}
			}
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(Presslistener2, this);
	}

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


		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//碰撞检测
	switch (level)
	{
	case 1:
	obj_position = { Vec2(0.9,0.4),Vec2(0.1,0.45),Vec2(0.52,0.3),Vec2(0.55,0.4), Vec2(0.3,0.35),
	Vec2(0.23,0.6), Vec2(0.28,0.55),Vec2(0.45,0.5), Vec2(0.6,0.53),Vec2(0.8,0.58),
	Vec2(0.25,0.48), Vec2(0.85,0.56),Vec2(0.42,0.17), Vec2(0.75,0.4),Vec2(0.37,0.15) };
	addObject("wallet", 1);
	addObject("big_stone", 2);
	addObject("small_stone", 2);
	addObject("small_gold", 5);
	addObject("middle_gold", 3);
	addObject("big_gold", 2);
	break;
	case 2:
	obj_position = { Vec2(0.1,0.25),Vec2(0.635,0.17), Vec2(0.2,0.56), Vec2(0.3,0.3), Vec2(0.54,0.275),
	Vec2(0.72,0.15), Vec2(0.42,0.273), Vec2(0.67,0.5), Vec2(0.76,0.62), Vec2(0.1,0.58),
	Vec2(0.8,0.2), Vec2(0.2,0.27), Vec2(0.38,0.35), Vec2(0.48,0.56), Vec2(0.56,0.47),
	Vec2(0.7,0.3), Vec2(0.72,0.65), Vec2(0.76,0.46), Vec2(0.655,0.4), Vec2(0.37,0.23) };
	addObject("wallet", 1);
	addObject("diamond", 1);
	addObject("small_gold", 7);
	addObject("middle_gold", 2);
	addObject("small_stone", 3);
	addObject("big_stone", 4);
	addObject("big_gold", 2);
	break;
	case 3:
	obj_position = {
	Vec2(0.2,0.25),
	Vec2(0.3,0.15),
	Vec2(0.2,0.7), Vec2(0.2,0.62), Vec2(0.25,0.68), Vec2(0.65,0.54),
	Vec2(0.15,0.665),
	Vec2(0.5,0.56),Vec2(0.7,0.5),Vec2(0.76,0.4),
	Vec2(0.25,0.4),Vec2(0.7,0.4),Vec2(0.81,0.5),Vec2(0.82,0.35),
	Vec2(0.17,0.52),Vec2(0.65,0.16),Vec2(0.9,0.6),
	Vec2(0.75,0.47),
	};
	addObject("diamond", 1);
	addObject("middle_gold", 3);
	addObject("big_stone", 4);
	addObject("small_stone", 3);
	addObject("wallet", 1);
	addObject("small_gold", 4);
	addObject("big_gold", 1);
	addObject("pig", 1);
	break;
	case 4:
	obj_position = {
	Vec2(0.2,0.55),Vec2(0.8,0.3),
	Vec2(0.8,0.17),
	Vec2(0.24,0.65), Vec2(0.43,0.45), Vec2(0.53,0.15),
	Vec2(0.26,0.43), Vec2(0.59,0.63), Vec2(0.76,0.68),
	Vec2(0.23,0.16), Vec2(0.62,0.15), Vec2(0.63,0.4),
	Vec2(0.23,0.47), Vec2(0.33,0.42), Vec2(0.38,0.17), Vec2(0.67,0.47), Vec2(0.72,0.45), Vec2(0.76,0.48), Vec2(0.8,0.44),
	Vec2(0.64,0.61),
	};
	//addObject("pig", 3);
	addObject("wallet", 1);
	addObject("small_gold", 7);
	addObject("middle_gold", 3);
	addObject("small_stone", 3);
	addObject("big_stone", 3);
	addObject("big_gold", 1);
	addObject("pig", 2);
	break;
	case 5:
	obj_position = {
	Vec2(0.2,0.3),
	Vec2(0.1,0.3),Vec2(0.45,0.15), Vec2(0.55,0.2), Vec2(0.8,0.15),
	Vec2(0.18,0.5), Vec2(0.35,0.55), Vec2(0.82,0.6),
	Vec2(0.21,0.63), Vec2(0.25,0.2), Vec2(0.42,0.4), Vec2(0.58,0.47),
	Vec2(0.26,0.55), Vec2(0.33,0.43), Vec2(0.75,0.55),
	Vec2(0.53,0.48),
	Vec2(0.15,0.4), Vec2(0.48,0.37), Vec2(0.8,0.45),
	Vec2(0.7,0.6),
	Vec2(0.65,0.17),
	Vec2(0.46,0.5),
	};

	addObject("TNT", 1);
	addObject("TNT2", 1);
	addObject("wallet", 1);
	addObject("diamond", 3);
	addObject("small_stone", 1);
	addObject("big_stone", 3);
	addObject("small_gold", 4);
	addObject("middle_gold", 3);
	addObject("big_gold", 4);
	addObject("pig", 1);
	break;
	}


	auto physicListener = EventListenerPhysicsContact::create();
	physicListener->onContactBegin = [=](PhysicsContact &contact)
	{
		float weight = 70.0;
		int addedscore = 0;
		auto sth = contact.getShapeB()->getBody()->getNode();
		if (sth->getTag() != WORLDTAG && (sth->getTag() == anchor2_TAG || sth->getTag() == anchor1_TAG)) {};
		//if (anchor->getChildren().empty()) {
			
			
			if (sth->getTag() != WORLDTAG&&sth->getTag() != anchor2_TAG&&contact.getShapeA()->getBody()->getNode()->getTag() == anchor1_TAG)
			{

				int music_tag = 0;
				string name = sth->getName();
				if (name == "TNT")
				{
					weight = 60;
					rope->set_addedscore(1);
					auto thing1 = getChildByTag(11);
					if (thing1)    thing1->removeFromParent();
					auto thing2 = getChildByTag(31);
					if (thing2)    thing2->removeFromParent();
					auto thing3 = getChildByTag(32);
					if (thing3)    thing3->removeFromParent();
					auto thing4 = getChildByTag(62);
					if (thing4)    thing4->removeFromParent();
					CCPoint position = sth->getPosition();
					sth->removeFromParent();
					TNTboom(position);
				}
				if (name == "TNT2")
				{
					weight = 60;
					rope->set_addedscore(1);
					auto thing1 = getChildByTag(51);
					if (thing1)    thing1->removeFromParent();
					auto thing2 = getChildByTag(52);
					if (thing2)    thing2->removeFromParent();
					CCPoint position = sth->getPosition();
					sth->removeFromParent();
					TNTboom(position);
				}
				if (name == "small_stone")
				{
					weight = 650;
					rope->set_addedscore(11);
					music_tag = 1;
				}
				if (name == "big_stone")
				{
					weight = 900;
					rope->set_addedscore(20);
					music_tag = 1;
				}
				if (name == "small_gold")
				{
					weight = 250;
					rope->set_addedscore(50);
					music_tag = 2;
				}
				if (name == "middle_gold")
				{
					weight = 450;
					rope->set_addedscore(100);
					music_tag = 2;
				}
				if (name == "big_gold")
				{
					weight = 900;
					rope->set_addedscore(500);
					music_tag = 3;
				}
				if (name == "diamond")
				{
					weight = 60.0;
					rope->set_addedscore(600);
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
					rope->set_addedscore(602);
					music_tag = 1;
				}
				if (contact.getShapeA()->getBody()->getNode()->getTag() == anchor1_TAG)
					if (name != "TNT"&&name != "TNT2")
					{
						rope->addObjectToRope1(name, anchor);//新建
						sth->removeFromParent();//移除
					}
				weight *= water_number == 0 ? 1 : 0.2;
				rope->runRope1Pull(weight);
				if (isMusicPlayed)
					playObjectMusic(music_tag);
			}
		//}
		//if (anchor2->getChildren().empty()&&(*(score.getSD())==0)) {
			if (sth->getTag() != WORLDTAG&&sth->getTag() != anchor1_TAG&&contact.getShapeA()->getBody()->getNode()->getTag() == anchor2_TAG)
			{
				int music_tag = 0;
				string name = sth->getName();
				if (name == "TNT")
				{
					weight = 60;
					rope->set_addedscore(1);
					auto thing1 = getChildByTag(11);
					if (thing1)    thing1->removeFromParent();
					auto thing2 = getChildByTag(31);
					if (thing2)    thing2->removeFromParent();
					auto thing3 = getChildByTag(32);
					if (thing3)    thing3->removeFromParent();
					auto thing4 = getChildByTag(62);
					if (thing4)    thing4->removeFromParent();
					CCPoint position = sth->getPosition();
					sth->removeFromParent();
					TNTboom(position);
				}
				if (name == "TNT2")
				{
					weight = 60;
					rope->set_addedscore(1);
					auto thing1 = getChildByTag(51);
					if (thing1)    thing1->removeFromParent();
					auto thing2 = getChildByTag(52);
					if (thing2)    thing2->removeFromParent();
					CCPoint position = sth->getPosition();
					sth->removeFromParent();
					TNTboom(position);

				}
				if (name == "small_stone")
				{
					weight = 650;
					rope2->set_addedscore(11);
					music_tag = 1;
				}
				if (name == "big_stone")
				{
					weight = 900;
					rope2->set_addedscore(20);
					music_tag = 1;
				}
				if (name == "small_gold")
				{
					weight = 250;
					rope2->set_addedscore(50);
					music_tag = 2;
				}
				if (name == "middle_gold")
				{
					weight = 450;
					rope2->set_addedscore(100);
					music_tag = 2;
				}
				if (name == "big_gold")
				{
					weight = 900;
					rope2->set_addedscore(500);
					music_tag = 3;
				}
				if (name == "diamond")
				{
					weight = 60.0;
					rope2->set_addedscore(600);
					music_tag = 3;
				}
				if (name == "wallet")
				{
					weight = 100.0;
					rope2->walletRope1_catched();
					music_tag = 2;
				}
				if (name == "pig")
				{
					weight = 60.0;
					rope2->set_addedscore(602);
					music_tag = 1;
				}
				if (contact.getShapeA()->getBody()->getNode()->getTag() == anchor2_TAG)
					if (name != "TNT"&&name != "TNT2")
					{
						rope2->addObjectToRope1(name, anchor2);//新建
						sth->removeFromParent();//移除
					}
				weight *= water_number == 0 ? 1 : 0.2;
				rope2->runRope2Pull(weight);
				sth->removeFromParent();//移除
				if (isMusicPlayed)
					playObjectMusic(music_tag);
		//	}
		}
		if (contact.getShapeA()->getBody()->getNode()->getTag() == anchor1_TAG&&sth->getTag() == WORLDTAG)
			rope->runRope1Pull(weight);
		if (contact.getShapeA()->getBody()->getNode()->getTag() == anchor2_TAG &&sth->getTag() == WORLDTAG)
			rope2->runRope2Pull(weight);
			
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

	return true;
}
inline void MainGame::addObject(std::string type, int number)
{
	for (int i = 0; i < number; ++i)
	{
		object* sth = object::create(type, false);
		this->addChild(sth, 8);
	}

}



void MainGame::_spriteMoveFinished(cocos2d::CCNode *sender) {
	CCSprite *sprite = (CCSprite *)sender;
	this->removeChild(sprite, true);
}

inline void object::makePosition(ObjectType object_type, object* _object)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	Vec2 _pos = *(obj_position.end() - 1);
	this->setPosition(CCPointMake(_pos.x*winSize.width, _pos.y*winSize.height));
	obj_position.pop_back();
	//}
	//break;
	//}
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
	else if (type == "TNT")
		object_type = TNT;
	else if (type == "TNT2")
		object_type = TNT2;
	else if (type == "pig")
		object_type = pig;
	switch (object_type)
	{
	case TNT:
	{
		this->initWithFile("TNT.png");
		setName("TNT");
		if (!isCatched)
		{
			this->makePosition(TNT, this);
			setObjectAsPhysicsBody(this);

		}
	}
	break;
	case TNT2:
	{
		this->initWithFile("TNT.png");

		setName("TNT2");
		if (!isCatched)
		{
			this->makePosition(TNT2, this);
			setObjectAsPhysicsBody(this);

		}
	}
	break;
	case small_stone:
	{this->initWithFile("small_stone.png");
	nST++;
	setTag(10 + nST);
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
	Scale(this, big_stone);
	nBT++;
	setTag(20 + nBT);
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
	Scale(this, small_gold);
	nSG++;
	setTag(30 + nSG);
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
	nMG++;
	setTag(40 + nMG);
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
	Scale(this, big_gold);
	nBG++;
	setTag(50 + nBG);
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

	nD++;
	setTag(60 + nD);
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
	nW++;
	setTag(70 + nW);
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

	if (!isCatched)
	{
		this->makePosition(pig, this);
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
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
		CCFiniteTimeAction *actionmove1 = CCMoveTo::create(12.0, CCPointMake((winSize.width)*0.8, this->getPosition().y));


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
		Repeat* _action2 = Repeat::create(action2, 20);
		CCFiniteTimeAction *actionmove2 = CCMoveTo::create(12.0, CCPointMake((winSize.width)*0.2, this->getPosition().y));
		auto pigX = this->getPosition().x;
		if (pigX == 0.2*winSize.width)
		{
			this->runAction(RepeatForever::create(CCSequence::create(actionmove1, actionmove2, NULL)));
			this->runAction(RepeatForever::create(CCSequence::create(_action1, _action2, NULL)));  // 运行精灵对象
		}
		else
		{
			this->runAction(RepeatForever::create(CCSequence::create(actionmove2, actionmove1, NULL)));
			this->runAction(RepeatForever::create(CCSequence::create(_action2, _action1, NULL)));  // 运行精灵对象

		}
	};
	}
	break;
	default:
		break;
	}
	return true;
}
inline void object::Scale(object* _object, ObjectType _objectType)
{
	float scale = 0;

	Size size = _object->getContentSize();
	switch (_objectType)
	{
	case big_stone:
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
	float scaleY = (float)size.height*scale / (float)size.height;
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
	auto anchor_size = anchor->getContentSize();
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
	Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	auto visibleSize = Director::sharedDirector()->getWinSize();
	Rope1Height -= 1;
	unsigned int effect_id = 0;
//	if (isMusicPlayed)
	//	effect_id = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ropePull.wav", true);
	auto anchor = this->getChildByName("anchor");
	auto body = anchor->getPhysicsBody();
	body->removeFromWorld();

	if (Rope1Height <= 20)
	{
		auto miner = _layer->getChildByName("Miner");
		miner->stopAllActions();
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseEffect(effect_id);
		unschedule(CC_SCHEDULE_SELECTOR(Rope1::reduceRope1Height));//停止调用
		Rope1Height = initRope1Height;
		_isRope1Changing = false;

		anchor->removeAllChildren();
		this->runRope1ShakeClaw();
		PhysicsBody *newbody = PhysicsBody::createEdgeBox(Size(anchor->getContentSize()));
		newbody->setCategoryBitmask(10);
		newbody->setCollisionBitmask(10);
		newbody->setContactTestBitmask(10);
		anchor->setPhysicsBody(newbody);
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
			CCFiniteTimeAction *move = CCMoveTo::create(0.5, Vec2((visibleSize.width)*0.7, (visibleSize.height)*0.97));
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
				waterlabel->setPosition(Vec2((visibleSize.width)*0.7, (visibleSize.height)*0.88));
				_layer->addChild(waterlabel);
				Size size2 = waterlabel->getContentSize();
				float scaleX2 = (float)size2.width / (float)size2.width;
				float scaleY2 = (float)size2.height / (float)size2.height;
				waterlabel->setScale(scaleX2, scaleY2);
			}

			CCSprite* get_water = CCSprite::create("waterlabel.png");
			_layer->addChild(get_water);
			get_water->setPosition(Vec2((visibleSize.width)*0.5, (visibleSize.height)*0.5));
			CCFiniteTimeAction *move = CCMoveTo::create(0.5, CCPointMake((visibleSize.width)*0.7, (visibleSize.height)*0.88));
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
		if (addedscore != 0 && isMusicPlayed)
			SimpleAudioEngine::getInstance()->playEffect("addMoney.mp3", false);
		*(score.getScore()) += addedscore;
		addedscore = 0;
		char str_2[50] = { '\0' };
		sprintf(str_2, "%d", score);
		totalScoreLB->setString(str_2);

		random_objtag = 0;
	}
	this->setContentSize(Size(Rope1Width, Rope1Height));
}
//回收绳子


void Rope1::runRope2Pull(float weight)
{
	float time = weight*0.0001;
	auto miner = _layer->getChildByName("Miner2");
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
	schedule(CC_SCHEDULE_SELECTOR(Rope1::reduceRope2Height), time);
	unschedule(CC_SCHEDULE_SELECTOR(Rope1::addRope1Height));
}//消除绳子的刚体性质


void Rope1::reduceRope2Height(float)//
{
	auto visibleSize = Director::sharedDirector()->getWinSize();
	Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	Rope1Height -= 1;
	unsigned int effect_id = 0;
	//if (isMusicPlayed)
		//effect_id = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ropePull.wav", true);
	auto anchor = this->getChildByName("anchor2");
	auto body = anchor->getPhysicsBody();
	body->removeFromWorld();


	if (Rope1Height <= 20)
	{
		auto miner = _layer->getChildByName("Miner2");
		miner->stopAllActions();
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseEffect(effect_id);
		unschedule(CC_SCHEDULE_SELECTOR(Rope1::reduceRope2Height));//停止调用
		Rope1Height = initRope1Height;
		_isRope1Changing = false;

		anchor->removeAllChildren();
		this->runRope1ShakeClaw();
		PhysicsBody *newbody = PhysicsBody::createEdgeBox(Size(anchor->getContentSize()));
		newbody->setCategoryBitmask(10);
		newbody->setCollisionBitmask(10);
		newbody->setContactTestBitmask(10);
		anchor->setPhysicsBody(newbody);
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
			get_crump->setPosition(Vec2((visibleSize.width)*0.5, (visibleSize.height)*0.5));
			CCFiniteTimeAction *move = CCMoveTo::create(0.5, Vec2((visibleSize.width)*0.7, (visibleSize.height)*0.97));
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
				waterlabel->setPosition(Vec2((visibleSize.width)*0.7, (visibleSize.height)*0.88));
				_layer->addChild(waterlabel);
				Size size2 = waterlabel->getContentSize();
				float scaleX2 = (float)size2.width / (float)size2.width;
				float scaleY2 = (float)size2.height / (float)size2.height;
				waterlabel->setScale(scaleX2, scaleY2);
			}

			CCSprite* get_water = CCSprite::create("waterlabel.png");
			_layer->addChild(get_water);
			get_water->setPosition(Vec2((visibleSize.width)*0.5, (visibleSize.height)*0.5));
			CCFiniteTimeAction *move = CCMoveTo::create(0.5, CCPointMake((visibleSize.width)*0.7, (visibleSize.height)*0.88));
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
		if (addedscore != 0 && isMusicPlayed)
			SimpleAudioEngine::getInstance()->playEffect("addMoney.mp3", false);
		*(score.getScore()) += addedscore;
		addedscore = 0;
		char str_2[50] = { '\0' };
		sprintf(str_2, "%d", score);
		totalScoreLB->setString(str_2);

		random_objtag = 0;
	}
	this->setContentSize(Size(Rope1Width, Rope1Height));
}

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
	random_objtag = rand() % 3 + 1;

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

	CCFiniteTimeAction *crumpmove = CCMoveTo::create(0.01, object_position);
	crump->runAction(CCSequence::create(crumpmove, NULL));

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
	crump->runAction(CCSequence::create(crumpmove, boomaction, _removeCrump, NULL));
	if (isMusicPlayed)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("boom.mp3", false);

}


void MainGame::use_crump2(Rope1* rope)
{
	// 移到指定位置
	crump_number -= 1;
	char curnum_crump[10] = { '\0' };
	if (crump_number < 1)
		crump_number = 0;
	sprintf(curnum_crump, "%d", crump_number);
	crumpLB->setString(curnum_crump);
	rope->unschedule(CC_SCHEDULE_SELECTOR(Rope1::reduceRope2Height));
	auto anchor = rope->getChildByName("anchor2");
	auto the_object = *(anchor->getChildren().begin());


	//将相对于绳子坐标转换到世界坐标下
	CCPoint object_position = rope->convertToWorldSpace(the_object->getPosition());

	CCSprite* crump = CCSprite::create();
	crump->initWithFile("crump.png");
	this->addChild(crump, 4);

	crump->setPosition(rope->getPosition());
	anchor->removeAllChildren();

	CCFiniteTimeAction *crumpmove = CCMoveTo::create(0.01, object_position);
	crump->runAction(CCSequence::create(crumpmove, NULL));

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
	crump->runAction(CCSequence::create(crumpmove, boomaction, _removeCrump, NULL));
	if (isMusicPlayed)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("boom.mp3", false);
}

void MainGame::playObjectMusic(int music_tag)
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
//TNT
void MainGame::TNTboom(CCPoint position)
{
	CCSprite* TNTBOOM = CCSprite::create("TNT_1.png");
	CCAnimation * tntBoom = CCAnimation::create();
	this->addChild(TNTBOOM);
	TNTBOOM->setPosition(position);
	for (int i = 1; i <= 10; i+=2)
	{
		char name[50] = { '\0' };
		sprintf(name, "TNT_%d.png", i);
		tntBoom->addSpriteFrameWithFileName(name);
	}
	tntBoom->setDelayPerUnit(0.1);
	CCAnimate * tntBoomAction = CCAnimate::create(tntBoom);
	CCFiniteTimeAction * removeTNT = CCCallFuncN::create(this, callfuncN_selector(MainGame::_spriteMoveFinished));
	TNTBOOM->runAction(CCSequence::create(tntBoomAction, removeTNT, NULL));
	if (isMusicPlayed)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("boom.mp3", false);

}
TimeSchedule1::TimeSchedule1()
{

}

TimeSchedule1::~TimeSchedule1()
{

}

bool TimeSchedule1::init(float time)
{
	pTime = time;
	schedule(schedule_selector(TimeSchedule1::update));

	return true;
}
void TimeSchedule1::update(float delta)
{
	pTime -= delta;
	char* mtime = new char[10];

	//清除上次调用时的label,防止重叠
	this->removeChild(label);

	//此处只是显示分钟数和秒数  自己可以定义输出时间格式
	sprintf(mtime, "%d", (int)pTime % 60);

	//label->setString(mtime);
	label = Label::createWithSystemFont(mtime, "Arial", 13);
	label->setPosition(0, 0);
	//设置倒计时颜色

	label->setColor(Color3B::BLACK);
	this->addChild(label);

	int target = 0;
	switch (level)
	{
	case 1:
		target = 650;
		break;
	case 2:
		target = 1195;
		break;
	case 3:
		target = 2010;
		break;
	case 4:
		target = 3095;
		break;
	case 5:
		target = 4450;
		break;
	}
	//如果时间到了则切换界面
	if ((int)pTime % 60 == 0 && (*score.getScore())<target)
	{
		*(score.getScore()) = 0;
		level = 0;
		auto director = Director::getInstance();
		CCScene *scene = WetherToStartAgain::createScene();
		auto transition = TransitionCrossFade::create(0.5f, scene);
		director->replaceScene(transition);
	}

	if ((int)pTime % 60 == 0 && (*score.getScore()) >= target)
	{
		if (level != 5) {
			auto director = Director::getInstance();
			CCScene *scene = Store::createScene();
			auto transition = TransitionCrossFade::create(0.5f, scene);
			director->replaceScene(transition);
		}
		else {
			auto director = Director::getInstance();
			CCScene *scene = Congratulation::createScene();
			auto transition = TransitionCrossFade::create(0.5f, scene);
			director->replaceScene(transition);
			level = 0;
			*(score.getScore()) = 0;
		}
	}

}

TimeSchedule1* TimeSchedule1::createTimer(float time)
{
	TimeSchedule1* timeSchedule = new TimeSchedule1;
	if (timeSchedule && timeSchedule->init(time))
	{
		timeSchedule->autorelease();
		return timeSchedule;
	}
	else
	{
		delete timeSchedule;
		timeSchedule = NULL;
	}
	return NULL;
}

MainGame::~MainGame()
{
	_eventDispatcher->removeCustomEventListeners("goOnGame");
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	if (level == 0)
	{
		if (*(score.getScore()) == 0)
			SimpleAudioEngine::getInstance()->playBackgroundMusic("pity.wav", false);
		else
			SimpleAudioEngine::getInstance()->playBackgroundMusic("Stage2.wav", false);
	}
	else
		SimpleAudioEngine::getInstance()->playBackgroundMusic("pass.mp3", false);
}







