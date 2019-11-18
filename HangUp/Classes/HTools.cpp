#include "HTools.h"

string Tips::GetCHString(string key, string xml)
{
	try
	{
		auto *chnStrings = Dictionary::createWithContentsOfFile(xml.c_str());	//��ʾ��������
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

void FlowWord::showWord(const char* text, CCPoint position, Color3B color, int size) {//textΪƮ�ֵ����ݣ�posΪƮ�ֵ�λ��
	/*��ʼ��*/
	label = CCLabelTTF::create(text, "Arial", size);//����һ������ΪArial���ֺ�Ϊ18������Ϊtext��CCLabelTTF��Ҳ���Ǳ�ǩ�ı�
	label->setColor(color);
	label->setPosition(position);//������λ��
	this->addChild(label);//�ڳ�������������ǩ�ı�
	/*�����������Ŵ�->�ƶ�->��С*/
// 	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();//��ȡ��Ļ�ĳߴ硢λ����Ϣ��     
// 	CCFiniteTimeAction* action1 = CCScaleTo::create(0.2f, 3.0f, 3.0f);//0.2s����x��y�Ϸ���ԷŴ�Ϊԭ�ߴ��3��
// 	CCFiniteTimeAction* action2 = CCMoveTo::create(0.3f, ccp(visibleSize.width / 4, 3 * visibleSize.height / 4));//��0.3s�ڣ��ƶ�������Ϊ(x=��Ļ��ȵ�25%��y=��Ļ�߶ȵ�75%��)
// 	CCFiniteTimeAction* action3 = CCScaleTo::create(0.2f, 0.1f, 0.1f);//֮����0.2s����x��y�Ͻ���СΪԭ�ߴ��0.1��
// 	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(FlowWord::flowEnd));//����һ���ص�������������ΪFlowWord���е�flowEnd()
// 	CCFiniteTimeAction* action = CCSequence::create(action1, action2, action3, callFunc, NULL);//���ϵ����ж�����ɶ�������action
	/*��labelʵ��action�������*/
//	CCFiniteTimeAction* action = CCSequence::create(action1, action2, action3, callFunc, NULL);//���ϵ����ж�����ɶ�������action

	//CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();//��ȡ��Ļ�ĳߴ硢λ����Ϣ��     
	//CCFiniteTimeAction* action1 = CCScaleTo::create(0.2f, 3.0f, 3.0f);//0.2s����x��y�Ϸ���ԷŴ�Ϊԭ�ߴ��3��
	CCFiniteTimeAction* action2 = CCMoveTo::create(0.3f, ccp(position.x, position.y + 30));//��0.3s�ڣ��ƶ�������Ϊ(x=��Ļ��ȵ�25%��y=��Ļ�߶ȵ�75%��)
	//CCFiniteTimeAction* action3 = CCScaleTo::create(0.2f, 0.1f, 0.1f);//֮����0.2s����x��y�Ͻ���СΪԭ�ߴ��0.1��
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(FlowWord::flowEnd));//����һ���ص�������������ΪFlowWord���е�flowEnd()
	CCFiniteTimeAction* action = CCSequence::create(action2,callFunc, NULL);//���ϵ����ж�����ɶ�������action

	label->runAction(action);
}

void FlowWord::flowEnd() {//�����������Ӹ��ڵ���ɾ������
	label->setVisible(false);//��������ʾ
	label->removeFromParentAndCleanup(true);//��ɾ��
}

ST_FighterAttr GetFighterAttr(FighterType type,int id)
{
	ST_FighterAttr attr;
	string json;
	if(type == HERO)
		json = Tips::GetCHString("players");
	else
		json = Tips::GetCHString("npcs");	//��ȡ�¼������߼�
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
				attr.m_name = JsonGetString(readdoc[i],"name");
				attr.m_hp = JsonGetInt(readdoc[i],"hp");
				attr.m_attck = JsonGetInt(readdoc[i],"at");
				attr.m_defense = JsonGetInt(readdoc[i],"df");
				attr.m_bj = JsonGetInt2(readdoc[i], "bj",10);
				attr.m_dodge = JsonGetInt2(readdoc[i], "dod",5);
				attr.m_money = JsonGetInt2(readdoc[i], "money",1);
				attr.m_bl = JsonGetInt2(readdoc[i], "bl",1);

				if(readdoc[i].HasMember("skill") && readdoc[i]["skill"].IsArray())
					for (int j = 0; j < readdoc[i]["skill"].Capacity(); j++)
					{
						ST_FighterSkill sk;
						sk.skillName = JsonGetString(readdoc[i]["skill"][j], "name");
						sk.lv = JsonGetInt(readdoc[i]["skill"][j], "lv");
						sk.at = JsonGetInt(readdoc[i]["skill"][j], "at");
						sk.turn = JsonGetInt(readdoc[i]["skill"][j], "turn");
						string ar = JsonGetString(readdoc[i]["skill"][j], "area");
						sk.area = EM_NOMAL;
						if (ar == "hor")
							sk.area = EM_HOR;
						else if (ar == "vec")
							sk.area = EM_VEC;
						else if (ar == "all")
							sk.area = EM_ALL;
						attr.vecSkill.push_back(sk);
					}
				break;
			}
		}
	}
	return attr;
}

std::vector<string> GetEnemys(int stage)
{
	std::vector<string> vec;
	string json = Tips::GetCHString("stages", XML_STAGE);
	if (json.empty())
		return vec;

	rapidjson::Document readdoc;
	bool bRet = false;
	ssize_t size = 0;
	readdoc.Parse<0>(json.c_str());
	if (readdoc.HasParseError())
	{
		return vec;
	}
	string enemys;
	if (readdoc.IsArray())
	{
		for (int i = 0; i < readdoc.Capacity(); i++)
		{
			if (stage == readdoc[i]["id"].GetInt())
			{
				enemys = JsonGetString(readdoc[i], "enemys");
				break;
			}
		}
	}
	std::vector<std::string> des;
	TSplit(vec, enemys,",");
	return vec;
}

std::vector<std::string> GetEnemysBoss(int stage)
{
	std::vector<string> vec;
	string json = Tips::GetCHString("stages", XML_STAGE);
	if (json.empty())
		return vec;

	rapidjson::Document readdoc;
	bool bRet = false;
	ssize_t size = 0;
	readdoc.Parse<0>(json.c_str());
	if (readdoc.HasParseError())
	{
		return vec;
	}
	string enemys;
	if (readdoc.IsArray())
	{
		for (int i = 0; i < readdoc.Capacity(); i++)
		{
			if (stage == readdoc[i]["id"].GetInt())
			{
				enemys = JsonGetString(readdoc[i], "boss");
				break;
			}
		}
	}
	std::vector<std::string> des;
	TSplit(vec, enemys, ",");
	return vec;
}

void TSplit(std::vector<string>& vecRet, const string& strSrc, string strSplit)
{
	vecRet.clear();
	string strTemp = strSrc;
	string split = strSplit;
	int splitSize = split.length();
	int npos = strTemp.find(strSplit);
	int nStartPos = 0;
	if (npos == string::npos)
	{
		vecRet.push_back(strTemp);
	}
	else
	{
		vecRet.push_back(strTemp.substr(0, npos));

		nStartPos = npos + splitSize;
		strTemp = strTemp.substr(nStartPos);
		while (npos != string::npos)
		{
			npos = strTemp.find(strSplit);
			if (npos == string::npos)
			{
				vecRet.push_back(strTemp);
			}
			else
			{
				string str = strTemp.substr(0, npos);
				vecRet.push_back(str);

				nStartPos = npos + splitSize;
				strTemp = strTemp.substr(nStartPos);
			}
		}
	}
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
	for (int i = 0; i < count; ++i)	//���man��λ��
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
	for (int i = 0; i < count; ++i)	//���man��λ��
	{
		int a = rand() % ids.size();
		vec.push_back(ids[a]);
	}
	return vec;
}

int Random0_100()
{
	return MakeRandom(0, 100);
}
