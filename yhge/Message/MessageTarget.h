//
//
//
#ifndef YHGE_MESSAGE_MESSAGETARGET_H_
#define YHGE_MESSAGE_MESSAGETARGET_H_

#include "cocos2d.h"
#include "YHGEMacros.h"
#include "Message.h"
#include "MessageHandler.h"

NS_CC_YHGE_BEGIN

class MessageTarget : public CCObject {
public:
    
  
    //message operate
    virtual void registerMessage(unsigned int type,SEL_MessageHandler handle , CCObject* pSender);
    virtual void unregisterMessage(unsigned int type ,SEL_MessageHandler handle ,CCObject* pSender);
    virtual void sendMessage(unsigned int type ,CCObject* pReceiver ,CCObject* data);
    virtual void sendMessage(unsigned int type ,CCObject* pReceiver);
	virtual void cleanupMessages();
    
protected:

};

NS_CC_YHGE_END


#endif //YHGE_MESSAGE_MESSAGETARGET_H_
