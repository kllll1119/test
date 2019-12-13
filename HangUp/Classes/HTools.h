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

// 分辨率
// 密度类型             代表的分辨率（px） 屏幕像素密度（dpi）
// 低密度（ldpi）       240x320             120
// 中密度（mdpi）       320x480             160
// 高密度（hdpi）       480x800             240
// 超高密度（xhdpi）    720x1280           320
// 超超高密度（xxhdpi） 1080x1920          480

USING_NS_CC;
using namespace ui;
using namespace std;

#define XML_CFG "hu.xml"
#define XML_STAGE "stage.xml"

#define ZORDER_BK 0				//背景
#define ZORDER_BK_MASK 1		//背景mask
#define ZORDER_MAIN 2			//主界面
#define ZORDER_S_FIGHT 10		//人物
#define ZORDER_MAIN_TIP 90		//主界面提示

#define UserDefault CCUserDefault::sharedUserDefault()

class Tips : public Node
{
public:
	static string GetCHString(string key,string xml= XML_CFG);
};

class FlowWord : public CCNode {
public:
	void showWord(const char* text, CCPoint pos,Color3B color,int size = 18);//飘字方法，text为飘字的内容，pos为飘字的位置
	void showSkillWord(const char* text, CCPoint pos, Color3B color, int size = 14);
private:
//	CCLabelTTF* label;//类成员
	void flowEnd(Node* lable);//飘字结束时的回调（处理）函数，主要用于删除自己	
	void flowSkillEnd(Node* lable);
};

enum SkillArea
{
	EM_NOMAL,	//单体
	EM_HOR,		//横
	EM_VEC,		//竖
	EM_ALL,		//全体
};

struct ST_FighterSkill
{
	ST_FighterSkill()
	{
		at = 0;
	}
	string skillName;	//技能名称
	SkillArea area;		//攻击区域
	int at;				//攻击率%
	int lv;				//要求等级
	int turn;			//触发回合
};

struct ST_FighterAttr
{
	string m_name;						//名字
	int m_hp = 0;						//血
	int m_attck= 0;						//攻击
	int m_defense = 0;					//防御
	int m_bj = 0;						//暴击(1-100)
	int m_dodge=0;						//闪避(1-100)
	int m_money = 0;					//金钱
	int m_bl = 0;						//爆率(1-100)
	vector<ST_FighterSkill> vecSkill;	//
};

enum FighterType { HERO = 0, ENEMY = 1 };

ST_FighterAttr GetFighterAttr(FighterType type,int id);	//配置读取属性

std::vector<string> GetEnemys(int stage);		//配置读取怪物
std::vector<string> GetEnemysBoss(int stage);	//配置读取怪物boss

void TSplit(std::vector<string>& vecRet, const string& strSrc, string strSplit);
	

int MakeRandom(int min, int max);
std::vector<int> MakeRandomIndex1_9(int count);
std::vector<int> MakeRandomIds(int count,vector<int> ids);

int Random0_100();

#define JsonChkObj(value, strKey) (value.HasMember(strKey)) 
#define JsonGetString(value, strKey) (JsonChkObj(value, strKey)? value[strKey].GetString() : "")
#define JsonGetInt(value, strKey) (JsonChkObj(value, strKey)? value[strKey].GetInt() : 0)
#define JsonGetInt2(value, strKey,val) (JsonChkObj(value, strKey)? value[strKey].GetInt() : val)
