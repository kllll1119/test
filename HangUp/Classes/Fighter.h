#pragma once
#include "cocos2d.h"
#include "HTools.h"

USING_NS_CC;

class Fighter : public Sprite
{
public:
	enum FighterType{ HERO=0, ENEMY=1};

public:
	Fighter();
	~Fighter();

	static Fighter* create(FighterType type, int id, int pos);

	void Alive();
	void Die();

	void Attack(int& demage,bool& baoji);	//攻击
	bool OnHurt(int damage, bool baoji);	//受伤,返回击杀

	void AttackEnd();

	void ResetData();
private:
	void InitPlayer();
	Vec2 GetPostion9();

public:
	FlowWord fw;			//飘文字

	Sprite*					m_pLifeBarBK;
	CCSprite*				m_pLifeBar;
	CCProgressTimer*		m_pLifeProgress;

	ImageView*				m_pImageWQ;		//武器
	ImageView*				m_pImageHurt;	//受伤

	FighterType m_type;		//类型
	Vec2 m_position;		//9宫格位置

	int m_attackCount;		//记录攻击次数
	int m_curHp;			//战斗中当前hp

	//初始属性
	int m_id;				//角色id
	int m_pos;				//角色9宫格id
	int m_sp;				//技能触发回合
	int m_hp;				//血
	int m_attck;			//攻击
	int m_defense;			//防御
	int m_dodge;			//闪避
};