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

	//if (UserDefault->isXMLFileExist()) //是否存在
	//std::string path = UserDefault->getXMLFilePath();
	//C:/Users/Administrator/AppData/Local/XJ23/UserDefault.xml
    
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
			pItem->setColor(Color3B(200, 50, 150));
			pItem->setPosition(Vec2(visibleSize.width / 2 + origin.x + xDistance, startYpos - yDistance));
		}

		char bk[20] = { 0 };
		char tm[20] = { 0 };
		char tag[20] = { 0 };
		snprintf(bk, 20 - 1, "bk%d", i);
		snprintf(tm, 20 - 1, "tm%d", i);
		snprintf(tag, 20 - 1, "tag%d", i);
		std::string backgroud = UserDefault->getStringForKey(bk);
		std::string time = UserDefault->getStringForKey(tm);
		std::string title = UserDefault->getStringForKey(tag);
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
			TTFConfig ttfConfig;
			ttfConfig.fontFilePath = "23hwxw.ttf";
			ttfConfig.distanceFieldEnabled = false;
			ttfConfig.glyphs = GlyphCollection::ASCII;
			ttfConfig.customGlyphs = nullptr;
			ttfConfig.outlineSize = 2;
			if (!title.empty())
			{
				ttfConfig.fontSize = 15;
				LabelRPG* lab = LabelRPG::createWithTTF(ttfConfig, "", cocos2d::TextHAlignment::CENTER);
				//pTime->setColor(Color3B(225, 127, 39));
				lab->setColor(Color3B(255, 255, 255));
				lab->setString(title);
				lab->setPosition(Vec2(98, 125));
				pItem->addChild(lab, 4);
			}

			if (!time.empty())	//time
			{
				ttfConfig.fontSize = 13;
				LabelRPG* pTime = LabelRPG::createWithTTF(ttfConfig, "", cocos2d::TextHAlignment::LEFT);
				pTime->setColor(Color3B(255, 255, 255));
				pTime->setString(time);
				pTime->setPosition(Vec2(100, 10));
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
		CCLOG("load/save,index:%d", index);
		if (index >= 0)
		{
			if (g_bSave)	//保存
			{
				SimpleAudioEngine::sharedEngine()->playEffect("wav/item.wav");
				Save(index);
				stopAllActions();
				Director::getInstance()->popScene();
			}
			else  //读取
			{
				SimpleAudioEngine::sharedEngine()->playEffect("wav/al.wav");
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
