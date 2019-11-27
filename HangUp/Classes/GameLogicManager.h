#pragma once
#include "cocos2d.h"
#include "HTools.h"
#include "Fighter.h"
#include <deque>

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

struct ST_HourInfo
{
	int exp = 0;
	int money = 0;
//	int turn = 1;
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

	void AppendHourInfo(int atack_count,ST_HourInfo info);	//这里的info是当局的，并不是hour的

	void UpdateHourLab();

	ST_HourInfo GetCurHourInfo();			//获取每小时获取金币等数目
public:
	map<int,Fighter*> m_player;	//pos-Fighter
	map<int,Fighter*> m_enemy;

	deque<ST_HourInfo> m_deqHourInfo;		//战斗获取记录（设定3局）

	int m_atack_count;		//攻击行动计数
	int m_trun;				//回合计数
	bool loading;

	int m_preGetMoney=0;

	GAME_ACTION m_gameAct;
	CCLayer*	m_manLayer=NULL;

	ImageView* m_bk=NULL;

	CCLabelTTF* m_labHourMoney=NULL;
	CCLabelTTF* m_labHourExp=NULL;

	int m_curStage;
	int m_nextStage;
	bool m_nextBoss;
};