//
//  LabelRPG.h
//  Cocos2dRogueLike
//
//  Created by kyokomi on 2014/04/20.
//
//

#ifndef __Cocos2dRogueLike__LabelRPG__
#define __Cocos2dRogueLike__LabelRPG__

#include "cocos2d.h"
#include <iostream>

class LabelRPG : public cocos2d::Label
{
public:
    LabelRPG(cocos2d::FontAtlas *atlas = nullptr, cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
          cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP,bool useDistanceField = false,bool useA8Shader = false);
    virtual ~LabelRPG();
    
    static LabelRPG* createWithTTF(const cocos2d::TTFConfig& ttfConfig, const std::string& text, cocos2d::TextHAlignment alignment = cocos2d::TextHAlignment::LEFT, int maxLineWidth = 680);
    
    void setStringWithRunText(int event,const std::string &text, float interval);
    
    void setOriginalPosition(cocos2d::Point originalPoint) {
        originalPoint_ = originalPoint;
        this->setPosition(originalPoint_);
    };

	void SetOverCallBack(std::function<void(int)> func)
	{
		m_tlakOverCB = func;
	}
    
private:
    int nowLabelLenght_;
    std::string nowLabelText_;
    cocos2d::Point originalPoint_;

	std::function<void(int)> m_tlakOverCB=NULL;
	int m_event=0;
};

#endif /* defined(__Cocos2dRogueLike__LabelRPG__) */
