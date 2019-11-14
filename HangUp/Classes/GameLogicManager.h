#pragma once
#include "cocos2d.h"
#include "HTools.h"
#include "Fighter.h"

USING_NS_CC;

#define _theGameManager GameLogicManager::instance()

enum GAME_ACTION
{
	ACT_NULL,
	ACT_PLAYER,
	ACT_ENEMY,
};
enum GAME_POS_ORDER
{
	POS_TOP,
	POS_CENTER,
	POS_BUTTOM
};

class GameLogicManager
{
private:
	GameLogicManager();
	~GameLogicManager();

public:
	static GameLogicManager* instance();

	void SetManLayer(CCLayer* layer);

	void GameLogic();

	void ReloadFighters();
	
	vector<Fighter*> FindAttackSrc(FighterType type,int pos9,int skillid);

	void InitFighter();						//根据场景初始化相关人物

	void AddFighter(Fighter* role);			//添加相关信息
	void RemoveFighter(Fighter* role);		//删除相关信息
	void ResetFighter();
public:
	map<int,Fighter*> m_player;	//pos-Fighter
	map<int,Fighter*> m_enemy;

	int m_trun = 0;
	GAME_ACTION gameAct;
	CCLayer*	m_manLayer;

	ImageView* m_bk;

	int m_curStage;
	int m_nextStage;
	bool m_nextBoss;
};