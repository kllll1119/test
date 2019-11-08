///////////////////////////////////////////////
//������by:����   QQ:414755548
//���Ǹս���˾�Ĳ���,������кõ�˼·,��ӭΪС���ṩһЩ����ͽ���,лл!!
///////////////////////////////////////////////
#include "GameScene.h"
#include "Player.h"

#define CCPointZero ccp(0,0)

Player* TestPlayer = NULL;

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

	//���볡��
	ImageView* m_bk = ImageView::create("bk1.png");
	m_bk->setPosition(Vec2(0, 0));
	m_bk->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_bk, 0);

	//�����ɫ
	addChild(Player::create(Player::HERO, 1, 0));
	addChild(Player::create(Player::HERO, 1, 1));
	addChild(Player::create(Player::HERO, 1, 2));
	addChild(Player::create(Player::HERO, 1, 3));
	addChild(Player::create(Player::HERO, 1, 4));
	addChild(Player::create(Player::HERO, 1, 5));
	addChild(Player::create(Player::HERO, 1, 6));
	addChild(Player::create(Player::HERO, 1, 7));
	addChild(Player::create(Player::HERO, 1, 8));

	addChild(Player::create(Player::ENEMY, 2, 0));
	addChild(Player::create(Player::ENEMY, 2, 1));
	addChild(Player::create(Player::ENEMY, 2, 2));
	addChild(Player::create(Player::ENEMY, 2, 3));
	addChild(Player::create(Player::ENEMY, 2, 4));
	addChild(Player::create(Player::ENEMY, 2, 5));
	addChild(Player::create(Player::ENEMY, 2, 6));
	addChild(Player::create(Player::ENEMY, 2, 7));

	TestPlayer = Player::create(Player::ENEMY, 2, 8);
	addChild(TestPlayer);

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
	if (count++ == 50)
		TestPlayer->Die();
}
