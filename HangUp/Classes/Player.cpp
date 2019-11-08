///////////////////////////////////////////////
//������by:����   QQ:414755548
//���Ǹս���˾�Ĳ���,������кõ�˼·,��ӭΪС���ṩһЩ����ͽ���,лл!!
///////////////////////////////////////////////
#include "Player.h"

#define PLAY_X_SITANCE 70	//x9������
#define PLAY_Y_SITANCE 80	//x9������

Player::Player()
{
}

Player::~Player()
{
}

Player* Player::create(PlayerType type, int id,int pos)
{
	Player* player = new Player();
	if (player)
	{
		player->m_type = type;
		player->m_id = id;
		player->m_pos = pos;
		player->InitPlayer();
		player->autorelease();
		player->setAnchorPoint(Vec2(0, 0));
		return player;
	}
	else
	{
		delete player;
		player = NULL;
		return NULL;
	}
}

void Player::InitPlayer()
{
	//����Ƥ��
	char playname[20] = { 0 };
	snprintf(playname, 19, "npc%d.png", m_id);
	initWithFile(playname);	

	//��������

	//����װ��

	//����λ��
	Vec2 position = GetPostion();
	setPosition(position);

	//����Ѫ��

	//���Ծ�Ӣ��
	if (m_pos == 4)
	{
		setColor(Color3B(255, 250, 150));
	}

	//���Ŵ���
	Alive();
}

Vec2 Player::GetPostion()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int xpos = 10 + m_pos%3* PLAY_X_SITANCE;
	int ypos = visibleSize.height/2 + 100;
	if (m_pos >= 3 && m_pos < 6)
		ypos -= PLAY_Y_SITANCE;
	else if (m_pos >= 6 && m_pos < 9)
		ypos -= 2 * PLAY_Y_SITANCE;
	if (m_type == Player::ENEMY)
	{
		xpos = visibleSize.width - xpos - getContentSize().width;
		setFlipX(true);
	}
	return Vec2(xpos, ypos);
}

void Player::Alive()
{
	CCScaleTo* btnmove = ScaleTo::create(2.f, 1.0f, 0.95f);
	CCScaleTo* btnmove2 = ScaleTo::create(2.f, 1.0f, 1.0f);

	float freetime = MakeRandom(10, 30) / 10.f;
	CCScaleTo* btnmove3 = ScaleTo::create(freetime, 1.0f, 1.0f);
	CCRepeatForever* m_btnAction = CCRepeatForever::create(static_cast<CCSequence *>(CCSequence::create(btnmove, btnmove2, btnmove3, NULL)));	//ѭ������
	runAction(m_btnAction);
}

void Player::Die()
{
	stopAllActions();
	setColor(Color3B(150, 50, 50));

	FadeOut* dieAni = FadeOut::create(1.0f);
	runAction(dieAni);
	schedule([&](float dt)
	{
		removeFromParent();
	}, 1.f, 1/*CC_REPEAT_FOREVER*/, 0.0f, "MySchedule");
}