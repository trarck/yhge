//
// 执行事件的函数句柄
//

#ifndef YHGE_EVENT_EVENTHANDLE_H_
#define YHGE_EVENT_EVENTHANDLE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "Event.h"

NS_CC_YHGE_BEGIN

//定义处理函数类型
typedef void (Ref::*SEL_EventHandle)(yhge::Event*);
#define YH_EVENT_SELECTOR(_SELECTOR) (yhge::SEL_EventHandle)(&_SELECTOR)

class EventHandle : public Ref {
public:
    
	inline EventHandle()
		:_pTarget(NULL),
		 _handle(NULL)
	{
		CCLOG("EventHandle create");
	}

    virtual ~EventHandle();

	inline Ref* getTarget()
	{
		return _pTarget;
	}

	inline void setTarget(Ref* pTarget)
	{
		CC_SAFE_RETAIN(pTarget);
		CC_SAFE_RELEASE(_pTarget);
		_pTarget=pTarget;
	}

	inline SEL_EventHandle getHandle()
	{
		return _handle;
	}

	inline void setHandle(SEL_EventHandle handle)
	{
		_handle=handle;
	}

	inline bool initWithTarget(Ref* pTarget,SEL_EventHandle handle)
	{
		setTarget(pTarget);
		_handle=handle;
		return true;
	}

	//不使用虚函数，来继承handle。
	//可以使用外包一层
	//virtual void execute(Event *event);
	inline void execute(yhge::Event *event)
	{
		if(_handle){
			(_pTarget->*_handle)(event);
		}
	}

protected:
	Ref* _pTarget;
	SEL_EventHandle _handle;
};

//class EventHandleD : public EventHandle {
//public:
//    
//	EventHandleD()
//		:_pTarget(NULL),
//		 _handle(NULL)
//	{
//		CCLOG("EventHandle create");
//	}
//
//    ~EventHandleD();
//
//    inline void execute(Event *event)
//	{
//		if(_handle){
//			(_pTarget->*_handle)(event);
//		}
//	}
//    
//private:
//
//    Ref* _pData;
//
//};

NS_CC_YHGE_END

#endif  // YHGE_EVENT_EVENTHANDLE_H_
