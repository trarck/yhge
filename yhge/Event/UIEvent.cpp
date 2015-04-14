#include "UIEvent.h"

NS_CC_YHGE_BEGIN

UIEvent::UIEvent()
:_pView(NULL)
,_lDetail(0)
{

}

UIEvent:: ~UIEvent()
{
    CC_SAFE_RELEASE(_pView);
}

bool UIEvent::initUIEvent(const std::string& type, bool canBubble, bool cancelable,cocos2d::CCNode* view, long detail)
{
    if(!Event::initEvent(type,canBubble,cancelable)){
        return false;
    }
    _pView=view;
    _lDetail=detail;
    return true;
}

NS_CC_YHGE_END