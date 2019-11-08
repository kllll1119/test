#pragma once
#include "cocos2d.h"
#include "HTools.h"

USING_NS_CC;

class Player : public Sprite
{
public:
	enum PlayerType{ HERO=0, ENEMY=1};

public:
	Player();
	~Player();

	static Player* create(PlayerType type, int id, int pos);

	void Alive();
	void Die();

	void Attack(int& demage,bool& baoji);	//����
	void OnHurt(int damage, bool baoji);	//����

private:
	void InitPlayer();
	Vec2 GetPostion9();

public:
	PlayerType m_type;		//����
	Vec2 m_position;		//9����λ��

	int m_id;				//��ɫid
	int m_pos;				//��ɫ9����id

	int m_sp;				//���ܴ����غ�
	int m_hp;				//Ѫ
	int m_attck;			//����
	int m_defense;			//����
	int m_dodge;			//����
		
};