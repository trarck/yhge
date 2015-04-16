//
// 执行事件的函数句柄
//

#ifndef YHGE_EVENT_EVENTHANDLERD_H_
#define YHGE_EVENT_EVENTHANDLERD_H_

#include "cocos2d.h"
#include "EventHandle.h"

NS_CC_YHGE_BEGIN

class Event;

//定义处理函数类型
typedef void (Ref::*SEL_EventHandleD)(Event*,Ref* data);
#define YH_EVENT_SELECTORD(_SELECTOR) (SEL_EventHandleD)(&_SELECTOR)

class EventHandleD : public EventHandle {
public:
    
	inline EventHandleD()
		 :_handleD(NULL)
        ,_data(NULL)
	{

	}

    ~EventHandleD();

	inline SEL_EventHandleD getHandleD()
	{
		return _handleD;
	}

	inline void setHandle(SEL_EventHandleD handle)
	{
		_handleD=handle;
	}

	inline bool initWithTarget(Ref* pTarget,SEL_EventHandleD handle,Ref* data)
	{
		setTarget(pTarget);
		_handleD=handle;
        setData(data);
		return true;
	}
    
    inline void setData(Ref* data)
    {
        CC_SAFE_RETAIN(data);
        CC_SAFE_RELEASE(_data);
        _data=data;
    }

    inline Ref* getData()
    {
        return _data;
    }

	virtual void execute(Event *event);

protected:
	SEL_EventHandleD _handleD;
    Ref* _data;
};

NS_CC_YHGE_END

#endif  // YHGE_EVENT_EVENTHANDLERD_H_
