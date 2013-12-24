//
// 执行消息的函数句柄
//

#ifndef YHGE_MESSAGE_MESSAGEHANDLER_H_
#define YHGE_MESSAGE_MESSAGEHANDLER_H_

#include "cocos2d.h"
#include "YHGEMacros.h"

NS_CC_YHGE_BEGIN

class Message;

//定义处理函数类型
typedef void (CCObject::*SEL_MessageHandler)(Message*);
#define message_selector(_SELECTOR) (SEL_MessageHandler)(&_SELECTOR)

class MessageHandler : public CCObject {
public:
    
	MessageHandler()
		:m_pTarget(NULL),
		 m_handle(NULL)
	{
		//CCLOG("MessageHandler create");
	}

    ~MessageHandler();

	CCObject* getTarget()
	{
		return m_pTarget;
	}

	void setTarget(CCObject* pTarget)
	{
		CC_SAFE_RETAIN(pTarget);
		CC_SAFE_RELEASE(m_pTarget);
		m_pTarget=pTarget;
	}

	SEL_MessageHandler getHandle()
	{
		return m_handle;
	}

	void setHandle(SEL_MessageHandler handle)
	{
		m_handle=handle;
	}

	bool initWithTarget(CCObject* pTarget,SEL_MessageHandler handle)
	{
		setTarget(pTarget);
		m_handle=handle;
		return true;
	}

	void execute(Message *msg)
	{
		if(m_handle){
			(m_pTarget->*m_handle)(msg);
		}
	}

private:
	CCObject* m_pTarget;
	SEL_MessageHandler m_handle;
};


NS_CC_YHGE_END

#endif  // YHGE_MESSAGE_MESSAGEHANDLER_H_
