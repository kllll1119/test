#include "GameLogicManager.h"

/*坐标参考NEW
ENEMY		PLAYER
2 1 0		0 1 2
5 4 3		3 4 5
8 7 6		6 7 8
*/

GameLogicManager::GameLogicManager()
{
	m_bk = NULL;
	m_trun = 1;
	m_curStage = 1;
	m_nextStage = 1;
	m_nextBoss = false;
	loading = false;
}

GameLogicManager::~GameLogicManager()
{
}

GameLogicManager* GameLogicManager::instance()
{
	static GameLogicManager s_gameManager;
	return &s_gameManager;
}

void GameLogicManager::SetManLayer(CCLayer* layer)
{
	m_manLayer = layer;

	m_gameAct = ACT_LOAD_DATA;
}

vector<Fighter*> GameLogicManager::FindAttackSrc(FighterType type, int pos9, ST_FighterSkill skill)
{ 
	vector<Fighter*> findFights;

	GAME_POS_ORDER findPos = POS_TOP;
	if (pos9 / 3 == 1)
		findPos = POS_CENTER;
	else if (pos9 / 3 == 2)
		findPos = POS_BUTTOM;

	map<int, Fighter*> *attackMap = &m_enemy;	//攻击对象
	if (type == ENEMY)
	{
		attackMap = &m_player;
	}

	int findAttackSrc = -1;	//攻击主目标
	{
		if (findPos == POS_TOP)
		{
			for (int i = 0; i <3; ++i)
			{
				if ((*attackMap).find(i) != (*attackMap).end())
				{
					findAttackSrc = i;
					break;
				}
			}
			for (int i = 3; findAttackSrc == -1 && i <6; ++i)
			{
				if ((*attackMap).find(i) != (*attackMap).end())
				{
					findAttackSrc = i;
					break;
				}
			}
			for (int i = 6; findAttackSrc == -1 && i < 9; ++i)
			{
				if ((*attackMap).find(i) != (*attackMap).end())
				{
					findAttackSrc = i;
					break;
				}
			}
		}
		else if (findPos == POS_CENTER)
		{
			for (int i = 3; findAttackSrc == -1 && i < 6; ++i)
			{
				if ((*attackMap).find(i) != (*attackMap).end())
				{
					findAttackSrc = i;
					break;
				}
			}
			for (int i = 0; findAttackSrc == -1 && i < 3; ++i)
			{
				if ((*attackMap).find(i) != (*attackMap).end())
				{
					findAttackSrc = i;
					break;
				}
			}
			for (int i = 6; findAttackSrc == -1 && i < 9; ++i)
			{
				if ((*attackMap).find(i) != (*attackMap).end())
				{
					findAttackSrc = i;
					break;
				}
			}
		}
		else
		{
			for (int i = 6; findAttackSrc == -1 && i <9; ++i)
			{
				if ((*attackMap).find(i) != (*attackMap).end())
				{
					findAttackSrc = i;
					break;
				}
			}
			for (int i = 0; findAttackSrc == -1 && i <3; ++i)
			{
				if ((*attackMap).find(i) != (*attackMap).end())
				{
					findAttackSrc = i;
					break;
				}
			}
			for (int i = 3; findAttackSrc == -1 && i <6; ++i)
			{
				if ((*attackMap).find(i) != (*attackMap).end())
				{
					findAttackSrc = i;
					break;
				}
			}
		}
	}

	//技能攻击
	if(skill.at>0 && findAttackSrc != -1)
	{
		if (skill.area == EM_VEC)
		{
			if (findAttackSrc / 3 == 0)
			{
				if((*attackMap).find(findAttackSrc)!= (*attackMap).end())
					findFights.push_back((*attackMap)[findAttackSrc]);
				if ((*attackMap).find(findAttackSrc + 3) != (*attackMap).end())
					findFights.push_back((*attackMap)[findAttackSrc+3]);
				if ((*attackMap).find(findAttackSrc + 6) != (*attackMap).end())
					findFights.push_back((*attackMap)[findAttackSrc+6]);
			}
			else if (findAttackSrc / 3 == 1)
			{
				if ((*attackMap).find(findAttackSrc-3) != (*attackMap).end())
					findFights.push_back((*attackMap)[findAttackSrc -3]);
				if ((*attackMap).find(findAttackSrc) != (*attackMap).end())
					findFights.push_back((*attackMap)[findAttackSrc]);
				if ((*attackMap).find(findAttackSrc+3) != (*attackMap).end())
					findFights.push_back((*attackMap)[findAttackSrc + 3]);
			}
			else
			{
				if ((*attackMap).find(findAttackSrc-6) != (*attackMap).end())
					findFights.push_back((*attackMap)[findAttackSrc -6]);
				if ((*attackMap).find(findAttackSrc-3) != (*attackMap).end())
					findFights.push_back((*attackMap)[findAttackSrc -3]);
				if ((*attackMap).find(findAttackSrc) != (*attackMap).end())
					findFights.push_back((*attackMap)[findAttackSrc]);
			}
		}
		else if (skill.area == EM_ALL)
		{
			map<int, Fighter*>::iterator iter = (*attackMap).begin();
			for (; iter!= (*attackMap).end(); ++iter)
			{
				findFights.push_back(iter->second);
			}
		}
	}
	else
	{
		findFights.push_back((*attackMap)[findAttackSrc]);
	}

	return findFights;
}

void GameLogicManager::GameLogic()
{
	static int count = 0;
 	if (count++ % 30 != 0)	//防止执行太快了...	越0.003一次
 		return;
	
	if (m_gameAct == ACT_LOAD_DATA && loading==false)
	{
		loading = true;
		//初始化

		//结算
		CCLOG("turn:%d,atack_count:%d", m_trun, m_atack_count);

		//结算完成
		ReloadFighters();
		m_gameAct = ACT_PLAYER;
		return;
	}

	loading = false;
	if (m_player.size() == 0 || m_enemy.size() == 0)	//胜利、失败
	{
		if (m_player.size() > 0)	//胜利
		{
			if (m_curStage == 1)
				m_nextStage = 2;
			else
				m_nextStage = 1;
			ST_HourInfo info;
			info.money = m_preGetMoney;
			AppendHourInfo(m_atack_count, info);
		}
		else
		{
			ST_HourInfo info;
			AppendHourInfo(m_atack_count, info);	//失败
		}
		UpdateHourLab();
// 		ST_HourInfo curInfo = GetCurHourInfo();
// 		CCLOG("h_money:%d,h_exp:%d", curInfo.money, curInfo.exp);
		m_gameAct = ACT_LOAD_DATA;
		return;
	}

	++m_atack_count;

	if (m_gameAct == ACT_PLAYER)
	{
		map<int, Fighter*>::iterator iter = m_player.begin();
		bool hasUnAttck = false;
		for (; iter != m_player.end(); ++iter)
		{
			if (iter->second->IsAttacked() == false)
			{
				hasUnAttck = true;
				int pos9 = iter->second->m_pos9;
				bool baoji = false;
				int damage = 0;
				ST_FighterSkill sk = iter->second->PreAttack(m_trun,damage, baoji);	//攻击准备

				//寻找他的攻击对象
				vector<Fighter*> vecSrc = FindAttackSrc(iter->second->m_type, iter->second->m_pos9, sk);
				for (int i = 0; i < vecSrc.size(); ++i)
				{
					iter->second->Attack();
					vecSrc[i]->OnHurt(damage, baoji);
				}
				break;
			}
		}
		if(hasUnAttck==false)
			m_gameAct = ACT_ENEMY;
	}
	else if (m_gameAct == ACT_ENEMY)
	{
		bool hasUnAttck = false;
		map<int, Fighter*>::iterator iter = m_enemy.begin();
		for (; iter != m_enemy.end(); ++iter)
		{
			if (iter->second->IsAttacked() == false)
			{
				hasUnAttck = true;
				int pos9 = iter->second->m_pos9;
				bool baoji = false;
				int damage = 0;
				ST_FighterSkill sk = iter->second->PreAttack(m_trun, damage, baoji);	//攻击准备

				//寻找他的攻击对象
				vector<Fighter*> vecSrc = FindAttackSrc(iter->second->m_type, iter->second->m_pos9, sk);
				for (int i = 0; i < vecSrc.size(); ++i)
				{
					iter->second->Attack();
					vecSrc[i]->OnHurt(damage, baoji);
				}
				break;
			}
		}
		if (hasUnAttck == false)
		{
			++m_trun;	//回合增加
			map<int, Fighter*>::iterator iter = m_enemy.begin();	//重置人员攻击状态
			for (; iter != m_enemy.end(); ++iter)
			{
				iter->second->ResetAttacked();
			}
			iter = m_player.begin();
			for (; iter != m_player.end(); ++iter)
			{
				iter->second->ResetAttacked();
			}
			m_gameAct = ACT_PLAYER;
		}
	}
}

void GameLogicManager::ReloadFighters()
{
	map<int, Fighter*>::iterator iter = m_enemy.begin();	//重置人员攻击状态
	for (; iter != m_enemy.end(); ++iter)
	{
		m_manLayer->removeChild(iter->second);
	}
	iter = m_player.begin();
	for (; iter != m_player.end(); ++iter)
	{
		m_manLayer->removeChild(iter->second);
	}
	m_enemy.clear();
	m_player.clear();
	InitFighter();
}

void GameLogicManager::InitFighter()
{
	//加载场景
	if (m_bk == NULL)
	{
		m_curStage = 1;
		m_bk = ImageView::create("bk1.png");
		m_bk->setPosition(Vec2(0, 0));
		m_bk->setAnchorPoint(Vec2(0, 0));
		m_manLayer->addChild(m_bk, ZORDER_BK);
	}
	char skinname[10] = { 0 };
	int curStage = m_curStage;
	if (m_nextStage != m_curStage)
	{
		curStage = m_nextStage;
		snprintf(skinname, 9, "bk%d.png", curStage);
		m_bk->loadTexture(skinname);
	}
	m_curStage = curStage;
	
	//加载小时获取数目
	UpdateHourLab();

	//加载日志框
	
	m_preGetMoney = 0;
	m_trun = 1;
	m_atack_count = 0;
	//加载玩家
	m_manLayer->addChild(Fighter::create(HERO, 1, 1), ZORDER_S_FIGHT);
	m_manLayer->addChild(Fighter::create(HERO, 1, 3), ZORDER_S_FIGHT);
	m_manLayer->addChild(Fighter::create(HERO, 1, 5), ZORDER_S_FIGHT);

	//生成怪物
	if (m_nextBoss == false)
	{
		std::vector<string> vecDes = GetEnemys(m_curStage);
		vector<int> vecEnemyIds;
		for (int i=0; i< vecDes.size(); ++i)
		{
			vecEnemyIds.push_back(atoi(vecDes[i].c_str()));
		}
		if (vecEnemyIds.size() == 0)
			return; //加载失败
// 		vecEnemyIds.push_back(1);
// 		vecEnemyIds.push_back(2);
// 		vecEnemyIds.push_back(3);
// 		vecEnemyIds.push_back(4);
// 		vecEnemyIds.push_back(5);
		vector<int> vecRandomIds = MakeRandomIds(5, vecEnemyIds);
		vector<int> vecRandomPos9 = MakeRandomIndex1_9(5);
		for (int i = 0; i < vecRandomPos9.size(); ++i)
		{
			m_manLayer->addChild(Fighter::create(ENEMY, vecRandomIds[i], vecRandomPos9[i]), ZORDER_S_FIGHT + vecRandomPos9[i]);
		}
	}
	else
	{
		//boss
		std::vector<string> vecDes = GetEnemysBoss(m_curStage);
		for (int i = 0; i < vecDes.size(); ++i)
		{
			int id = atoi(vecDes[i].c_str());
			if(id>0)
				m_manLayer->addChild(Fighter::create(ENEMY, id,i));
		}
	}
	m_gameAct = ACT_PLAYER;
}

void GameLogicManager::AddFighter(Fighter* role)
{
	if (role->m_type == HERO)
	{
		m_player.emplace(role->m_pos9, role);
	}
	else
	{
		m_enemy.emplace(role->m_pos9, role);

		m_preGetMoney += role->m_attr.m_money;
	}
}

void GameLogicManager::RemoveFighter(Fighter* role)
{
	map<int, Fighter*>::iterator iter = m_player.begin();
	for (; iter != m_player.end(); ++iter)
	{
		if (role == iter->second)
		{
			m_player.erase(iter);
			return;
		}
	}
	iter = m_enemy.begin();
	for (; iter != m_enemy.end(); ++iter)
	{
		if (role == iter->second)
		{
			m_enemy.erase(iter);
			return;
		}
	}
}

void GameLogicManager::ResetFighter()
{
	m_player.clear();
	m_enemy.clear();
}

void GameLogicManager::AppendHourInfo(int atack_count, ST_HourInfo info)
{
	if(m_deqHourInfo.size()==0)	//初始化添加两个空元素
	{
		m_deqHourInfo.push_front(ST_HourInfo());
		m_deqHourInfo.push_front(ST_HourInfo());
	}
	else if (m_deqHourInfo.size() >= 3)
		m_deqHourInfo.pop_back();

	//一个atack_count单位约为0.5秒
	float scale = 3600/ (0.5f * atack_count);
	info.exp *= scale;
	info.money *= scale;
	CCLOG("AppendFightInfo:money:%d,exp:%d", info.money, info.exp);
	m_deqHourInfo.push_front(info);
}

void GameLogicManager::UpdateHourLab()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (m_labHourMoney == NULL || m_labHourExp==NULL)
	{
		m_labHourMoney = CCLabelTTF::create("", "Arial", 16,Size::ZERO, cocos2d::TextHAlignment::RIGHT);
		m_labHourMoney->setColor(Color3B::RED);

		m_labHourMoney->setAnchorPoint(ccp(0,0));
		//m_labHourMoney->setHorizontalAlignment(TextHAlignment::RIGHT);
		//m_labHourMoney->setPosition(ccp(visibleSize.width-180,visibleSize.height - 100));

		m_manLayer->addChild(m_labHourMoney, ZORDER_MAIN_TIP);
		
		m_labHourExp = CCLabelTTF::create("", "Arial", 16, Size::ZERO, cocos2d::CCTextAlignment::RIGHT);
		m_labHourExp->setColor(Color3B::RED);
		//m_labHourExp->setPosition(ccp(visibleSize.width - 80, visibleSize.height - 100));
		m_labHourExp->setAnchorPoint(ccp(0, 0));
		m_manLayer->addChild(m_labHourExp, ZORDER_MAIN_TIP);
	}

	ST_HourInfo hInfo = GetCurHourInfo();
	char buf[30] = { 0 };
	snprintf(buf, 29, "%d/h Money",hInfo.money);
	m_labHourMoney->setString(buf);
	snprintf(buf, 29, "%d/h Exp", hInfo.money);
	m_labHourExp->setString(buf);
	CCLOG("h_money:%d,h_exp:%d", hInfo.money, hInfo.exp);

	m_labHourMoney->setPosition(ccp(visibleSize.width - 180, visibleSize.height - 100));
	m_labHourExp->setPosition(ccp(visibleSize.width - 80, visibleSize.height - 100));
}

ST_HourInfo GameLogicManager::GetCurHourInfo()
{
	ST_HourInfo info;
	int size = m_deqHourInfo.size();
	if (size <= 0)
		return info;
	for (size_t i=0; i< size; ++i)
	{
		info.exp += m_deqHourInfo[i].exp;
		info.money += m_deqHourInfo[i].money;
	}
	info.exp /= size;
	info.money /= size;
	return info;
}
