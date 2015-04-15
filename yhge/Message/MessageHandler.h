//
// 执行消息的函数句柄
//

#ifndef YHGE_MESSAGE_MESSAGEHANDLER_H_
#define YHGE_MESSAGE_MESSAGEHANDLER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class Message;

//定义处理函数类型
typedef void (Ref::*SEL_MessageHandler)(Message*);
#define MESSAGE_SELECTOR(_SELECTOR) static_cast<cocos2d::yhge::SEL_MessageHandler>(&_SELECTOR)

class MessageHandler : public Ref {
public:
    
	MessageHandler()
		:_target(NULL),
		 _handle(NULL)
	{
		//CCLOG("MessageHandler create");
	}

    ~MessageHandler();

	Ref* getTarget()
	{
		return _target;
	}

	void setTarget(Ref* pTarget)
	{
		CC_SAFE_RETAIN(pTarget);
		CC_SAFE_RELEASE(_target);
		_target=pTarget;
	}

	SEL_MessageHandler getHandle()
	{
		return _handle;
	}

	void setHandle(SEL_MessageHandler handle)
	{
		_handle=handle;
	}

	bool initWithTarget(Ref* pTarget,SEL_MessageHandler handle)
	{
		setTarget(pTarget);
		_handle=handle;
		return true;
	}

	void execute(Message *msg)
	{
		if(_handle){
			(_target->*_handle)(msg);
		}
	}

private:
	Ref* _target;
	SEL_MessageHandler _handle;
};


NS_CC_YHGE_END

#endif  // YHGE_MESSAGE_MESSAGEHANDLER_H_
