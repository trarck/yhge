//
//
//
#ifndef YHGE_MESSAGE_MESSAGETARGET_H_
#define YHGE_MESSAGE_MESSAGETARGET_H_

#include "Message.h"
#include "MessageHandler.h"

NS_CC_YHGE_BEGIN

class MessageTarget : public Ref {
public:
    
  
    //message operate
    virtual void registerMessage(unsigned int type,SEL_MessageHandler handle , Ref* pSender);
    virtual void unregisterMessage(unsigned int type ,SEL_MessageHandler handle ,Ref* pSender);
    virtual void sendMessage(unsigned int type ,Ref* pReceiver ,Ref* data);
    virtual void sendMessage(unsigned int type ,Ref* pReceiver);
	virtual void cleanupMessages();
    
protected:

};

NS_CC_YHGE_END


#endif //YHGE_MESSAGE_MESSAGETARGET_H_
