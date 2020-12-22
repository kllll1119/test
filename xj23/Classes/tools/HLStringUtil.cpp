//
//  HLStringUtil.cpp
//  HoolaiEngine
//
//  Created by zhao shuan on 13-2-26.
//

#include "HLStringUtil.h"
#include "stdlib.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "SplashScene.h"

using namespace std;
USING_NS_CC;

// Helper function. I included it here so that you can compile the whole file
// it returns a random value between min and max included
float fgRangeRand(float min, float max)
{
	float rnd = ((float)rand() / (float)RAND_MAX);
	return rnd * (max - min) + min;
}

// map<int,ST_EventInfo> g_eventInfo;	//这个来控制所有逻辑，初始化一次即可
// 
// void AddEventWithJson(int event,std::string json)
// {
// 	CCLOG("AddEventWithJson[%d]:%s\n", event, json.c_str());
// 	rapidjson::Document readdoc;
// 	bool bRet = false;
// 	ssize_t size = 0;
// 	readdoc.Parse<0>(json.c_str());
// 	if (readdoc.HasParseError())
// 	{
// 		CCLOG("GetParseError%s\n", readdoc.GetParseError());
// 	}
// 
// 	if (!readdoc.IsObject())
// 		return;
// 
// 	int role = 0;
// 	if(readdoc.HasMember("role"))
// 		role = readdoc["role"].GetInt();
// 	std::string ico = "";
// 	if (readdoc.HasMember("ico"))
// 		ico = readdoc["ico"].GetString();
// 
// 	std::string bk = "";
// 	if (readdoc.HasMember("bk"))
// 		bk = readdoc["bk"].GetString();
// 	
// 	std::string music = "";
// 	if (readdoc.HasMember("music"))
// 		music = readdoc["music"].GetString();
// 
// 	std::string wav = "";
// 	if (readdoc.HasMember("wav"))
// 		wav = readdoc["wav"].GetString();
// 
// 	std::string item = "";
// 	if (readdoc.HasMember("item"))
// 		item = readdoc["item"].GetString();
// 
// 	float shark = 0.0f;
// 	if (readdoc.HasMember("shark"))
// 		shark = (float)readdoc["shark"].GetInt();
// 
// 	float bktime = 1.0f;
// 	if (readdoc.HasMember("bktime"))
// 		bktime = readdoc["bktime"].GetDouble();
// 
// 	float mv = 0.0f;
// 	if (readdoc.HasMember("mv"))
// 		mv = readdoc["mv"].GetDouble();
// 
// 	int bkx = 0;
// 	if (readdoc.HasMember("bkx"))
// 		bkx = readdoc["bkx"].GetInt();
// 
// 	int bky = 0;
// 	if (readdoc.HasMember("bky"))
// 		bky = readdoc["bky"].GetInt();
// 
// 	int save = 0;
// 	if (readdoc.HasMember("save"))
// 		save = readdoc["save"].GetInt();
// 
// 	int gotoEvent = 0;
// 	if (readdoc.HasMember("goto"))
// 		gotoEvent = readdoc["goto"].GetInt();
// 
// 	std::vector<ST_ChooseInfo> vecChoose;
// 	if (readdoc.HasMember("choose"))
// 	{
// 		rapidjson::Value& _array = readdoc["choose"];
// 		if (_array.IsArray())
// 		{
// 			for (int i = 0; i < _array.Capacity(); i++)
// 			{
// 				ST_ChooseInfo info;
// 				rapidjson::Value& arraydoc = _array[i];
// 				if (arraydoc.HasMember("goto"))
// 				{
// 					info.gotoEvent = arraydoc["goto"].GetInt();
// 				}
// 				if (arraydoc.HasMember("bk"))
// 				{
// 					info.bk = arraydoc["bk"].GetString();
// 				}
// 				if (arraydoc.HasMember("key"))
// 				{
// 					info.key = arraydoc["key"].GetString();
// 				}
// 				vecChoose.push_back(info);
// 			}
// 		}
// 	}
// 	ST_EventInfo info;
// 	info.role = (EM_ROLE)role;
// 	info.ico = ico;
// 	info.bk = bk;
// 	info.muisc = music;
// 	info.wav = wav;
// 	info.vecChoose = vecChoose;
// 	info.item = item;
// 	info.shark = shark;
// 	info.bktime = bktime;
// 	info.bkx = bkx;
// 	info.bky = bky;
// 	info.save = save;
// 	info.mv = mv;
// 	info.gotoEvent = gotoEvent;
// 	g_eventInfo.emplace(event, info);
// }

void InitEvent()
{
// 	char buf[20] = { 0 };
// 	int event_id = 1;
// 	while (true)
// 	{
// 		snprintf(buf, 20 - 1, "event_%d", event_id);
// 		string str = Tips::GetCHString(buf);	//读取事件配置逻辑
// 		if (str.empty())
// 			break;
// 		AddEventWithJson(event_id, str);
// 		++ event_id;
// 	}

	//下面是手动写事件逻辑
// 	std::vector<ST_ChooseInfo> vecNull;
// 	AddEvent(1, vecNull, ROLE_NOMAL,"","bk1.png", "snd/scxd.mp3");
// 	std::vector<ST_ChooseInfo> vecChoose;
// 	ST_ChooseInfo st;
// 	st.gotoEvent = 0;
// 	st.key = "chs15_0";
// 	vecChoose.push_back(st);
// 	st.gotoEvent = 0;
// 	st.key = "chs15_1";
// 	vecChoose.push_back(st);
// 	AddEvent(15, vecChoose, ROLE_CHOOSE);
}

// bool GetEventInfo(int event, ST_EventInfo& info)
// {
// 	if (g_eventInfo.find(event) != g_eventInfo.end())
// 	{
// 		info = g_eventInfo[event];
// 		return true;
// 	}
// 	return false;
// }

bool GetEventInfoEx(int event, ST_EventInfo& info)
{
	if (event <= 0)
		return false;
	char buf[10] = { 0 };
	snprintf(buf,9, "et_%d", event);
	string json = Tips::GetCHString(buf);	//读取事件配置逻辑
	if (json.empty())
		return false;

	CCLOG("GetEventInfoEx[%d]:%s\n", event, json.c_str());
	rapidjson::Document readdoc;
	bool bRet = false;
	ssize_t size = 0;
	readdoc.Parse<0>(json.c_str());
	if (readdoc.HasParseError())
	{
		CCLOG("HasParseError\n");
		return false;
	}
	if (!readdoc.IsObject())
		return false;

	int role = 0;
	if (readdoc.HasMember("role"))
		role = readdoc["role"].GetInt();
	std::string ico = "";
	if (readdoc.HasMember("ico"))
		ico = readdoc["ico"].GetString();
	if (!ico.empty() && ico.find(".png") == -1)
		ico += ".png";

	std::string bk = "";
	if (readdoc.HasMember("bk"))
		bk = readdoc["bk"].GetString();
	if (!bk.empty() && bk.find(".png") == -1)
		bk += ".png";

	std::string music = "";
	if (readdoc.HasMember("music"))
		music = readdoc["music"].GetString();

	std::string wav = "";
	if (readdoc.HasMember("wav"))
		wav = readdoc["wav"].GetString();

	std::string item = "";
	if (readdoc.HasMember("item"))
		item = readdoc["item"].GetString();

	std::string mask = "";
	if (readdoc.HasMember("mask"))
		mask = readdoc["mask"].GetString();
	if (!mask.empty() && mask.find(".png") == -1)
		mask += ".png";

	if (readdoc.HasMember("tag"))
		info.tag = readdoc["tag"].GetString();
	
	float shark = 0.0f;
	if (readdoc.HasMember("shark"))
		shark = (float)readdoc["shark"].GetInt();

	float bktime = 1.0f;
	if (readdoc.HasMember("bktime"))
		bktime = readdoc["bktime"].GetDouble();

	float mv = 0.0f;
	if (readdoc.HasMember("mv"))
		mv = readdoc["mv"].GetDouble();

	int bkx = 0;
	if (readdoc.HasMember("bkx"))
		bkx = readdoc["bkx"].GetInt();

	int bky = 0;
	if (readdoc.HasMember("bky"))
		bky = readdoc["bky"].GetInt();

	int save = 0;
	if (readdoc.HasMember("save"))
		save = readdoc["save"].GetInt();

	int gotoEvent = 0;
	if (readdoc.HasMember("goto"))
		gotoEvent = readdoc["goto"].GetInt();

	std::vector<ST_ChooseInfo> vecChoose;
	if (readdoc.HasMember("choose"))
	{
		rapidjson::Value& _array = readdoc["choose"];
		if (_array.IsArray())
		{
			for (int i = 0; i < _array.Capacity(); i++)
			{
				ST_ChooseInfo info;
				rapidjson::Value& arraydoc = _array[i];
				if (arraydoc.HasMember("goto"))
				{
					info.gotoEvent = arraydoc["goto"].GetInt();
				}
				if (arraydoc.HasMember("bk"))
				{
					info.bk = arraydoc["bk"].GetString();
					if (!info.bk.empty() && info.bk.find(".png") == -1)
						info.bk += ".png";
				}
				if (arraydoc.HasMember("key"))
				{
					info.key = arraydoc["key"].GetString();
				}
				vecChoose.push_back(info);
			}
		}
	}
	info.role = (EM_ROLE)role;
	info.ico = ico;
	info.bk = bk;
	info.muisc = music;
	info.wav = wav;
	info.mask = mask;
	info.vecChoose = vecChoose;
	info.item = item;
	info.shark = shark;
	info.bktime = bktime;
	info.bkx = bkx;
	info.bky = bky;
	info.save = save;
	info.mv = mv;
	info.gotoEvent = gotoEvent;
	return true;
}

std::string GetCurTime()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	struct timeval now;
	struct tm* time;

	gettimeofday(&now, NULL);

	time = localtime(&now.tv_sec);

	char date[32] = { 0 };
	//格式化 使用需要的日期格式
	snprintf(date,31, "%d/%02d/%02d  %02d:%02d:%02d",
		(int)time->tm_year + 1900,
		(int)time->tm_mon + 1,
		(int)time->tm_mday,
		(int)time->tm_hour,
		(int)time->tm_min,
		(int)time->tm_sec);
	return date;
#elif ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	struct tm* tm;
	time_t timep;
	time(&timep);
	tm = localtime(&timep);
	char date[32] = { 0 };
	snprintf(date,31, "%d/%02d/%02d  %02d:%02d:%02d", (int)tm->tm_year + 1900, (int)tm->tm_mon + 1, (int)tm->tm_mday,
		tm->tm_hour,tm->tm_min,tm->tm_sec);
	return date;
#endif
	return "";
}

void Save(int index)
{
	char event[20] = { 0 };
	char bk[20] = { 0 };
	char music[20] = { 0 };
	char chs[20] = { 0 };
	char tm[20] = { 0 };
	char tag[20] = { 0 };
	snprintf(event, 20 - 1, "event%d", index);
	snprintf(bk, 20 - 1, "bk%d", index);
	snprintf(music, 20 - 1, "music%d", index);
	snprintf(chs, 20 - 1, "chs%d", index);
	snprintf(tm, 20 - 1, "tm%d", index);
	snprintf(tag, 20 - 1, "tag%d", index);
	SplashScene* spIns = SplashScene::instance();
	if (spIns)
	{
		UserDefault->setIntegerForKey(event, spIns->m_curEvent);
		UserDefault->setStringForKey(bk, spIns->m_backgroud);
		UserDefault->setStringForKey(music, spIns->m_music);
		UserDefault->setIntegerForKey(chs, spIns->m_lastChoose);
		UserDefault->setStringForKey(tm, GetCurTime());
		if(!spIns->m_tag.empty())
			UserDefault->setStringForKey(tag, spIns->m_tag);
	}
}