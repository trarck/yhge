//
//  对消息优先级的支持
//

#ifndef YHGE_MESSAGE_MESSAGEMANAGERINTERFACE_H_
#define YHGE_MESSAGE_MESSAGEMANAGERINTERFACE_H_

#include "Message.h"
#include "MessageHandler.h"

NS_CC_YHGE_BEGIN

class MessageManagerInterface : public CCObject {
public:
    
    /**
     * observer 消息接收者
     * sender   消息发送者
     */
    //receiver对sender发来的type消息可以有多个响应方法，实际中情况会很少
    
     /**
     * observer 消息接收者
     * sender   消息发送者
     */
    //receiver对sender发来的type消息可以有多个响应方法，实际中情况会很少
    
    virtual bool registerReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle ,CCObject*  handleObject);

	virtual bool registerReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle);
	
	virtual bool registerReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,MessageHandler* handler);
	
	/**
	 * 检查是否已经注册某个消息。
	 */
	virtual bool isRegisterReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle ,CCObject*  handleObject);

	virtual bool isRegisterReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle);

	/**
	 * 取消注册到接收者的处理对象的处理方法，该方法注册到发送者的某个消息。
	 */
	virtual void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle,CCObject*  handleObject);

    /**
	 * 取消接收者的处理方法，该方法注册到发送者的某个消息。
	 */
	virtual void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle);

	/**
	 * 取消接收者注册到某个发送者的某个消息的所有处理方法。
	 */
    virtual void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender);

	/**
	 * 取消接收者注册到某个消息的所有处理方法。
	 */
    virtual void removeReceiver(CCObject* receiver,unsigned int type);

	/**
	 * 取消接收者的所以注册信息。
	 */
    virtual void removeReceiver(CCObject* receiver);
    
	/**
	 * 取消接收者处理某个消息的某个方法。
	 */
    virtual void removeReceiver(CCObject* receiver,unsigned int type ,SEL_MessageHandler handle);
    
	/**
	 * 取消接收者注册到发送者的任意消息的某个处理方法。
	 */
    virtual void removeReceiver(CCObject* receiver,CCObject* sender,SEL_MessageHandler handle);
    
	/**
	 * 取消接收者注册到发送者的所有消息的所有处理方法。
	 */
    virtual void removeReceiver(CCObject* receiver,CCObject* sender);

	/**
	 * 取消接收者注册到任意发送者任意消息的某个处理方法。
	 */
    virtual void removeReceiver(CCObject* receiver,SEL_MessageHandler handle);
   	
    /**
	 * 取消注册到接收者的处理对象的所有处理方法，该方法注册到发送者的某个消息。
	 */
	virtual void removeReceiverAllHanldes(CCObject* receiver,unsigned int type ,CCObject* sender,CCObject*  handleObject);

    /**
	 * 取消接收者处理某个消息的所有方法。
	 */
	virtual void removeReceiverAllHanldes(CCObject* receiver,unsigned int type ,CCObject*  handleObject);

    /**
	 * 取消接收者注册到发送者的任意消息的所有处理方法。
	 */
    virtual void removeReceiverAllHanldes(CCObject* receiver,CCObject* sender,CCObject*  handleObject);

    /**
	 * 取消接收者注册到任意发送者任意消息的所有处理方法。
	 */
	virtual void removeReceiverAllHanldes(CCObject* receiver,CCObject*  handleObject);

	/**
	 * 发送消息。
	 */
	virtual void dispatchMessage(Message* message);

	/**
	 * 发送消息到某个接收者。
	 */
	virtual void dispatchMessage(Message* message ,CCObject*  receiver);


	/**
	 * 发送消息的工具方法。
	 */
    virtual void dispatchMessage(unsigned int type ,CCObject* sender ,CCObject* receiver,CCObject* data);
    
    /**
	 * 发送消息的工具方法。
	 */
    virtual void dispatchMessage(unsigned int type ,CCObject* sender ,CCObject* receiver);

	/**
	 * 发送消息的工具方法。
	 * 数据是一个字典
	 */
	virtual void dispatchMessageWithDictionary(unsigned int type ,CCObject* sender ,CCObject* receiver,CCDictionary* data);
     
};

NS_CC_YHGE_END

#endif // YHGE_MESSAGE_MESSAGEMANAGERINTERFACE_H_