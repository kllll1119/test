#include "Fighter.h"
#include "GameLogicManager.h"

#define PLAY_X_SITANCE 70	//x9宫格x间距
#define PLAY_Y_SITANCE 70	//x9宫格y间距
#define PLAY_Y_SITANCE_OFF 5 //中间怪物y间距


#define ATTACK_X_POS 3		//攻击x位移

#define DAMAGE_OFFSET 5		//攻击波动（偏差）

Fighter::Fighter()
{
	m_type = ENEMY;
	m_sp = 3;				//技能触发回合

	m_pLifeBarBK=NULL;
	m_pLifeBar = NULL;
	m_pLifeProgress = NULL;

	m_pImageWQ = NULL;
	m_pImageHurt = NULL;

	m_bAttacked = false;
}

Fighter::~Fighter()
{
}

Fighter* Fighter::create(FighterType type, int id,int pos9)
{
	Fighter* pFighter = new Fighter();
	if (pFighter)
	{
		pFighter->m_type = type;
		pFighter->m_id = id;
		pFighter->m_pos9 = pos9;
		pFighter->InitPlayer();
		pFighter->autorelease();
		pFighter->setAnchorPoint(Vec2(0, 0));
		_theGameManager->AddFighter(pFighter);
		return pFighter;
	}
	else
	{
		delete pFighter;
		pFighter = NULL;
		return NULL;
	}
}

void Fighter::InitPlayer()
{
	//加载皮肤
	char skinname[20] = { 0 };
	if(m_type==HERO)
		snprintf(skinname, 19, "player%d.png", m_id);
	else
		snprintf(skinname, 19, "npc%d.png", m_id);
	bool bOK = initWithFile(skinname);
	if(bOK==false)
		return;

	//加载位置
	Vec2 position = GetPostion9();
	setPosition(position);

	//加载阴影
// 	m_pImageShadow = ImageView::create("shadow.png");
// 	m_pImageShadow->setPosition(Vec2(getContentSize().width / 2, 0));
// 	this->addChild(m_pImageShadow, 0);

	//加载属性
	m_attr = GetFighterAttr(m_type,m_id);
	if (m_attr.m_hp > 0)
	{
		m_curHp = m_attr.m_hp;
	}

	//加载装备
	if (m_type == HERO)
	{
		m_pImageWQ = ImageView::create("wq1.png");
		m_pImageWQ->setAnchorPoint(Vec2(1.0f, 0));
		m_pImageWQ->setPosition(Vec2(getContentSize().width/4, getContentSize().height/2));
		m_pImageWQ->setVisible(false);
		m_pImageWQ->setScale(1.2f); //放大大小
		this->addChild(m_pImageWQ, 0);
	}

	m_pImageHurt = ImageView::create("hh1.png");
	m_pImageHurt->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2));
	m_pImageHurt->setVisible(false);
	this->addChild(m_pImageHurt, 0);

	//加载血条
	m_pLifeBarBK = CCSprite::create("life_bk.png");
	m_pLifeBarBK->setAnchorPoint(Vec2(0, 0));
	m_pLifeBarBK->setPosition(Vec2((getContentSize().width-50)/2,-5));
	m_pLifeBar = CCSprite::create("life_bar.png");
	m_pLifeProgress = CCProgressTimer::create(m_pLifeBar);
	m_pLifeProgress->setType(kCCProgressTimerTypeBar);
	m_pLifeProgress->setBarChangeRate(Vec2(1, 0));
	m_pLifeProgress->setMidpoint(Vec2(0, 0));
	m_pLifeProgress->setPosition(Vec2(25, 2));
	m_pLifeProgress->setPercentage(100);
	m_pLifeBarBK->addChild(m_pLifeProgress, 0, 0);
//	m_pLifeBarBK->setVisible(false);
	addChild(m_pLifeBarBK);

	//测试精英怪
// 	setColor(Color3B(255, 255, 255));
// 	if (m_pos9 == 4)
// 		setColor(Color3B(255, 127, 39));
//  else if (m_pos == 1)
//  	setColor(Color3B(150,120, 120));

	//播放存活动画
	Alive();

	addChild(&fw);
}

Vec2 Fighter::GetPostion9()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int xpos = 10 + m_pos9 %3* PLAY_X_SITANCE;
	int ypos = visibleSize.height-250;
	if (m_pos9/3==1)
		ypos -= PLAY_Y_SITANCE;
	else if (m_pos9 / 3 == 2)
		ypos -= 2 * PLAY_Y_SITANCE;
	if (m_type == HERO)
	{
		xpos = visibleSize.width - xpos - getContentSize().width;
		//setFlipX(true);
	}

	if (m_pos9 == 1 || m_pos9 == 4 || m_pos9 == 7)
	{
		ypos += PLAY_Y_SITANCE_OFF;
	}

	return Vec2(xpos, ypos);
}

void Fighter::Alive()
{
	CCScaleTo* btnmove = ScaleTo::create(3.f, 1.0f, 0.95f);
	CCScaleTo* btnmove2 = ScaleTo::create(3.f, 1.0f, 1.0f);

	float freetime = MakeRandom(20, 30) / 10.f;
	CCScaleTo* btnmove3 = ScaleTo::create(freetime, 1.0f, 1.0f);
	CCRepeatForever* m_btnAction = CCRepeatForever::create(static_cast<CCSequence *>(CCSequence::create(btnmove, btnmove2, btnmove3, NULL)));	//循环动作
	runAction(m_btnAction);
}

void Fighter::Die()
{
	_theGameManager->RemoveFighter(this);

	if (m_type = ENEMY)
	{
		//爆金币
		if (Random0_100() < m_attr.m_bl)
		{
			//爆装备逻辑
		}
	}

	stopAllActions();
	setColor(Color3B(255, 127, 39));
	//setColor(Color3B(78, 200, 78));

	float dieTime = 1.0f;
	FadeOut* dieAni = FadeOut::create(dieTime);
	runAction(dieAni);
	schedule([&](float dt)
	{
		removeFromParent();
	}, dieTime, 1, 0.0f, "Die");//CC_REPEAT_FOREVER
}

ST_FighterSkill Fighter::PreAttack(int turn, int& demage, bool& baoji)
{
	int attackOffset = MakeRandom(-DAMAGE_OFFSET, DAMAGE_OFFSET);	//攻击波动
	//判断攻击属性
	demage = m_attr.m_attck + attackOffset;
	baoji = false;
	if (Random0_100() < m_attr.m_bj)
	{
		baoji = true;
		//demage *= 1.5;
	}

	//判断技能飘字等
	ST_FighterSkill sk;
	for (int i=0; turn > 0 &&  i< m_attr.vecSkill.size(); ++i)
	{
		if (m_attr.vecSkill[i].turn>0 && turn % m_attr.vecSkill[i].turn == 0)
		{
			fw.showWord(m_attr.vecSkill[i].skillName.c_str(), Vec2(m_position.x + getContentSize().width / 2, m_position.y + getContentSize().height - 10), Color3B(255, 0, 0), 18);
			return m_attr.vecSkill[i];
		}
	}
	return sk;
}

void Fighter::Attack()
{
	//攻击动画
	int attackPos = -ATTACK_X_POS;
	if (m_type == ENEMY)
	{
		attackPos = ATTACK_X_POS;
	}
	Vec2 pos = Vec2(m_position.x+ attackPos,m_position.y);
	CCMoveBy* btnmove = CCMoveBy::create(0.1f, pos);
	CCRepeat* m_btnAction = CCRepeat::create(static_cast<CCSequence *>(CCSequence::create(btnmove, btnmove->reverse(), NULL)),1);
	runAction(m_btnAction);

	if (m_type == HERO && m_pImageWQ)
	{
		m_pImageWQ->setVisible(true);
		CCRotateBy* rotateBy = CCRotateBy::create(0.2f, -90.f);
		CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Fighter::AttackEnd));
		CCFiniteTimeAction* action = CCSequence::create(rotateBy, callFunc, NULL);
		m_pImageWQ->runAction(action);
	}
	m_bAttacked = true;
}

bool Fighter::OnHurt(int damage, bool baoji)
{
	if (m_curHp <= 0)
		return false;

	int realDamage = damage - m_attr.m_defense;
	if (realDamage <= 0)
		realDamage = 1;

	if (Random0_100() < m_attr.m_dodge)
	{
		realDamage = 0; //闪避
	}

	

	if (realDamage > 0)
	{
		//受伤动画
		setColor(Color3B(255, 213, 170));
		m_pImageHurt->setVisible(true);
		schedule([&](float dt)
		{
			setColor(Color3B(255, 255, 255));
			m_pImageHurt->setVisible(false);
		}, 0.1f, 1, 0, "hurt");

// 		m_pLifeBarBK->setVisible(true);
// 		unschedule("showlife");
// 		schedule([&](float dt)
// 		{
// 			m_pLifeBarBK->setVisible(false);
// 		}, 2.0f, 1, 0, "showlife");
	}

	//伤害飘字等
	Color3B color = Color3B(255, 255, 255);
	int size = 12;
	if (baoji && realDamage>0)	//受到暴击
	{
		realDamage *= 2;
		color = Color3B(255, 0, 0);
		size = 14;
	}

	char strDamage[20] = {'0',0};
	if(realDamage>0)
		snprintf(strDamage, 19, "-%d", realDamage);
	int xOff = MakeRandom(-8, 8);
	int yOff = MakeRandom(-5, 5);
	fw.showWord(strDamage, Vec2(m_position.x + xOff + getContentSize().width/2,m_position.y+getContentSize().height-25 + yOff), color, size);

	//判断死亡
	if (realDamage > 0)
	{
		m_curHp -= realDamage;
		float hp_percent = m_curHp / (float)m_attr.m_hp * 100;
		m_pLifeProgress->setPercentage(hp_percent);
		if (m_curHp <= 0)
		{
			m_pLifeProgress->setPercentage(0);
			Die();
			return true;
		}
	}
	return false;
}

void Fighter::ResetData()
{

}

void Fighter::AttackEnd()
{
	m_pImageWQ->setVisible(false);
	m_pImageWQ->setRotation(0);
}

bool Fighter::IsAttacked()
{
	return m_bAttacked;
}

void Fighter::ResetAttacked()
{
	m_bAttacked = false;
}
