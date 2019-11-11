#include "GameLogicManager.h"

Fighter* testPlayer = NULL;
Fighter* testEneme = NULL;

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

vector<Fighter*> GameLogicManager::FindAttackSrc(Fighter::FighterType type, int pos9,int skillid)
{ 
	vector<Fighter*> findFights;
	Fighter* findFight = NULL;
	if (type == Fighter::HERO)
	{

	}
	else if (type == Fighter::HERO)
	{

	}
	return findFights;
}

void GameLogicManager::GameLogic()
{
	static int count = 0;
	if (count++ % 30 != 0)	//防止执行太快了...
		return;

	if (gameAct == EM_PLAYER)
	{
		map<int, Fighter*>::iterator iter = m_player.begin();
		for (; iter != m_player.end(); ++iter)
		{
			if (iter->second->m_attackCount == m_trun)
			{
				int pos9 = iter->second->m_pos;
				bool baoji = false;
				int damage = 0;
				iter->second->Attack(damage, baoji);	//攻击准备

				//寻找他的攻击对象
				map<int, Fighter*>::iterator iter = m_enemy.begin();
				for (; iter != m_enemy.end(); ++iter)
				{
					iter->second->OnHurt(damage, baoji);
					break;
				}
			}
		}
		gameAct = EM_ENEMY;
	}
	else if (gameAct == EM_ENEMY)
	{
		map<int, Fighter*>::iterator iter = m_enemy.begin();
		for (; iter != m_enemy.end(); ++iter)
		{
			if (iter->second->m_attackCount == m_trun)
			{
				int pos9 = iter->second->m_pos;
				bool baoji = false;
				int damage = 0;
				iter->second->Attack(damage, baoji);	//攻击准备

				//寻找他的攻击对象
				map<int, Fighter*>::iterator iter = m_player.begin();
				for (; iter != m_player.end(); ++iter)
				{
					iter->second->OnHurt(damage, baoji);
					break;
				}
			}
		}
		++m_trun;
		gameAct = EM_PLAYER;
	}
// 	static int count = 0;
// 	count++;
// 	if (count%50==0)
// 	{
// 		if (testEneme->m_curHp > 0)
// 		{
// 			int att = 0;
// 			bool bj = false;
// 			testPlayer->Attack(att, bj);
// 
// 			if(count>200)
// 				testEneme->OnHurt(50, true);
// 			else
// 				testEneme->OnHurt(50, false);
// 		}
// 	}
}
void GameLogicManager::InitFighter(CCLayer* layer, int statge)
{
	testPlayer = Fighter::create(Fighter::HERO, 1, 8);
	layer->addChild(testPlayer);

	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 0));
	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 1));
	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 2));
	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 3));
	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 4));
	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 5));
	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 6));
	// 	addChild(Fighter::create(Fighter::ENEMY, 2, 7));

	testEneme = Fighter::create(Fighter::ENEMY, 2, 8);
	layer->addChild(testEneme);

	gameAct = EM_PLAYER;
}

void GameLogicManager::AddFighter(Fighter* role)
{
	if (role->m_type == Fighter::HERO)
	{
		m_player.emplace(role->m_pos, role);
	}
	else
	{
		m_enemy.emplace(role->m_pos, role);
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
