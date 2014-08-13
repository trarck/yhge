//
//
//	每个对象只有一个处理消息的函数，和window的消息类似
//	hash(接收者)→hash(发送者)→handler
//

#ifndef YHGE_MESSAGE_SIMPLEMESSAGEMANAGER_H_
#define YHGE_MESSAGE_SIMPLEMESSAGEMANAGER_H_

#include "MessageManager.h"
#include "MessageHandler.h"

NS_CC_YHGE_BEGIN

class SwitchMessageManager : public MessageManager {
public:
	SwitchMessageManager();

	inline void setEnableExecDeleteHandle(bool enableExecDeleteHandle)
	{
	    m_enableExecDeleteHandle = enableExecDeleteHandle;
	}

	inline bool isEnableExecDeleteHandle()
	{
	    return m_enableExecDeleteHandle;
	}
	
protected:

	/**
	 * 执行接收者的处理列表的所有处理方法。
	 */
	void execHandleList(CCArray* handleList ,Message* message);
	
protected:
	
	bool m_enableExecDeleteHandle;
};

NS_CC_YHGE_END

#endif //YHGE_MESSAGE_SIMPLEMESSAGEMANAGER_H_
