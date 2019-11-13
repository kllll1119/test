#pragma once
#include <cocos2d.h>
#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>
#include <ctype.h>
#include <2d/CCNode.h>
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "ui/cocosGUI.h"
#include "ui/UIWidget.h"

USING_NS_CC;
using namespace ui;
using namespace std;

#define XML_CH_CFG "hu.xml"

#define ZORDER_BOTTOM 0			//底层
#define ZORDER_BK 1				//背景
#define ZORDER_DHK 10			//对话框背景
#define ZORDER_TX 11			//人物头像
#define ZORDER_WZ 11			//文字
#define ZORDER_BTN 11			//点击按钮
#define ZORDER_GETITEM 12		//获得道具
#define ZORDER_CHOOSE 20		//选择
#define ZOORDER_MASK 100		//mask

#define UserDefault CCUserDefault::sharedUserDefault()

class Tips : public Node
{
public:
	static string GetCHString(string key);
};

class FlowWord : public CCNode {
public:
	void showWord(const char* text, CCPoint pos,Color3B color,int size = 12);//飘字方法，text为飘字的内容，pos为飘字的位置
private:
	CCLabelTTF* label;//类成员
	void flowEnd();//飘字结束时的回调（处理）函数，主要用于删除自己	
};

struct ST_FighterAttr
{
	int m_hp=100;				//血
	int m_attck=0;			//攻击
	int m_defense=0;			//防御
	int m_dodge=0;			//闪避
};

enum FighterType { HERO = 0, ENEMY = 1 };

ST_FighterAttr GetFighterAttr(FighterType type,int id);

int MakeRandom(int min, int max);
std::vector<int> MakeRandomIndex1_9(int count);
std::vector<int> MakeRandomIds(int count,vector<int> ids);