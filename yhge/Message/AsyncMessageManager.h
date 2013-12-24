//
//  TODO:对消息优先级的支持
//

#ifndef YHGE_MESSAGE_ASYNCMESSAGEMANAGER_H_
#define YHGE_MESSAGE_ASYNCMESSAGEMANAGER_H_

#include "Message.h"
#include "MessageHandler.h"

NS_CC_YHGE_BEGIN

/**
 *
 * 存储结构hash(消息).hash(接收者).hash(发送者).array(处理单元)
 */
class AsyncMessageManager : public CCObject {

public:

    AsyncMessageManager();

    ~AsyncMessageManager();

    static AsyncMessageManager* sharedAsyncMessageManager();

    bool init();
 
    /**
	 * 发送消息。
	 */
    void dispatchMessage(Message* message,float delay);


protected:
  
};

NS_CC_YHGE_END

#endif // YHGE_MESSAGE_ASYNCMESSAGEMANAGER_H_