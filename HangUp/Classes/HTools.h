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

#define ZORDER_BOTTOM 0			//�ײ�
#define ZORDER_BK 1				//����
#define ZORDER_DHK 10			//�Ի��򱳾�
#define ZORDER_TX 11			//����ͷ��
#define ZORDER_WZ 11			//����
#define ZORDER_BTN 11			//�����ť
#define ZORDER_GETITEM 12		//��õ���
#define ZORDER_CHOOSE 20		//ѡ��
#define ZOORDER_MASK 100		//mask

#define UserDefault CCUserDefault::sharedUserDefault()

class Tips : public Node
{
public:
	static string GetCHString(string key);
};

class FlowWord : public CCNode {
public:
	void showWord(const char* text, CCPoint pos,Color3B color,int size = 12);//Ʈ�ַ�����textΪƮ�ֵ����ݣ�posΪƮ�ֵ�λ��
private:
	CCLabelTTF* label;//���Ա
	void flowEnd();//Ʈ�ֽ���ʱ�Ļص���������������Ҫ����ɾ���Լ�	
};

struct ST_FighterAttr
{
	int m_hp=100;				//Ѫ
	int m_attck=0;			//����
	int m_defense=0;			//����
	int m_dodge=0;			//����
};

enum FighterType { HERO = 0, ENEMY = 1 };

ST_FighterAttr GetFighterAttr(FighterType type,int id);

int MakeRandom(int min, int max);
std::vector<int> MakeRandomIndex1_9(int count);
std::vector<int> MakeRandomIds(int count,vector<int> ids);