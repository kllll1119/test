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

	void InitFighter();						//���ݳ�����ʼ���������

	void AddFighter(Fighter* role);			//��������Ϣ
	void RemoveFighter(Fighter* role);		//ɾ�������Ϣ
	void ResetFighter();

	void AppendHourInfo(int atack_count,ST_HourInfo info);	//�����info�ǵ��ֵģ�������hour��

	void UpdateHourLab();

	ST_HourInfo GetCurHourInfo();			//��ȡÿСʱ��ȡ��ҵ���Ŀ
public:
	map<int,Fighter*> m_player;	//pos-Fighter
	map<int,Fighter*> m_enemy;

	deque<ST_HourInfo> m_deqHourInfo;		//ս����ȡ��¼���趨3�֣�

	int m_atack_count;		//�����ж�����
	int m_trun;				//�غϼ���
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