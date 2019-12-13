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

// �ֱ���
// �ܶ�����             ����ķֱ��ʣ�px�� ��Ļ�����ܶȣ�dpi��
// ���ܶȣ�ldpi��       240x320             120
// ���ܶȣ�mdpi��       320x480             160
// ���ܶȣ�hdpi��       480x800             240
// �����ܶȣ�xhdpi��    720x1280           320
// �������ܶȣ�xxhdpi�� 1080x1920          480

USING_NS_CC;
using namespace ui;
using namespace std;

#define XML_CFG "hu.xml"
#define XML_STAGE "stage.xml"

#define ZORDER_BK 0				//����
#define ZORDER_BK_MASK 1		//����mask
#define ZORDER_MAIN 2			//������
#define ZORDER_S_FIGHT 10		//����
#define ZORDER_MAIN_TIP 90		//��������ʾ

#define UserDefault CCUserDefault::sharedUserDefault()

class Tips : public Node
{
public:
	static string GetCHString(string key,string xml= XML_CFG);
};

class FlowWord : public CCNode {
public:
	void showWord(const char* text, CCPoint pos,Color3B color,int size = 18);//Ʈ�ַ�����textΪƮ�ֵ����ݣ�posΪƮ�ֵ�λ��
	void showSkillWord(const char* text, CCPoint pos, Color3B color, int size = 14);
private:
//	CCLabelTTF* label;//���Ա
	void flowEnd(Node* lable);//Ʈ�ֽ���ʱ�Ļص���������������Ҫ����ɾ���Լ�	
	void flowSkillEnd(Node* lable);
};

enum SkillArea
{
	EM_NOMAL,	//����
	EM_HOR,		//��
	EM_VEC,		//��
	EM_ALL,		//ȫ��
};

struct ST_FighterSkill
{
	ST_FighterSkill()
	{
		at = 0;
	}
	string skillName;	//��������
	SkillArea area;		//��������
	int at;				//������%
	int lv;				//Ҫ��ȼ�
	int turn;			//�����غ�
};

struct ST_FighterAttr
{
	string m_name;						//����
	int m_hp = 0;						//Ѫ
	int m_attck= 0;						//����
	int m_defense = 0;					//����
	int m_bj = 0;						//����(1-100)
	int m_dodge=0;						//����(1-100)
	int m_money = 0;					//��Ǯ
	int m_bl = 0;						//����(1-100)
	vector<ST_FighterSkill> vecSkill;	//
};

enum FighterType { HERO = 0, ENEMY = 1 };

ST_FighterAttr GetFighterAttr(FighterType type,int id);	//���ö�ȡ����

std::vector<string> GetEnemys(int stage);		//���ö�ȡ����
std::vector<string> GetEnemysBoss(int stage);	//���ö�ȡ����boss

void TSplit(std::vector<string>& vecRet, const string& strSrc, string strSplit);
	

int MakeRandom(int min, int max);
std::vector<int> MakeRandomIndex1_9(int count);
std::vector<int> MakeRandomIds(int count,vector<int> ids);

int Random0_100();

#define JsonChkObj(value, strKey) (value.HasMember(strKey)) 
#define JsonGetString(value, strKey) (JsonChkObj(value, strKey)? value[strKey].GetString() : "")
#define JsonGetInt(value, strKey) (JsonChkObj(value, strKey)? value[strKey].GetInt() : 0)
#define JsonGetInt2(value, strKey,val) (JsonChkObj(value, strKey)? value[strKey].GetInt() : val)
