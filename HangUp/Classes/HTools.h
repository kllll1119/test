#pragma once
#include <cocos2d.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <2d/CCNode.h>
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;
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

bool testReadNpc();

int MakeRandom(int min, int max);