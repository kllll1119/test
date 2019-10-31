///////////////////////////////////////////////
//制作者by:旋风   QQ:414755548
//我是刚进公司的菜鸟,如果你有好的思路,欢迎为小弟提供一些意见和交流,谢谢!!
///////////////////////////////////////////////
#include "GameScene.h"
#include "HTools.h"

#define CCPointZero ccp(0,0)

int yOffset = -20;
int xOffset = 100;

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

Sprite* InitRole(int index)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int xpos = 100;
	std::string name = "npc1.png";
	if (index == 2)
	{
		name = "npc2.png";
	}
	Sprite* sp1 = Sprite::create();
	sp1->initWithFile(name);

	if (index == 2)
	{
		xpos = visibleSize.width - xpos - sp1->getContentSize().width;
		sp1->setFlipX(true);
	}
	sp1->setPosition(ccp(xpos, visibleSize.height / 2));
	sp1->setAnchorPoint(Vec2(0, 0.5));

	CCScaleTo* btnmove = ScaleTo::create(2.0f, 1.0f, 0.95f);	//循环放大缩小
	CCScaleTo* btnmove2 = ScaleTo::create(2.0f, 1.0f, 1.0f);	
	CCRepeatForever* m_btnAction = CCRepeatForever::create(static_cast<CCSequence *>(CCSequence::create(btnmove, btnmove2/*btnmove->reverse()*/, NULL)));
	sp1->runAction(m_btnAction);
	return sp1;
}

bool GameScene::init(){
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	addChild(InitRole(1));
	addChild(InitRole(2));

	testReadNpc();
	return true;
}

void GameScene::onEnter(){
	CCLayer::onEnter();
}

void GameScene::onExit(){
	CCLayer::onExit();
}