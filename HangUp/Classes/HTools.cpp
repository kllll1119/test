#include "HTools.h"

string Tips::GetCHString(string key)
{
	try
	{
		auto *chnStrings = Dictionary::createWithContentsOfFile(XML_CH_CFG);	//显示中文配置
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

bool testReadNpc()
{
	string json = Tips::GetCHString("npcs");	//读取事件配置逻辑
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
	return true;
}

int MakeRandom(int min, int max)
{
	static bool init = false;
	if (!init)
	{
		init = true;
		srand((unsigned)time(nullptr));
	}

	return min + rand()%(max-min);
}
