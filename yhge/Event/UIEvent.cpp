#include "UIEvent.h"

NS_CC_YHGE_BEGIN

UIEvent::UIEvent()
:m_pView(NULL)
,m_lDetail(0)
{

}

UIEvent:: ~UIEvent()
{
    CC_SAFE_RELEASE(m_pView);
}

bool UIEvent::initUIEvent(const std::string& type, bool canBubble, bool cancelable,cocos2d::CCNode* view, long detail)
{
    if(!Event::initEvent(type,canBubble,cancelable)){
        return false;
    }
    m_pView=view;
    m_lDetail=detail;
    return true;
}

NS_CC_YHGE_END