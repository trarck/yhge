#ifndef YHGE_EVENT_UIEVENT_H_
#define YHGE_EVENT_UIEVENT_H_

#include "Event.h"

NS_CC_YHGE_BEGIN

class UIEvent:public Event
{
public:
    UIEvent();

    ~UIEvent();

    bool initUIEvent(const std::string& type, bool canBubble, bool cancelable,cocos2d::CCNode* view, long detail);

    inline void setView( cocos2d::CCNode* view)
    {
        CC_SAFE_RETAIN(view);
        CC_SAFE_RELEASE(m_pView);
        m_pView = view;
    }

    inline  cocos2d::CCNode* getView()
    {
        return m_pView;
    }

    inline void setDetail(long detail)
    {
        m_lDetail = detail;
    }

    inline long getDetail()
    {
        return m_lDetail;
    }

private:
    cocos2d::CCNode* m_pView;
    long m_lDetail;

};
NS_CC_YHGE_END

#endif  // YHGE_EVENT_UIEVENT_H_