#include "GlobalTipScene.h"
#include "TitleScene.h"
#include "ui/cocosGUI.h"

USING_NS_CC;

using namespace ui;

// there's no 'id' in cpp, so we recommend returning the class instance pointer
Scene* GlobalTipScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GlobalTipScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool GlobalTipScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create("global_tip.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	Size szContent = sprite->getContentSize();
	float scale = visibleSize.width / szContent.width;
	sprite->setScale( scale );
    this->addChild(sprite, 0);

	//淡入效果
	this->setOpacity(0);
	this->setCascadeOpacityEnabled(true);
	CCFadeIn *action2 = CCFadeIn::create(1);
	this->runAction(action2);
// 	CCFadeOut *action = CCFadeOut::create(1/*0.5f*/);	//淡出
// 	this->runAction(action);

	schedule(schedule_selector(GlobalTipScene::TimeAction), 3/*, kRepeatForever, 0*/);
//	schedule(schedule_selector(GlobalTipScene::TimeClose), 4/*, kRepeatForever, 0*/);
	
    return true;
}

void GlobalTipScene::TimeAction(float dt)
{
// 	static int i = 0;
// 	CCLOG("Custom%d",++i);
	CCFadeOut *action = CCFadeOut::create(1/*0.5f*/);	//淡出
 	this->runAction(action);

	TimeClose(dt);
}

void GlobalTipScene::TimeClose(float dt)
{
//	this->stopAllActions();
	auto scene = TitleScene::createScene();
	if (!scene)
		return;
	auto director = Director::getInstance();
	director->pushScene(scene);
}
