#pragma once
#include "cocos2d.h"
#include "HTools.h"
#include "Fighter.h"

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

	void AddPlayer(Fighter* role);			//添加相关信息
	void RemovePlayer(Fighter* role);		//删除相关信息
	void ResetPlayer();
public:
	map<int,Fighter*> m_player;	//pos-Fighter
	map<int,Fighter*> m_enemy;
};