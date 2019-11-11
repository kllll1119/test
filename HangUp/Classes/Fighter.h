#pragma once
#include "cocos2d.h"
#include "HTools.h"

USING_NS_CC;

class Fighter : public Sprite
{
public:
	enum PlayerType{ HERO=0, ENEMY=1};

public:
	Fighter();
	~Fighter();

	static Fighter* create(PlayerType type, int id, int pos);

	void Alive();
	void Die();

	void Attack(int& demage,bool& baoji);	//����
	bool OnHurt(int damage, bool baoji);	//����,���ػ�ɱ

	void AttackEnd();
private:
	void InitPlayer();
	Vec2 GetPostion9();

public:
	FlowWord fw;			//Ʈ����

	Sprite*					m_pLifeBarBK;
	CCSprite*				m_pLifeBar;
	CCProgressTimer*		m_pLifeProgress;

	ImageView*				m_pImageWQ;		//����
	ImageView*				m_pImageHurt;	//����

	PlayerType m_type;		//����
	Vec2 m_position;		//9����λ��

	int m_curHp;			//ս���е�ǰhp

	//��ʼ����
	int m_id;				//��ɫid
	int m_pos;				//��ɫ9����id
	int m_sp;				//���ܴ����غ�
	int m_hp;				//Ѫ
	int m_attck;			//����
	int m_defense;			//����
	int m_dodge;			//����
};