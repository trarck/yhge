#ifndef YHGE_EVENT_UIEVENT_H_
#define YHGE_EVENT_UIEVENT_H_

#include "Event.h"

NS_CC_YHGE_BEGIN

class UIEvent:public Event
{
public:
    UIEvent();

    ~UIEvent();

    bool initUIEvent(const std::string& type, bool canBubble, bool cancelable,cocos2d::Node* view, long detail);

    inline void setView( cocos2d::Node* view)
    {
        CC_SAFE_RETAIN(view);
        CC_SAFE_RELEASE(_pView);
        _pView = view;
    }

    inline  cocos2d::Node* getView()
    {
        return _pView;
    }

    inline void setDetail(long detail)
    {
        _lDetail = detail;
    }

    inline long getDetail()
    {
        return _lDetail;
    }

private:
    cocos2d::Node* _pView;
    long _lDetail;

};
NS_CC_YHGE_END

#endif  // YHGE_EVENT_UIEVENT_H_