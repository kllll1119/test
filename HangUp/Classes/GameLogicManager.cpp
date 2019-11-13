#include "GameLogicManager.h"

/*坐标参考
ENEMY		PLAYER
0 1 2		2 1 0
3 4 5		5 4 3
6 7 8		8 7 6
*/

GameLogicManager::GameLogicManager()
{
	m_trun = 0;
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
}

vector<Fighter*> GameLogicManager::FindAttackSrc(Fighter::FighterType type, int pos9,int skillid)
{ 
	vector<Fighter*> findFights;

	GAME_POS_ORDER findPos = POS_TOP;
	if (pos9 / 3 == 1)
		findPos = POS_CENTER;
	else if (pos9 / 3 == 2)
		findPos = POS_BUTTOM;

	//技能查询

	//普通查询
	Fighter* findFight = NULL;
	if (type == Fighter::HERO)
	{
		if (findPos == POS_TOP)
		{
			for (int i = 2; i >= 0; --i)
			{
				if (m_enemy.find(i) != m_enemy.end())
				{
					findFights.push_back(m_enemy[i]);
					return findFights;
				}
			}
			for (int i = 5; i >= 3; --i)
			{
				if (m_enemy.find(i) != m_enemy.end())
				{
					findFights.push_back(m_enemy[i]);
					return findFights;
				}
			}
			for (int i = 8; i >= 6; --i)
			{
				if (m_enemy.find(i) != m_enemy.end())
				{
					findFights.push_back(m_enemy[i]);
					return findFights;
				}
			}
		}
		else if (findPos == POS_CENTER)
		{
			for (int i = 5; i >= 3; --i)
			{
				if (m_enemy.find(i) != m_enemy.end())
				{
					findFights.push_back(m_enemy[i]);
					return findFights;
				}
			}
			for (int i = 2; i >= 0; --i)
			{
				if (m_enemy.find(i) != m_enemy.end())
				{
					findFights.push_back(m_enemy[i]);
					return findFights;
				}
			}
			for (int i = 8; i >= 6; --i)
			{
				if (m_enemy.find(i) != m_enemy.end())
				{
					findFights.push_back(m_enemy[i]);
					return findFights;
				}
			}
		}
		else
		{
			for (int i = 8; i >= 6; --i)
			{
				if (m_enemy.find(i) != m_enemy.end())
				{
					findFights.push_back(m_enemy[i]);
					return findFights;
				}
			}
			for (int i = 2; i >= 0; --i)
			{
				if (m_enemy.find(i) != m_enemy.end())
				{
					findFights.push_back(m_enemy[i]);
					return findFights;
				}
			}
			for (int i = 5; i >= 3; --i)
			{
				if (m_enemy.find(i) != m_enemy.end())
				{
					findFights.push_back(m_enemy[i]);
					return findFights;
				}
			}
		}
	}
	else if (type == Fighter::ENEMY)
	{
		if (findPos == POS_TOP)
		{
			for (int i = 2; i >= 0; --i)
			{
				if (m_player.find(i) != m_player.end())
				{
					findFights.push_back(m_player[i]);
					return findFights;
				}
			}
			for (int i = 5; i >= 3; --i)
			{
				if (m_player.find(i) != m_player.end())
				{
					findFights.push_back(m_player[i]);
					return findFights;
				}
			}
			for (int i = 8; i >= 6; --i)
			{
				if (m_player.find(i) != m_player.end())
				{
					findFights.push_back(m_player[i]);
					return findFights;
				}
			}
		}
		else if (findPos == POS_CENTER)
		{
			for (int i = 5; i >= 3; --i)
			{
				if (m_player.find(i) != m_player.end())
				{
					findFights.push_back(m_player[i]);
					return findFights;
				}
			}
			for (int i = 2; i >= 0; --i)
			{
				if (m_player.find(i) != m_player.end())
				{
					findFights.push_back(m_player[i]);
					return findFights;
				}
			}
			for (int i = 8; i >= 6; --i)
			{
				if (m_player.find(i) != m_player.end())
				{
					findFights.push_back(m_player[i]);
					return findFights;
				}
			}
		}
		else
		{
			for (int i = 8; i >= 6; --i)
			{
				if (m_player.find(i) != m_player.end())
				{
					findFights.push_back(m_player[i]);
					return findFights;
				}
			}
			for (int i = 2; i >= 0; --i)
			{
				if (m_player.find(i) != m_player.end())
				{
					findFights.push_back(m_player[i]);
					return findFights;
				}
			}
			for (int i = 5; i >= 3; --i)
			{
				if (m_player.find(i) != m_player.end())
				{
					findFights.push_back(m_player[i]);
					return findFights;
				}
			}
		}
	}
	return findFights;
}

void GameLogicManager::GameLogic()
{
	static int count = 0;
	if (count++ % 30 != 0)	//防止执行太快了...	越0.003一次
		return;

	if (m_player.size() == 0 || m_enemy.size() == 0)
	{
		ReloadFighters();
		return;
	}

// 	if (m_player.size() == 0)
// 	{
// 		//CCLOG("failed");	//失败
// 	}
// 	else if (m_enemy.size() == 0)
// 	{
// 		//CCLOG("victory");	//胜利
// 	}

	if (gameAct == EM_PLAYER)
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
				iter->second->PreAttack(m_trun,damage, baoji);	//攻击准备

				//寻找他的攻击对象
				vector<Fighter*> vecSrc = FindAttackSrc(iter->second->m_type, iter->second->m_pos9, 0);
				for (int i = 0; i < vecSrc.size(); ++i)
				{
					iter->second->Attack();
					vecSrc[i]->OnHurt(damage, baoji);
				}
// 				map<int, Fighter*>::iterator iter2 = m_enemy.begin();
// 				for (; iter2 != m_enemy.end(); ++iter2)
// 				{
// 					iter->second->Attack();
// 					iter2->second->OnHurt(damage, baoji);
// 					break;
// 				}
				break;
			}
		}
		if(hasUnAttck==false)
			gameAct = EM_ENEMY;
	}
	else if (gameAct == EM_ENEMY)
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
				iter->second->PreAttack(m_trun, damage, baoji);	//攻击准备

				//寻找他的攻击对象
				vector<Fighter*> vecSrc = FindAttackSrc(iter->second->m_type, iter->second->m_pos9, 0);
				for (int i = 0; i < vecSrc.size(); ++i)
				{
					iter->second->Attack();
					vecSrc[i]->OnHurt(damage, baoji);
				}
//				map<int, Fighter*>::iterator iter2 = m_player.begin();
// 				for (; iter2 != m_player.end(); ++iter2)
// 				{
// 					iter->second->Attack();
// 					iter2->second->OnHurt(damage, baoji);
// 					break;
// 				}
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
			gameAct = EM_PLAYER;
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
	InitFighter(0);
}

void GameLogicManager::InitFighter(int statge)
{
	m_trun = 0;
	//加载玩家
	m_manLayer->addChild(Fighter::create(Fighter::HERO, 1, 1));
	m_manLayer->addChild(Fighter::create(Fighter::HERO, 1, 3));
	m_manLayer->addChild(Fighter::create(Fighter::HERO, 1, 5));

	//随机生成怪物
	vector<int> vecEnemyIds;
	vecEnemyIds.push_back(2);
	vecEnemyIds.push_back(3);
	vecEnemyIds.push_back(4);
	vecEnemyIds.push_back(5);
	vector<int> vecRandomIds = MakeRandomIds(5, vecEnemyIds);
	vector<int> vecRandomPos9 = MakeRandomIndex1_9(5);
	for (int i=0; i<vecRandomPos9.size(); ++i)
	{
		m_manLayer->addChild(Fighter::create(Fighter::ENEMY, vecRandomIds[i], vecRandomPos9[i]));
	}
	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 0));
// 	layer->addChild(Fighter::create(Fighter::ENEMY, 2, 4));
// 	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 2));
// 	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 3));
// 	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 4));
// 	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 5));
// 	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 6));
// 	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 7));
// 
// 	layer->addChild(Fighter::create(Fighter::ENEMY, 2, 8));

	gameAct = EM_PLAYER;
}

void GameLogicManager::AddFighter(Fighter* role)
{
	if (role->m_type == Fighter::HERO)
	{
		m_player.emplace(role->m_pos9, role);
	}
	else
	{
		m_enemy.emplace(role->m_pos9, role);
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
