#pragma once
#include "cocos2d.h"
#include "HTools.h"
#include "Player.h"

USING_NS_CC;

#define _theGameManager GameLogicManager::instance()

enum GAME_ACTION
{
	EM_NULL,
};

class GameLogicManager
{
private:
	GameLogicManager();
	~GameLogicManager();

public:
	static GameLogicManager* instance();

	void AddPlayer(Player* role);			//��������Ϣ
	void RemovePlayer(Player* role);		//ɾ�������Ϣ
	void ResetPlayer();
public:
	map<int,Player*> m_player;	//pos-player
	map<int,Player*> m_enemy;
};