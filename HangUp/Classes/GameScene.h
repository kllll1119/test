#pragma once
#include "cocos2d.h"
#include "HTools.h"

class GameScene : public CCLayer
{
public:
	GameScene();
	~GameScene();
	static CCScene* scene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	virtual void onEnter();
	virtual void onExit();

	virtual void update(float delta);
private:
};