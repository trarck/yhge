//
// 执行事件的函数句柄
//

#ifndef YHGE_EVENT_CCEVENTHANDLERD_H_
#define YHGE_EVENT_CCEVENTHANDLERD_H_

#include "cocos2d.h"
#include "EventHandle.h"

NS_CC_YHGE_BEGIN

class Event;

//定义处理函数类型
typedef void (CCObject::*SEL_EventHandleD)(Event*,CCObject* data);
#define yh_event_selectorD(_SELECTOR) (SEL_EventHandleD)(&_SELECTOR)

class EventHandleD : public EventHandle {
public:
    
	inline EventHandleD()
		 :m_handleD(NULL)
        ,m_data(NULL)
	{

	}

    ~EventHandleD();

	inline SEL_EventHandleD getHandleD()
	{
		return m_handleD;
	}

	inline void setHandle(SEL_EventHandleD handle)
	{
		m_handleD=handle;
	}

	inline bool initWithTarget(CCObject* pTarget,SEL_EventHandleD handle,CCObject* data)
	{
		setTarget(pTarget);
		m_handleD=handle;
        setData(data);
		return true;
	}
    
    inline void setData(CCObject* data)
    {
        CC_SAFE_RETAIN(data);
        CC_SAFE_RELEASE(m_data);
        m_data=data;
    }

    inline CCObject* getData()
    {
        return m_data;
    }

	virtual void execute(Event *event);

protected:
	SEL_EventHandleD m_handleD;
    CCObject* m_data;
};

NS_CC_YHGE_END

#endif  // YHGE_EVENT_CCEVENTHANDLERD_H_
