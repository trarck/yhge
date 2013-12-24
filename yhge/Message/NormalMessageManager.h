//
//  TODO:对消息优先级的支持,延迟消息
//
//  没有全局消息，当发送者为空时，不是收到所有人发来的消息，而只能收到由空发送人发来的消息。
//	空可以用一个全局对象表示，和普通的对象处理一样处理.当投递普通对象的消息时,不触发全局消息。
//
//

#ifndef YHGE_MESSAGE_NORMALMESSAGEMANAGER_H_
#define YHGE_MESSAGE_NORMALMESSAGEMANAGER_H_

#include "cocos2d.h"
#include "YHGEMacros.h"
#include "MessageManager.h"

NS_CC_YHGE_BEGIN

class NormalMessageManager: public MessageManager 
{
public:
	static NormalMessageManager* sharedNormalMessageManager();
    void dispatchMessage(Message* message);
};

NS_CC_YHGE_END

#endif // YHGE_MESSAGE_NORMALMESSAGEMANAGER_H_
