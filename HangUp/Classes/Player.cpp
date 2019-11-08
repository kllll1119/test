#include "Player.h"
#include "GameLogicManager.h"

#define PLAY_X_SITANCE 70	//x9宫格间距
#define PLAY_Y_SITANCE 80	//x9宫格间距

#define ATTACK_X_POS 10

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
		_theGameManager->AddPlayer(player);
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
	//加载皮肤
	char playname[20] = { 0 };
	snprintf(playname, 19, "npc%d.png", m_id);
	initWithFile(playname);	

	//加载属性

	//加载装备

	//加载位置
	Vec2 position = GetPostion9();
	setPosition(position);

	//加载血条

	//测试精英怪
	if (m_pos == 4)
		setColor(Color3B(255, 127, 39));
// 	else if (m_pos == 1)
// 		setColor(Color3B(39, 80, 212));
// 	else if (m_pos == 2)
// 		setColor(Color3B(78, 200, 78));
// 	else if (m_pos == 8)
// 		setColor(Color3B(255, 127, 39));

	//播放存活动画
	Alive();
}

Vec2 Player::GetPostion9()
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
	CCRepeatForever* m_btnAction = CCRepeatForever::create(static_cast<CCSequence *>(CCSequence::create(btnmove, btnmove2, btnmove3, NULL)));	//循环动作
	runAction(m_btnAction);
}

void Player::Die()
{
	_theGameManager->RemovePlayer(this);
	stopAllActions();
	//setColor(Color3B(255, 80, 39));
	setColor(Color3B(78, 200, 78));

	FadeOut* dieAni = FadeOut::create(2.0f);
	runAction(dieAni);
	schedule([&](float dt)
	{
		removeFromParent();
	}, 2.f, 1/*CC_REPEAT_FOREVER*/, 0.0f, "Die");
}

void Player::Attack(int& demage, bool& baoji)
{
	//判断技能飘字等

	//攻击动画
	int attackPos = ATTACK_X_POS;
	if (m_type == ENEMY)
	{
		attackPos = -ATTACK_X_POS;
	}
	Vec2 pos = Vec2(m_position.x+ attackPos,m_position.y);
	CCMoveBy* btnmove = CCMoveBy::create(0.2f, pos);
	CCRepeat* m_btnAction = CCRepeat::create(static_cast<CCSequence *>(CCSequence::create(btnmove, btnmove->reverse(), NULL)),1);
	runAction(m_btnAction);
}

void Player::OnHurt(int damage, bool baoji)
{
	//受伤动画

	//伤害飘字等
}
