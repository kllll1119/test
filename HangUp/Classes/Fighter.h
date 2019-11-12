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

	void PreAttack(int turn,int& demage, bool& baoji);	//准备攻击，返回出相关的攻击属性
	void Attack();								//攻击动画
	bool OnHurt(int damage, bool baoji);	//受伤,返回击杀

	void ResetData();

	bool IsAttacked();
	void ResetAttacked();

private:
	void InitPlayer();
	Vec2 GetPostion9();
	void AttackEnd();

public:
	FlowWord fw;			//飘文字

	Sprite*					m_pLifeBarBK;
	CCSprite*				m_pLifeBar;
	CCProgressTimer*		m_pLifeProgress;

	ImageView*				m_pImageWQ;		//武器
	ImageView*				m_pImageHurt;	//受伤

	FighterType m_type;		//类型
	Vec2 m_position;		//9宫格位置

	int m_curHp;			//战斗中当前hp
	bool m_bAttacked;		//当前回合是否攻击过

	//初始属性
	int m_id;				//角色id
	int m_pos;				//角色9宫格id
	int m_sp;				//技能触发回合
	int m_hp;				//血
	int m_attck;			//攻击
	int m_defense;			//防御
	int m_dodge;			//闪避
};