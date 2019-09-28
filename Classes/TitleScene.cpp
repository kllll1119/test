#include "TitleScene.h"
#include "SplashScene.h"
#include "SaveScene.h"
#include "ui/cocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;
using namespace ui;

// there's no 'id' in cpp, so we recommend returning the class instance pointer
Scene* TitleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TitleScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.2f);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("snd/hmxy_2h.mp3", true);
	
    // return the scene
    return scene;
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool TitleScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->setCascadeOpacityEnabled(true);

    auto sprite = Sprite::create("manbk.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	Size szContent = sprite->getContentSize();
	float scale = visibleSize.width / szContent.width;
	sprite->setScale( scale );
    this->addChild(sprite, 0);

	ImageView *pTitle = ImageView::create("title.png");
	pTitle->setPosition(Vec2(visibleSize.width / 2 + origin.x+10, visibleSize.height-350));
	pTitle->setAnchorPoint(Vec2(0.5f, 0));
	this->addChild(pTitle, 1);

// 	pTitle->setOpacity(0);
// 	CCFadeIn *action = CCFadeIn::create(3);
// 	pTitle->runAction(action);

	CCMoveBy* btnmove = CCMoveBy::create(3.0f, ccp(0, 10));	//循环上下移动
	pTitle->runAction(CCRepeatForever::create(static_cast<CCSequence *>(CCSequence::create(btnmove, btnmove->reverse(), NULL))));

	//淡入效果
 	this->setOpacity(0);
	CCFadeIn *action2 = CCFadeIn::create(1);
	this->runAction(action2);


	Button* pStart = Button::create("btn_start1.png", "btn_start1.png");
	pStart->setPosition(Vec2(visibleSize.width / 2 + origin.x-200, 60));
	pStart->setAnchorPoint(Vec2(0.5, 0));
	pStart->addTouchEventListener(CC_CALLBACK_2(TitleScene::BtnStart, this));
	this->addChild(pStart, 1);

	Button* pLoad = Button::create("btn_load1.png", "btn_load1.png");
	pLoad->setPosition(Vec2(visibleSize.width / 2 + origin.x+20, 60));
	pLoad->setAnchorPoint(Vec2(0.5, 0));
	pLoad->addTouchEventListener(CC_CALLBACK_2(TitleScene::BtnLoad, this));
	this->addChild(pLoad, 1);

	Button* pExit = Button::create("btn_exit.png", "btn_exit.png");
	pExit->setPosition(Vec2(visibleSize.width / 2 + origin.x + 240, 60));
	pExit->setAnchorPoint(Vec2(0.5, 0));
	pExit->addTouchEventListener(CC_CALLBACK_2(TitleScene::BtnExit, this));
	this->addChild(pExit, 1);
    return true;
}

void TitleScene::BtnStart(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("wav/al.wav");
		stopAllActions();
		auto scene = SplashScene::createScene(-1);
		Director::getInstance()->runWithScene(scene);
	}
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}

void TitleScene::BtnLoad(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("wav/al.wav");
		auto scene = SaveScene::createScene(false);
		Director::getInstance()->runWithScene(scene);
	}
}

void TitleScene::BtnExit(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	if (type == Widget::TouchEventType::ENDED)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("wav/al.wav");
		stopAllActions();
		Director::getInstance()->popScene();
		Director::getInstance()->stopAnimation();
	}
}
