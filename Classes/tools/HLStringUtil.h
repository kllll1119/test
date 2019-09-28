//
//  HLStringUtil.h
//  HoolaiEngine
//
//  Created by zhao shuan on 13-2-26.
//

#ifndef __HLSTRINGUTIL_H__
#define __HLSTRINGUTIL_H__

#include "cocos2d.h"
#include <string>
#include <vector>
#include <map>
#include <string>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include "2d/CCNode.h"
#include "ui/UIScale9Sprite.h"

USING_NS_CC;

#define XML_CH_CFG "xj23.xml"

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
///////////////////////// 读写示例 ////////////////////////////
//1:设置set
// UserDefault->setBoolForKey("bool", true);
// UserDefault->setIntegerForKey("integer", 100);
// UserDefault->setFloatForKey("float", 33.33f);
// UserDefault->setDoubleForKey("double", 44.44);
// UserDefault->setStringForKey("string", "1111111");

//2:获取get，并输出到控制台,通过关键字，获取数据
// bool b = UserDefault->getBoolForKey("bool");
// int i = UserDefault->getIntegerForKey("integer");
// float f = UserDefault->getFloatForKey("float");
// double d = UserDefault->getDoubleForKey("double");
// string ret = UserDefault->getStringForKey("string");

//3:当set完后，数据不会马上保存到XML文件中，记得flush
//CCUserDefault::sharedUserDefault()->flush();

//3:输出XML文件路径
//if(UserDefault->isXMLFileExist()) //是否存在
//	string path = UserDefault->getXMLFilePath();
//////////////////////////////////////////////////////////////

// namespace StringUtil
// {
//     inline void StringToUpper(std::string& str)
//     {
//         if (str.empty())
//         {
//             return;
//         }
//         
//         size_t size = str.size();
//         for (size_t i = 0; i < size; ++i)
//         {
//             str[i] = toupper(str[i]);
//         }
//     }
//     
//     inline void StringToLower(std::string& str)
//     {
//         if (str.empty())
//         {
//             return;
//         }
//         
//         size_t size = str.size();
//         for (size_t i = 0; i < size; ++i)
//         {
//             str[i] = tolower(str[i]);
//         }
//     }
//     
//     inline std::string& ReplaceAll(std::string& str, const char* toReplace, const char* replace)
//     {
//         size_t pos = str.find(toReplace);
//         size_t len = strlen(toReplace);
//         while (pos != std::string::npos)
//         {
//             str = str.replace(pos, len, replace);
//             pos = str.find(toReplace);
//         }
//         return str;
//     }
//     
//     inline std::string& Trim(std::string& str)
// 	{
// 		std::string::size_type p = str.find_first_not_of(" \t\r\n");
// 		if (p == std::string::npos)
// 		{
// 			str = "";
// 			return str;
// 		}
// 		std::string::size_type q = str.find_last_not_of(" \t\r\n");
// 		str = str.substr(p, q-p+1);
// 		return str;
// 	}
//     
//     inline unsigned long Hash(const char * str)
// 	{
// 		const unsigned long prime1 = 4224542477ul;
// 		const unsigned long prime2 = 3264857ul;
// 		unsigned long hash = 0;
// 		for (const char * c = str; *c; c++)
// 		{
// 			hash += prime1 * hash + *c + 1 + (hash % prime2);
// 		}
// 		return hash;
// 	}
//     
//     inline unsigned int BKDRHash(const char *str)
// 	{
// 		unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
//         unsigned int hash = 0;
//         
//         while (*str)
//         {
//             hash = hash * seed + (*str++);
//         }
//         
//         return (hash & 0x7FFFFFFF);
// 	}
//     
//     inline void Split(std::vector<std::string>& vs,
//                               const std::string& line,
//                               char dmt)
// 	{
// 		std::string::size_type p=0;
// 		std::string::size_type q;
// 		vs.clear();
// 		for(;;)
// 		{
// 			q = line.find(dmt,p);
// 			std::string str = line.substr(p,q-p);
// 			Trim(str);
// 			vs.push_back(str);
// 			if(q == std::string::npos) break;
// 			p = q+1;
// 		}
// 	}
//     
//     inline void Split(std::vector<std::string>& vs,
//                       const std::string& line,
//                       const std::string& dmt)
// 	{
// 		std::string::size_type p=0;
// 		std::string::size_type q;
// 		vs.clear();
// 		for(;;)
// 		{
// 			q = line.find(dmt,p);
// 			std::string str = line.substr(p,q-p);
// 			Trim(str);
// 			vs.push_back(str);
// 			if(q == std::string::npos) break;
// 			p = q+dmt.length();
// 		}
// 	}
//     
//     inline void SplitInt(std::vector<int>& vs,
//                                 const std::string& line,
//                                 char dmt)
// 	{
// 		std::string::size_type p=0;
// 		std::string::size_type q;
// 		vs.clear();
// 		for(;;)
// 		{
// 			q = line.find(dmt,p);
// 			std::string str = line.substr(p,q-p);
// 			Trim(str);
// 			if(!str.empty()) vs.push_back(atoi(str.c_str()));
// 			if(q == std::string::npos) break;
// 			p = q+1;
// 		}
// 	}
//     
//     inline std::string Format(const std::string fmt, ...)
//     {
//         int size = 100;
//         std::string str;
//         va_list ap;
//         while (1)
//         {
//             str.resize(size);
//             va_start(ap, fmt);
//             int n = vsnprintf((char *)str.c_str(), size, fmt.c_str(), ap);
//             va_end(ap);
//             if (n > -1 && n < size)
//             {
//                 str.resize(n);
//                 return str;
//             }
//             else
//                 size *= 2;
//         }
//         return str;
//     }
//     
//     inline std::string Format(const char* fmt, ...)
//     {
//         int size = 100;
//         std::string str;
//         va_list ap;
//         while (1)
//         {
//             str.resize(size);
//             va_start(ap, fmt);
//             int n = vsnprintf((char *)str.c_str(), size, fmt, ap);
//             va_end(ap);
//             if (n > -1 && n < size)
//             {
//                 str.resize(n);
//                 return str;
//             }
//             else
//                 size *= 2;
//         }
//         return str;
//     }
//     
//     std::string MD5(const char* str);
//     
//     std::string Base64Encode(const unsigned char* data, int len);
//     
//     std::vector<unsigned char> Base64Decode(const char* data);
//     
//     std::string UrlEncode(const std::string& str);
//     std::string UrlDecode(const std::string& str);
// };

/**
* @breif 提示框（带自动消失）
*/
class Tips : public Node
{
public:
	static std::string GetCHString(std::string key)
	{
		try
		{
			
			auto *chnStrings = Dictionary::createWithContentsOfFile(XML_CH_CFG);	//显示中文配置
			if (chnStrings)
			{
				String* str = static_cast<String*>(chnStrings->objectForKey(key));
				if(str)
					return str->getCString();
			}
			return "";
		}
		catch (...)
		{
			return "";
		}
	}

	static void Show(const char* sContent,const char* key="", float fShowTime = 3.0f)
	{
		cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

		//创建消息文本标签控件
		LabelTTF *pTextLabel = NULL;
		if (strlen(key)>0)
		{
			pTextLabel = LabelTTF::create(Tips::GetCHString(key).c_str(), "", 12, Size::ZERO,
				TextHAlignment::CENTER, TextVAlignment::TOP);
		}
		else
		{
			pTextLabel = LabelTTF::create(sContent, "", 12, Size::ZERO,
				TextHAlignment::CENTER, TextVAlignment::TOP);
		}
		pTextLabel->setColor(Color3B(240, 240, 240));

		int x = pTextLabel->getPositionX();
		int y = pTextLabel->getPositionY();

		//提示框背景
		ui::Scale9Sprite *pBg = ui::Scale9Sprite::create("pic/tipbg.png", Rect(0, 0, 200, 26));
		pBg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		pTextLabel->setPosition(pBg->getContentSize().width / 2, pBg->getContentSize().height / 2);
		pBg->addChild(pTextLabel);

		Tips *pTipsNode = new Tips();
		pTipsNode->addChild(pBg);
		pTipsNode->scheduleOnce(schedule_selector(Tips::onScheduleOnce), fShowTime);

		Scene *pScene = Director::getInstance()->getRunningScene();
		pScene->addChild(pTipsNode);
	}

private:
	void onScheduleOnce(float fDelay)
	{
		this->removeFromParent();
	}
};

enum EM_ROLE
{
	ROLE_NOMAL = 0,		//普通消息
	ROLE_ZY = 1,		//慕容紫英
	ROLE_ML = 2,		//柳梦璃
	ROLE_TH = 3,		//云天河
	ROLE_LS = 4,		//韩菱纱
	ROLE_NPC1 = 5,		//蒙面人1
	ROLE_PJ = 6,		//裴剑
	ROLE_NPC2 = 7,		//蒙面人2
	ROLE_SY = 8,		//夙瑶
	ROLE_HS = 9,		//怀朔
	ROLE_XJ = 10,		//璇玑
	ROLE_XX = 11,		//玄霄
	ROLE_CHOOSE=999,	//选项
};

//选项信息
struct ST_ChooseInfo
{
	std::string bk;
	std::string key;	//显示的文字key
	int gotoEvent=0;		//选了该选项执行跳转，<=0不跳转
};

struct ST_EventInfo 
{
	ST_EventInfo()
	{
		role = ROLE_NOMAL;
		ico = "";
		shark = 0;
		bktime = 0;
		bkx = 0;
		bky = 0;
		save = 0;
		gotoEvent = 0;
	}
	EM_ROLE role;							//角色
	std::string ico;						//头像
	std::string bk;							//场景
	std::string muisc;						//音乐
	std::string wav;						//音效
	std::string mask;						
	int shark;								//屏幕晃动
	float bktime;							//bk加载过渡时间
	float mv;								//mv展示时间
	int bkx;
	int bky;
	int save;								//自动存档点
	int gotoEvent;
	std::string item;						//显示获得的物品
	std::vector<ST_ChooseInfo> vecChoose;	//选项
};

float fgRangeRand(float min, float max);
void InitEvent();	//初始化各种事件
//bool GetEventInfo(int event, ST_EventInfo& info);

bool GetEventInfoEx(int event, ST_EventInfo& info);

std::string GetCurTime();

#endif
