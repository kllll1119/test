#ifndef __SPLASHSCENE_H__
#define	_SPLASHSCENE_H__

#include "cocos2d.h"
#include "LabelRPG.h"
#include "ui/cocosGUI.h"
#include "ui/UIWidget.h"

USING_NS_CC;

using namespace ui;

class SplashScene :	public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int index);

	static SplashScene* instance();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void InitAllUI();	//显示主游戏界面

	void FirstGame();

	void AutoSave();
	void LoadSave(int index);

	void PlayWav(std::string wav);
	void PlayMisic(std::string music);
	void StopMisic();
    
    // a selector callback
	void ScreenClick(cocos2d::Ref* pSender);

    void TalkBKClick(cocos2d::Ref* pSender, Widget::TouchEventType type);

	void TalkOverCB(int event);

	void ScreenShark(int stength=8,int count=10, float duration=0.01f);	//屏幕晃动,stength强度>0

	void BtnClick(cocos2d::Ref* pSender, Widget::TouchEventType type);

	void BtnSave(cocos2d::Ref* pSender, Widget::TouchEventType type);

	void ChangeBackgroup(std::string backgroud,float delay=0.5f);

	void DelayAddEvent(float duration=0.0f);

    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);

public:
	std::string m_backgroud;
	std::string m_music;
	std::string m_wav;
	int m_lastChoose = -1;
	int m_curEvent = 0;	//当前event

private:
	void update(float delta);

	void showText();

	int initok = 0;

	int m_runEvent = 0;	//执行的event

	int m_bTalking = 0;

	ImageView* m_TouXiangLeft=NULL;		//头像左
	//ImageView* m_TouXiangRight = NULL;	//头像右

	ImageView* m_mask = NULL;

	ImageView* m_GetItem = NULL;

	LabelRPG* m_labTalk=NULL;
	Sprite* m_btnok=NULL;
	RepeatForever* m_btnAction=NULL;

	Button* m_btnDhk=NULL;	//对话框背景
	Button* m_btnChoose1 = NULL;	//选项
	Button* m_btnChoose2 = NULL;
	Button* m_btnChoose3 = NULL;

	Button* m_btnSave = NULL;

	LabelRPG* m_lab1 = NULL;
	LabelRPG* m_lab2 = NULL;
	LabelRPG* m_lab3 = NULL;

	LabelRPG* m_firstTips = NULL;

	ImageView* m_pBackgroud = NULL;

	int delay_count = 0;
};

#endif