#include "SplashScene.h"
#include "tools/HLStringUtil.h"
#include "SimpleAudioEngine.h"
#include "SaveScene.h"

using namespace CocosDenshion;

int g_LoadIndex = -1;
SplashScene* g_spInstance = NULL;

// there's no 'id' in cpp, so we recommend returning the class instance pointer
Scene* SplashScene::createScene(int index)
{
	g_LoadIndex = index;
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	g_spInstance = layer;
    // return the scene
    return scene;
}

SplashScene* SplashScene::instance()
{
	return g_spInstance;
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_pBackgroud = ImageView::create("bk_null.png");
	m_pBackgroud->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	Size szContent = m_pBackgroud->getContentSize();
	this->addChild(m_pBackgroud, ZORDER_BK);

	if (g_LoadIndex>=0)
	{
		LoadSave(g_LoadIndex);
	}
	else
	{
		FirstGame();
	}
  
    return true;
}

void SplashScene::InitAllUI()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//对话框背景
	m_btnDhk = Button::create("dhk.png", "dhk.png");
	m_btnDhk->setPosition(Vec2(visibleSize.width / 2 + origin.x, 0));
	Size szContent = m_btnDhk->getContentSize();
	float scale = visibleSize.width / szContent.width;
	m_btnDhk->setScale(scale);
	m_btnDhk->setAnchorPoint(Vec2(0.5, 0));
	m_btnDhk->setTouchEnabled(false);
	m_btnDhk->addTouchEventListener(CC_CALLBACK_2(SplashScene::TalkBKClick, this));
	this->addChild(m_btnDhk, ZORDER_DHK);

	//对话人物左
	m_TouXiangLeft = ImageView::create("zy1.png");
	m_TouXiangLeft->setPosition(Vec2(0, 0));
	m_TouXiangLeft->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_TouXiangLeft, ZORDER_TX);
	m_TouXiangLeft->setVisible(false);

	//人物右
// 	m_TouXiangRight = ImageView::create("npc1.png");
// 	m_TouXiangRight->setPosition(Vec2(visibleSize.width-172, 0));
// 	m_TouXiangRight->setFlippedX(true);	//翻转
// 	m_TouXiangRight->setAnchorPoint(Vec2(1, 0));
// 	this->addChild(m_TouXiangRight, ZORDER_TX);
// 	m_TouXiangRight->setVisible(false);

	m_GetItem = ImageView::create("slz.png");
	m_GetItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
	m_GetItem->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(m_GetItem, ZORDER_GETITEM);
	m_GetItem->setVisible(false);

	m_mask = ImageView::create("mask1.png");
	m_mask->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	m_mask->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(m_mask, ZOORDER_MASK);
	m_mask->setVisible(false);

	//对话文字
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "23hwxw.ttf";
	ttfConfig.fontSize = 24;
	ttfConfig.distanceFieldEnabled = false;
	ttfConfig.outlineSize = 0;// 10;描边
	ttfConfig.glyphs = GlyphCollection::ASCII;
	ttfConfig.customGlyphs = nullptr;
	m_labTalk = LabelRPG::createWithTTF(ttfConfig, "");
	//lab->setColor(Color3B(255,255,255));
	m_labTalk->SetOverCallBack(std::bind(&SplashScene::TalkOverCB, this, std::placeholders::_1));

	m_labTalk->setOriginalPosition(Vec2(175, 130));
	this->addChild(m_labTalk, ZORDER_WZ);


	//右下角按钮
	m_btnok = Sprite::create("btn_ok.png");
	m_btnok->setPosition(Vec2(visibleSize.width - 70, 10));
	m_btnok->setAnchorPoint(Vec2(1, 0));
	this->addChild(m_btnok, ZORDER_BTN);
	m_btnok->setVisible(false);
	CCMoveBy* btnmove = CCMoveBy::create(0.4f, ccp(0, 3));	//循环上下移动
	m_btnAction = CCRepeatForever::create(static_cast<CCSequence *>(CCSequence::create(btnmove, btnmove->reverse(), NULL)));
	m_btnok->runAction(m_btnAction);

	//选项
	Color3B clolorChoose = Color3B(255, 255, 255);
	m_btnChoose1 = Button::create("choose.png", "choose.png");
	m_btnChoose1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height - 150));
	m_btnChoose1->setAnchorPoint(Vec2(0.5, 0));
	ttfConfig.fontSize = 18;
	ttfConfig.outlineSize = 1;
	m_lab1 = LabelRPG::createWithTTF(ttfConfig, Tips::GetCHString("choose1"));
	m_lab1->setColor(clolorChoose);
	m_lab1->setPosition(m_btnChoose1->getContentSize().width / 2, m_btnChoose1->getContentSize().height / 2);
	m_btnChoose1->addChild(m_lab1);
	m_btnChoose1->addTouchEventListener(CC_CALLBACK_2(SplashScene::BtnClick, this));

	m_btnChoose2 = Button::create("choose.png", "choose.png");
	m_btnChoose2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height - 220));
	m_btnChoose2->setAnchorPoint(Vec2(0.5, 0));
	m_btnChoose2->addTouchEventListener(CC_CALLBACK_2(SplashScene::BtnClick, this));
	m_lab2 = LabelRPG::createWithTTF(ttfConfig, Tips::GetCHString("choose2"));
	m_lab2->setColor(clolorChoose);
	m_lab2->setPosition(m_btnChoose2->getContentSize().width / 2, m_btnChoose2->getContentSize().height / 2);
	m_btnChoose2->addChild(m_lab2);

	m_btnChoose3 = Button::create("choose.png", "choose.png");
	m_btnChoose3->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height - 290));
	m_btnChoose3->setAnchorPoint(Vec2(0.5, 0));
	m_btnChoose3->addTouchEventListener(CC_CALLBACK_2(SplashScene::BtnClick, this));
	m_lab3 = LabelRPG::createWithTTF(ttfConfig, Tips::GetCHString("choose3"));
	m_lab3->setColor(clolorChoose);
	m_lab3->setPosition(m_btnChoose3->getContentSize().width / 2, m_btnChoose3->getContentSize().height / 2);
	m_btnChoose3->addChild(m_lab3);

	m_btnChoose1->setVisible(false);
	m_btnChoose2->setVisible(false);
	m_btnChoose3->setVisible(false);
	this->addChild(m_btnChoose1, ZORDER_CHOOSE);
	this->addChild(m_btnChoose2, ZORDER_CHOOSE);
	this->addChild(m_btnChoose3, ZORDER_CHOOSE);

	//保存
	m_btnSave = Button::create("save.png", "save.png");
	m_btnSave->setPosition(Vec2(visibleSize.width - 60, visibleSize.height - 60));
	m_btnSave->setAnchorPoint(Vec2(0, 0));
	m_btnSave->addTouchEventListener(CC_CALLBACK_2(SplashScene::BtnSave, this));
	this->addChild(m_btnSave, ZORDER_CHOOSE);

	scheduleUpdate();
	initok = true;
}

void SplashScene::FirstGame()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//显示首次游戏界面
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "23hwxw.ttf";
	ttfConfig.fontSize = 20;
	ttfConfig.distanceFieldEnabled = false;
	ttfConfig.outlineSize = 0;// 10;描边
	ttfConfig.glyphs = GlyphCollection::ASCII;
	ttfConfig.customGlyphs = nullptr;
	m_firstTips = LabelRPG::createWithTTF(ttfConfig, "");
	m_firstTips->setColor(Color3B(240, 240, 240));
	m_firstTips->setStringWithRunText(-1, Tips::GetCHString("first"), 0.05f);
	m_firstTips->setOriginalPosition(Vec2(visibleSize.width / 2 - 150, visibleSize.height / 2 + 50));
	this->addChild(m_firstTips, ZORDER_WZ);

	AutoSave(); //清除存档
	scheduleOnce([&](float dt)
	{
		m_pBackgroud->setTouchEnabled(true);
		m_pBackgroud->addClickEventListener(CC_CALLBACK_1(SplashScene::ScreenClick, this));
	}, 2.0f, "FirstGame");
}

void SplashScene::AutoSave()
{
	Save(5);
}

void SplashScene::LoadSave(int index)
{
	//加载event点和场景音乐
	char event[20] = { 0 };
	char bk[20] = { 0 };
	char music[20] = { 0 };
	char chs[20] = { 0 };
	snprintf(event, 20 - 1, "event%d", index);
	snprintf(bk, 20 - 1, "bk%d", index);
	snprintf(music, 20 - 1, "music%d", index);
	snprintf(chs, 20 - 1, "chs%d", index);
	m_curEvent = UserDefault->getIntegerForKey(event);
	m_backgroud = UserDefault->getStringForKey(bk);
	m_music = UserDefault->getStringForKey(music);
	m_lastChoose = UserDefault->getIntegerForKey(chs);
	ChangeBackgroup(m_backgroud);
	PlayMisic(m_music);
	if (m_curEvent <= 0)
		FirstGame();
	else
		InitAllUI();
}

void SplashScene::PlayWav(std::string wav)
{
	m_wav = wav;
	scheduleOnce([&](float dt)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(m_wav.c_str());
	}, 0.5f, "PlayWav");	//执行一次
}

void SplashScene::PlayMisic(std::string music)
{
	StopMisic();
	m_music = music;
	scheduleOnce([&](float dt)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(m_music.c_str(), true);
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.2f);
	}, 2.0f, "PlayMisic");	//执行一次
}

void SplashScene::StopMisic()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}

void SplashScene::ScreenClick(cocos2d::Ref* pSender)
{
	m_pBackgroud->setTouchEnabled(false);
	this->removeChild(m_firstTips);
	m_curEvent = atoi(Tips::GetCHString("debug_start").c_str());	//调试
	if (m_curEvent <= 0)
		m_curEvent = 1;	//1;初始id
	InitAllUI();
}

void SplashScene::TalkBKClick(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		if (m_bTalking == 0)
		{
			m_btnDhk->setTouchEnabled(false);
			DelayAddEvent();
		}
		CCLOG("TalkBKClick m_bTalking:%d", m_bTalking);
	}
}


void SplashScene::TalkOverCB(int event)
{
	CCLOG("TalkOverCB event:%d", event);
	m_bTalking = 0;
	m_btnok->setVisible(true);	//显示
	m_btnDhk->setTouchEnabled(true);
}

void SplashScene::ScreenShark(int stength, int count, float duration)
{
	if (stength <= 1)
		stength = 2;
	float randx = fgRangeRand(1, stength);
	float randy = fgRangeRand(1, stength);
	CCMoveBy* btnmove1 = CCMoveBy::create(duration, ccp(0, randy));
	CCMoveBy* btnmove2 = CCMoveBy::create(duration, ccp(randx, randy));
	CCMoveBy* btnmove3 = CCMoveBy::create(duration, ccp(randx, 0));
	CCMoveBy* btnmove4 = CCMoveBy::create(duration, ccp(randx, randy));
	runAction(Repeat::create(static_cast<CCSequence *>(CCSequence::create(
		btnmove1, btnmove4->reverse(),
		btnmove2, btnmove3->reverse(),
		btnmove3, btnmove2->reverse(),
		btnmove4, btnmove1->reverse(),
		NULL)), count));
}

void SplashScene::BtnClick(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
	int id = -1;
	if (type == Widget::TouchEventType::ENDED)	//触摸结束（在控件内抬起）
	{
		SimpleAudioEngine::sharedEngine()->playEffect("wav/al.wav");
		Button* clickedBtn = (Button*)pSender;
		if (clickedBtn)
		{
			m_btnChoose1->setVisible(false);
			m_btnChoose2->setVisible(false);
			m_btnChoose3->setVisible(false);

			ST_EventInfo info;
			if (GetEventInfoEx(m_curEvent, info))
			{
				int id = (int)clickedBtn->getUserData();
				m_lastChoose = id;
				if (info.vecChoose.size()-1 >= id)
				{
					if (!info.vecChoose[id].bk.empty())
						ChangeBackgroup(info.vecChoose[id].bk);

					if (info.vecChoose[id].gotoEvent > 0)
					{
						m_curEvent = info.vecChoose[id].gotoEvent;
						return;
					}
				}
			}
			DelayAddEvent();
		}
	}
}

void SplashScene::BtnSave(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("wav/al.wav");
		auto scene = SaveScene::createScene(true);
		Director::getInstance()->runWithScene(scene);
	}
}

void SplashScene::ChangeBackgroup(std::string backgroud,float delay)
{
	m_backgroud = backgroud;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_pBackgroud->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));	//恢复坐标
	if (delay < 0.5f)
	{
		m_pBackgroud->loadTexture(m_backgroud);
		CCFadeIn *action2 = CCFadeIn::create(1.0f);
		m_pBackgroud->runAction(action2);
	}
	else
	{
		CCFadeOut *action2 = CCFadeOut::create(0.5f);
		m_pBackgroud->runAction(action2);
		scheduleOnce([&](float dt)
		{
			m_pBackgroud->loadTexture(m_backgroud);
			m_pBackgroud->setOpacity(0);
			CCFadeIn *action2 = CCFadeIn::create(1.0f);
			m_pBackgroud->runAction(action2);
		}, delay, "ChangeBackgroup");	//执行一次
	}
}

void SplashScene::DelayAddEvent(float duration/*=2.0f*/)
{
	ST_EventInfo info;
	if (GetEventInfoEx(m_curEvent, info))
	{
		if (info.gotoEvent > 0)
		{
			m_curEvent = info.gotoEvent;
		}
		else
			++m_curEvent;
		CCLOG("DelayAddEvent m_curEvent:%d,gotoEvent:%d", m_curEvent, info.gotoEvent);
	}
	else
	{
		++m_curEvent;
		CCLOG("DelayAddEvent2 m_curEvent:%d", m_curEvent);
	}
// 	{
// 		schedule([&](float dt)
// 		{
// 			unschedule("DelayAddEvent");
// 			++m_curEvent;
// 			CCLOG("DelayAddEvent m_curEvent:%d",m_curEvent);
// 		}, duration, 1, 0.0f, "DelayAddEvent");	//CC_REPEAT_FOREVER，可执行多次
// 	}
}

void SplashScene::update(float delta)
{
//	CCLOG("update:%.2f", delta);
	if (delay_count++ % 30 != 0)
		return;
	if (initok && m_runEvent != m_curEvent)
	{
		m_bTalking = 1;
		m_btnok->setVisible(false);	//隐藏

		m_btnDhk->setTouchEnabled(false);
		m_runEvent = m_curEvent;

		ST_EventInfo info;
		if (GetEventInfoEx(m_curEvent, info))
		{
			if (!info.bk.empty())
				ChangeBackgroup(info.bk, info.bktime);

			if (!info.muisc.empty())
				PlayMisic(info.muisc);

			if (!info.wav.empty())
				PlayWav(info.wav);

			if (!info.tag.empty())
				m_tag = info.tag;

			if (!info.item.empty())
			{
				m_GetItem->loadTexture(info.item);
				m_GetItem->setVisible(true);
			}
			else
				m_GetItem->setVisible(false);

			if (!info.bk.empty())
			{
				scheduleOnce([&](float dt)
				{
					showText();
				}, 1.5f,"showText");	//CC_REPEAT_FOREVER，可执行多次
			}
			else
			{
				showText();
			}
		}
		else
		{
			CCLOG("[err]none Event:%d", m_curEvent);
			//++m_curEvent;	//暂不自动跳过空事件
		}
	}
	else
		CCLOG("curEvent:%d", m_curEvent);
}

void SplashScene::showText()
{
	CCLOG("showText:%d", m_curEvent);
	ST_EventInfo info;
	if (GetEventInfoEx(m_curEvent, info))
	{
		if (info.shark > 0)
		{
			ScreenShark(10, info.shark);
		}

		if (!info.mask.empty())
		{
			m_mask->loadTexture(info.mask);
			m_mask->setVisible(true);
			schedule([&](float dt)
			{
				m_mask->setVisible(false);
			}, 0.2f, 1, 0.0f, "mask");	//CC_REPEAT_FOREVER，可执行多次
		}

		if (info.bkx != 0 || info.bky != 0)
		{
			CCMoveBy* btnmove = CCMoveBy::create(2.0f, ccp(info.bkx, info.bky));
			m_pBackgroud->runAction(btnmove);
		}

		int cbEvent = m_curEvent;
		if (info.mv>0.01f)
		{
			cbEvent = -1;
			scheduleOnce([&](float dt)
			{
				++m_curEvent;
			}, info.mv, "mv");	//CC_REPEAT_FOREVER，可执行多次
		}

		if (info.role == ROLE_CHOOSE)	//选项
		{
			m_btnChoose1->setVisible(false);
			m_btnChoose2->setVisible(false);
			m_btnChoose3->setVisible(false);
			for (int i = 0; i < info.vecChoose.size(); ++i)	//目前暂时最多3项
			{
				if (i == 0)
				{
					m_lab1->setString(Tips::GetCHString(info.vecChoose[i].key));
					m_btnChoose1->setUserData((void*)0);
					m_btnChoose1->setVisible(true);
				}
				else if (i == 1)
				{
					m_lab2->setString(Tips::GetCHString(info.vecChoose[i].key));
					m_btnChoose2->setUserData((void*)1);
					m_btnChoose2->setVisible(true);
				}
				else
				{
					m_lab3->setString(Tips::GetCHString(info.vecChoose[i].key));
					m_btnChoose3->setUserData((void*)2);
					m_btnChoose3->setVisible(true);
				}
			}
			return;
		}

		m_TouXiangLeft->setVisible(false);
		//m_TouXiangRight->setVisible(false);
		Size visibleSize = Director::getInstance()->getVisibleSize();
		if (!info.ico.empty())
		{
			m_TouXiangLeft->loadTexture(info.ico);
			m_TouXiangLeft->setVisible(true);
		}
		auto *chnStrings = Dictionary::createWithContentsOfFile(XML_CH_CFG);
		if (chnStrings)
		{
			char buf[20] = { 0 };
			if (m_lastChoose >= 0)
			{
				snprintf(buf, 20 - 1, "%d_%d", m_runEvent, m_lastChoose);
				String* str = static_cast<String*>(chnStrings->objectForKey(buf));	//尝试寻找分支，找不到就重置分支
				if (str == NULL)
				{
					snprintf(buf, 20 - 1, "%d", m_runEvent);
					m_lastChoose = -1;
				}
			}
			else
			{
				snprintf(buf, 20 - 1, "%d", m_runEvent);
			}
			String* str = static_cast<String*>(chnStrings->objectForKey(buf));
			if (str && str->length()>0)
			{
				m_btnDhk->setVisible(true);
				m_labTalk->setStringWithRunText(cbEvent, str->getCString(), 0.05f);
				
			}
			else
			{
				m_labTalk->setString("");
				m_btnDhk->setVisible(false);
				CCLOG("[warn]text null:%d", m_curEvent);
			}
		}
		if (info.mv < 0.001f)
			AutoSave();
	}
}
