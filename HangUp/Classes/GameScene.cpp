///////////////////////////////////////////////
//制作者by:旋风   QQ:414755548
//我是刚进公司的菜鸟,如果你有好的思路,欢迎为小弟提供一些意见和交流,谢谢!!
///////////////////////////////////////////////
#include "GameScene.h"
#include "GameLogicManager.h"

#define CCPointZero ccp(0,0)

Fighter* testPlayer = NULL;
Fighter* testEneme = NULL;

GameScene::GameScene(){
}
GameScene::~GameScene(){
}

Scene* GameScene::scene(){
	Scene* scene = Scene::create();
	GameScene * gameLayer = GameScene::create();
	scene->addChild(gameLayer);
	return scene;
}

bool GameScene::init(){
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//载入场景
	ImageView* m_bk = ImageView::create("bk1.png");
	m_bk->setPosition(Vec2(0, 0));
	m_bk->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_bk, 0);

	//载入主界面遮挡
	ImageView* m_bkMan = ImageView::create("bkman.png");
	m_bkMan->setPosition(Vec2(0, 0));
	m_bkMan->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_bkMan, 1);

	//载入角色
	addChild(Fighter::create(Fighter::HERO, 1, 0));
	addChild(Fighter::create(Fighter::HERO, 1, 1));
	addChild(Fighter::create(Fighter::HERO, 1, 2));
	addChild(Fighter::create(Fighter::HERO, 1, 3));
	addChild(Fighter::create(Fighter::HERO, 1, 4));
	addChild(Fighter::create(Fighter::HERO, 1, 5));
	addChild(Fighter::create(Fighter::HERO, 1, 6));
	addChild(Fighter::create(Fighter::HERO, 1, 7));

	testPlayer = Fighter::create(Fighter::HERO, 1, 8);
	addChild(testPlayer);

	addChild(Fighter::create(Fighter::ENEMY, 2, 0));
	addChild(Fighter::create(Fighter::ENEMY, 2, 1));
	addChild(Fighter::create(Fighter::ENEMY, 2, 2));
	addChild(Fighter::create(Fighter::ENEMY, 2, 3));
	addChild(Fighter::create(Fighter::ENEMY, 2, 4));
	addChild(Fighter::create(Fighter::ENEMY, 2, 5));
	addChild(Fighter::create(Fighter::ENEMY, 2, 6));
	addChild(Fighter::create(Fighter::ENEMY, 2, 7));

	testEneme = Fighter::create(Fighter::ENEMY, 2, 8);
	addChild(testEneme);

	testReadNpc();

	scheduleUpdate();
	return true;
}

void GameScene::onEnter(){
	CCLayer::onEnter();
}

void GameScene::onExit(){
	CCLayer::onExit();
}

void GameScene::update(float delta)
{
	//CCLOG("update:%.2f", delta);
	static int count = 0;
	count++;
	if (count%50==0)
	{
		if (testEneme->m_curHp > 0)
		{
			int att = 0;
			bool bj = false;
			testPlayer->Attack(att, bj);

			if(count>200)
				testEneme->OnHurt(50, true);
			else
				testEneme->OnHurt(50, false);
		}
	}

// 	if (count == 100)
// 	{
// 		int att = 0;
// 		bool bj = false;
// 		testEneme->Attack(att, bj);
// 		//TestPlayer->Die();
// 	}
}
