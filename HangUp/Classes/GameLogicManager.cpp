#include "GameLogicManager.h"

GameLogicManager::GameLogicManager()
{
}

GameLogicManager::~GameLogicManager()
{
}

GameLogicManager* GameLogicManager::instance()
{
	static GameLogicManager s_gameManager;
	return &s_gameManager;
}

void GameLogicManager::AddPlayer(Fighter* role)
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

void GameLogicManager::RemovePlayer(Fighter* role)
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

void GameLogicManager::ResetPlayer()
{
	m_player.clear();
	m_enemy.clear();
}
