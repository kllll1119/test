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

void FlowWord::showWord(const char* text, CCPoint position, Color3B color, int size) {//text为飘字的内容，pos为飘字的位置
	/*初始化*/
	label = CCLabelTTF::create(text, "Arial", size);//创建一个字体为Arial，字号为18，内容为text的CCLabelTTF，也就是标签文本
	label->setColor(color);
	label->setPosition(position);//设置其位置
	this->addChild(label);//在场景上添加这个标签文本
	/*三个动作，放大->移动->缩小*/
// 	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();//获取屏幕的尺寸、位置信息等     
// 	CCFiniteTimeAction* action1 = CCScaleTo::create(0.2f, 3.0f, 3.0f);//0.2s内在x、y上方向皆放大为原尺寸的3倍
// 	CCFiniteTimeAction* action2 = CCMoveTo::create(0.3f, ccp(visibleSize.width / 4, 3 * visibleSize.height / 4));//在0.3s内，移动到坐标为(x=屏幕宽度的25%，y=屏幕高度的75%处)
// 	CCFiniteTimeAction* action3 = CCScaleTo::create(0.2f, 0.1f, 0.1f);//之后在0.2s内在x、y上皆缩小为原尺寸的0.1倍
// 	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(FlowWord::flowEnd));//声明一个回调（处理）函数，为FlowWord类中的flowEnd()
// 	CCFiniteTimeAction* action = CCSequence::create(action1, action2, action3, callFunc, NULL);//以上的所有动作组成动作序列action
	/*对label实行action这个动作*/
//	CCFiniteTimeAction* action = CCSequence::create(action1, action2, action3, callFunc, NULL);//以上的所有动作组成动作序列action

	//CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();//获取屏幕的尺寸、位置信息等     
	//CCFiniteTimeAction* action1 = CCScaleTo::create(0.2f, 3.0f, 3.0f);//0.2s内在x、y上方向皆放大为原尺寸的3倍
	CCFiniteTimeAction* action2 = CCMoveTo::create(0.3f, ccp(position.x, position.y + 30));//在0.3s内，移动到坐标为(x=屏幕宽度的25%，y=屏幕高度的75%处)
	//CCFiniteTimeAction* action3 = CCScaleTo::create(0.2f, 0.1f, 0.1f);//之后在0.2s内在x、y上皆缩小为原尺寸的0.1倍
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(FlowWord::flowEnd));//声明一个回调（处理）函数，为FlowWord类中的flowEnd()
	CCFiniteTimeAction* action = CCSequence::create(action2,callFunc, NULL);//以上的所有动作组成动作序列action

	label->runAction(action);
}

void FlowWord::flowEnd() {//动作结束，从父节点中删除自身
	label->setVisible(false);//先隐藏显示
	label->removeFromParentAndCleanup(true);//再删除
}

ST_FighterAttr GetFighterAttr(int id)
{
	ST_FighterAttr attr;
	string json = Tips::GetCHString("npcs");	//读取事件配置逻辑
	if (json.empty())
		return attr;

	rapidjson::Document readdoc;
	bool bRet = false;
	ssize_t size = 0;
	readdoc.Parse<0>(json.c_str());
	if (readdoc.HasParseError())
	{
		return attr;
	}
	if (readdoc.IsArray())
	{
		for (int i = 0; i < readdoc.Capacity(); i++)
		{
			if (id == readdoc[i]["id"].GetInt())
			{
				//string name = readdoc[i]["name"].GetString();
				attr.m_hp = readdoc[i]["hp"].GetInt();
				attr.m_attck = readdoc[i]["at"].GetInt();
				attr.m_defense = readdoc[i]["df"].GetInt();
			}
		}
	}
	return attr;
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

std::vector<int> MakeRandomIndex1_9(int count)
{
	int arr[9] = {0,1,2,3,4,5,6,7,8};
	int size = 8;
	std::vector<int> vec;
	for (int i = 0; i < count; ++i)	//随机man个位置
	{
		int a = rand() % size;
		vec.push_back(arr[a]);
		if (arr[a] != arr[size])
		{
			arr[a] = arr[size];
			--size;
		}
	}
	return vec;
}
std::vector<int> MakeRandomIds(int count, vector<int> ids)
{
	std::vector<int> vec;
	for (int i = 0; i < count; ++i)	//随机man个位置
	{
		int a = rand() % ids.size();
		vec.push_back(ids[a]);
	}
	return vec;
}