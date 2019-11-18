#pragma once
#include "cocos2d.h"
#include "HTools.h"
#include "Fighter.h"

USING_NS_CC;

#define _theGameManager GameLogicManager::instance()

enum GAME_ACTION
{
	ACT_LOAD_DATA,
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
	
	vector<Fighter*> FindAttackSrc(FighterType type,int pos9, ST_FighterSkill skill);

	void InitFighter();						//根据场景初始化相关人物

	void AddFighter(Fighter* role);			//添加相关信息
	void RemoveFighter(Fighter* role);		//删除相关信息
	void ResetFighter();
public:
	map<int,Fighter*> m_player;	//pos-Fighter
	map<int,Fighter*> m_enemy;

	int m_atack_count;		//攻击行动计数
	int m_trun;				//回合计数
	bool loading;

	GAME_ACTION m_gameAct;
	CCLayer*	m_manLayer;

	ImageView* m_bk;

	int m_curStage;
	int m_nextStage;
	bool m_nextBoss;
};