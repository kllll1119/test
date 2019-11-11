#pragma once
#include "cocos2d.h"
#include "HTools.h"
#include "Fighter.h"

USING_NS_CC;

#define _theGameManager GameLogicManager::instance()

enum GAME_ACTION
{
	EM_NULL,
	EM_PLAYER,
	EM_ENEMY,
};

class GameLogicManager
{
private:
	GameLogicManager();
	~GameLogicManager();

public:
	static GameLogicManager* instance();

	void GameLogic();

	vector<Fighter*> FindAttackSrc(Fighter::FighterType type,int pos9,int skillid);

	void InitFighter(CCLayer* layer,int statge);			//���ݳ�����ʼ���������

	void AddFighter(Fighter* role);			//��������Ϣ
	void RemoveFighter(Fighter* role);		//ɾ�������Ϣ
	void ResetFighter();
public:
	map<int,Fighter*> m_player;	//pos-Fighter
	map<int,Fighter*> m_enemy;

	int m_trun = 0;
	GAME_ACTION gameAct;
};