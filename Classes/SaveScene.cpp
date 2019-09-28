#include "SaveScene.h"
#include "SplashScene.h"
#include "ui/cocosGUI.h"
#include "SimpleAudioEngine.h"
#include "tools/HLStringUtil.h"

USING_NS_CC;

bool g_bSave = false;	//是否是保存模式

using namespace CocosDenshion;
using namespace ui;

// there's no 'id' in cpp, so we recommend returning the class instance pointer
Scene* SaveScene::createScene(bool saveMode)
{
	g_bSave = saveMode;
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SaveScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

	
    // return the scene
    return scene;
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool SaveScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->setCascadeOpacityEnabled(true);

    auto sprite = Sprite::create("save_bk.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	Size szContent = sprite->getContentSize();
	float scale = visibleSize.width / szContent.width;
	sprite->setScale(scale);
    this->addChild(sprite, 0);

	int startYpos = 300;
	int xDistance = 230;
	int yDistance = 180;
	for (int i=0; i<6; ++i)
	{
		Button* pItem = Button::create("save_item(161_90).png", "save_item(161_90).png");
		pItem->setAnchorPoint(Vec2(0.5, 0));
		pItem->setUserData((void*)-1);
		if (i ==0)	//上排
		{
			pItem->setPosition(Vec2(visibleSize.width / 2 + origin.x - xDistance, startYpos));
		}
		else if (i == 1)
		{
			pItem->setPosition(Vec2(visibleSize.width / 2 + origin.x + 0, startYpos));
		}
		else if (i == 2)
		{
			pItem->setPosition(Vec2(visibleSize.width / 2 + origin.x + xDistance, startYpos));
		}
		else if (i == 3)	//下排
		{
			pItem->setPosition(Vec2(visibleSize.width / 2 + origin.x - xDistance, startYpos- yDistance));
		}
		else if (i == 4)
		{
			pItem->setPosition(Vec2(visibleSize.width / 2 + origin.x + 0, startYpos - yDistance));
		}
		else //5暂定为系统自动存档
		{
			pItem->setPosition(Vec2(visibleSize.width / 2 + origin.x + xDistance, startYpos - yDistance));
		}

		char bk[20] = { 0 };
		char tm[20] = { 0 };
		snprintf(bk, 20 - 1, "bk%d", i);
		snprintf(tm, 20 - 1, "tm%d", i);
		std::string backgroud = UserDefault->getStringForKey(bk);
		std::string time = UserDefault->getStringForKey(tm);
		if (!backgroud.empty())	//如果有存档，显示相关图片
		{
			ImageView* pImg = ImageView::create(backgroud);
			pImg->setPosition(Vec2(17,23));
			pImg->setAnchorPoint(Vec2(0, 0));
			float scale =  161/ visibleSize.width;
			pImg->setScale(scale);
			pItem->addChild(pImg, 2);
			if (i == 5)
			{
				ImageView* pSysTip = ImageView::create("save_sys.png");
				pSysTip->setPosition(Vec2(55, 55));
				pSysTip->setAnchorPoint(Vec2(0, 0));
				pItem->addChild(pSysTip, 3);
			}
			if (!time.empty())
			{	//time
				TTFConfig ttfConfig;
				ttfConfig.fontFilePath = "23hwxw.ttf";
				ttfConfig.fontSize = 13;
				ttfConfig.distanceFieldEnabled = false;
				ttfConfig.outlineSize = 1;
				ttfConfig.glyphs = GlyphCollection::ASCII;
				ttfConfig.customGlyphs = nullptr;
				LabelRPG* pTime = LabelRPG::createWithTTF(ttfConfig, "", cocos2d::TextHAlignment::LEFT);
				//pTime->setColor(Color3B(225, 127, 39));
				pTime->setColor(Color3B(255, 255, 255));
				//pTime->setStringWithRunText(-1, time, 0.01f);
				pTime->setString(time);
				pTime->setPosition(Vec2(100, 10));
				//pTime->setOriginalPosition(Vec2(100, 10));
				pItem->addChild(pTime,4);
			}
			pItem->setUserData((void*)i);
		}
		if (g_bSave)
		{
			if(i == 5)
				pItem->setUserData((void*)-1);
			else
				pItem->setUserData((void*)i);
		}
		pItem->addTouchEventListener(CC_CALLBACK_2(SaveScene::BtnItemClick, this));
		this->addChild(pItem, 1);
	}

	Button* pClose = Button::create("close.png", "close.png");
	pClose->setAnchorPoint(Vec2(0.5, 0));
	pClose->setPosition(Vec2(visibleSize.width-55, 15));
	pClose->addTouchEventListener(CC_CALLBACK_2(SaveScene::BtnItemClose, this));
	this->addChild(pClose, 1);
    return true;
}

void Save(int index)
{
	char event[20] = { 0 };
	char bk[20] = { 0 };
	char music[20] = { 0 };
	char chs[20] = { 0 };
	char tm[20] = { 0 };
	snprintf(event, 20 - 1, "event%d", index);
	snprintf(bk, 20 - 1, "bk%d", index);
	snprintf(music, 20 - 1, "music%d", index);
	snprintf(chs, 20 - 1, "chs%d", index);
	snprintf(tm, 20 - 1, "tm%d", index);
	SplashScene* spIns = SplashScene::instance();
	if (spIns)
	{
		UserDefault->setIntegerForKey(event, spIns->m_curEvent);
		UserDefault->setStringForKey(bk, spIns->m_backgroud);
		UserDefault->setStringForKey(music, spIns->m_music);
		UserDefault->setIntegerForKey(chs, spIns->m_lastChoose);
		UserDefault->setStringForKey(tm, GetCurTime());
	}
}

void SaveScene::BtnItemClick(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		int index = -1;
		Button* pItem = (Button*)pSender;
		if (pItem)
		{
			index = (int)pItem->getUserData();
		}
		CCLOG("load save,index:%d", index);
		SimpleAudioEngine::sharedEngine()->playEffect("wav/al.wav");
		if (index >= 0)
		{
			if (g_bSave)	//保存
			{
				Save(index);
				stopAllActions();
				Director::getInstance()->popScene();
			}
			else  //读取
			{
				auto scene = SplashScene::createScene(index);
				Director::getInstance()->runWithScene(scene);
			}
		}
	}
}

void SaveScene::BtnItemClose(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("wav/al.wav");
		stopAllActions();
		onExit();
		Director::getInstance()->popScene();
	}
}
