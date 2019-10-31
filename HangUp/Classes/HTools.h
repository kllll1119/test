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
	static std::string GetCHString(std::string key)
	{
		try
		{
			auto *chnStrings = Dictionary::createWithContentsOfFile(XML_CH_CFG);	//��ʾ��������
			if (chnStrings)
			{
				String* str = static_cast<String*>(chnStrings->objectForKey(key));
				if (str)
					return str->getCString();
			}
			return "";
		}
		catch (...)
		{
			return "";
		}
	}
};

bool testReadNpc()
{
	string json = Tips::GetCHString("npcs");	//��ȡ�¼������߼�
	if (json.empty())
		return false;

	rapidjson::Document readdoc;
	bool bRet = false;
	ssize_t size = 0;
	readdoc.Parse<0>(json.c_str());
	if (readdoc.HasParseError())
	{
		return false;
	}
	
	if (readdoc.IsArray())
	{
		for (int i = 0; i < readdoc.Capacity(); i++)
		{
			int id = readdoc[i]["id"].GetInt();
			string name = readdoc[i]["name"].GetString();
		}
	}
}