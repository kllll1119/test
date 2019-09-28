#ifndef __TITLESCENE_H__
#define	__TITLESCENE_H__

#include "cocos2d.h"
#include "ui/cocosGUI.h"
#include "ui/UIWidget.h"

USING_NS_CC;

using namespace ui;

class TitleScene :	public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 

	void BtnStart(cocos2d::Ref* pSender, Widget::TouchEventType type);
	void BtnLoad(cocos2d::Ref* pSender, Widget::TouchEventType type);
	void BtnExit(cocos2d::Ref* pSender, Widget::TouchEventType type);
    
	// implement the "static create()" method manually
    CREATE_FUNC(TitleScene);
};


#endif