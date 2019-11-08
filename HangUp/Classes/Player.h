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

private:
	void InitPlayer();
	Vec2 GetPostion();

public:
	PlayerType m_type = HERO;	//����
	int m_id;					//��ɫid
	int m_pos;					//��ɫ9����λ��
};