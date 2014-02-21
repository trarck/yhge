//
// 鎵ц浜嬩欢鐨勫嚱鏁板彞鏌?
//

#ifndef YHGE_EVENT_EVENTHANDLEWRAP_H_
#define YHGE_EVENT_EVENTHANDLEWRAP_H_

#include "cocos2d.h"
#include "EventHandle.h"

NS_CC_YHGE_BEGIN

//瀹氫箟澶勭悊鍑芥暟绫诲瀷
typedef void (CCObject::*SEL_EventHandleD)(yhge::Event* evt,CCObject* data);
#define YH_EVENT_HANDLED_SELECTOR(_SELECTOR) (SEL_EventHandleD)(&_SELECTOR)

class EventHandleWrap : public CCObject {
public:
    
	inline EventHandleWrap()
        :m_pTarget(NULL)
		,m_handle(NULL)
        ,m_data(NULL)
	{

	}

    ~EventHandleWrap();

    inline void handle(yhge::Event* event){
        if(m_handle){
		    (m_pTarget->*m_handle)(event,m_data);
	    }
    }

    inline CCObject* getTarget()
	{
		return m_pTarget;
	}

	inline void setTarget(CCObject* pTarget)
	{
		CC_SAFE_RETAIN(pTarget);
		CC_SAFE_RELEASE(m_pTarget);
		m_pTarget=pTarget;
	}

	inline SEL_EventHandleD getHandle()
	{
		return m_handle;
	}

	inline void setHandle(SEL_EventHandleD handle)
	{
		m_handle=handle;
	}

	inline bool initWithTarget(CCObject* pTarget,SEL_EventHandleD handle,CCObject* data)
	{
		setTarget(pTarget);
		m_handle=handle;
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

protected:
	CCObject* m_pTarget;
	SEL_EventHandleD m_handle;
    CCObject* m_data;
};

NS_CC_YHGE_END

#endif  // YHGE_EVENT_EVENTHANDLEWRAP_H_
