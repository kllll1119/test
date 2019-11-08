#pragma once
#include "cocos2d.h"
#include "ui/cocosGUI.h"
#include "ui/UIWidget.h"
#include "HTools.h"

USING_NS_CC;
using namespace ui;

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