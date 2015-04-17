//
// 鎵ц浜嬩欢鐨勫嚱鏁板彞鏌?
//

#ifndef YHGE_EVENT_EVENTHANDLEWRAP_H_
#define YHGE_EVENT_EVENTHANDLEWRAP_H_

#include "cocos2d.h"
#include "EventHandle.h"

NS_CC_YHGE_BEGIN

//瀹氫箟澶勭悊鍑芥暟绫诲瀷
typedef void (Ref::*SEL_EventHandleD)(yhge::Event* evt,Ref* data);
#define YH_EVENT_HANDLED_SELECTOR(_SELECTOR) (SEL_EventHandleD)(&_SELECTOR)

class EventHandleWrap : public Ref {
public:
    
	inline EventHandleWrap()
        :_target(NULL)
		,_handle(NULL)
        ,_data(NULL)
	{

	}

    ~EventHandleWrap();

    inline void handle(yhge::Event* event){
        if(_handle){
		    (_target->*_handle)(event,_data);
	    }
    }

    inline Ref* getTarget()
	{
		return _target;
	}

	inline void setTarget(Ref* pTarget)
	{
		CC_SAFE_RETAIN(pTarget);
		CC_SAFE_RELEASE(_target);
		_target=pTarget;
	}

	inline SEL_EventHandleD getHandle()
	{
		return _handle;
	}

	inline void setHandle(SEL_EventHandleD handle)
	{
		_handle=handle;
	}

	inline bool initWithTarget(Ref* pTarget,SEL_EventHandleD handle,Ref* data)
	{
		setTarget(pTarget);
		_handle=handle;
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

protected:
	Ref* _target;
	SEL_EventHandleD _handle;
    Ref* _data;
};

NS_CC_YHGE_END

#endif  // YHGE_EVENT_EVENTHANDLEWRAP_H_
