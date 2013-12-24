//
//
//	每个对象只有一个处理消息的函数，和window的消息类似
//	hash(接收者)→hash(发送者)→handler
//

#ifndef YHGE_MESSAGE_SIMPLEMESSAGEMANAGER_H_
#define YHGE_MESSAGE_SIMPLEMESSAGEMANAGER_H_

#include "cocos2d.h"
#include "YHGEMacros.h"
#include "MessageManager.h"
#include "MessageHandler.h"

NS_CC_YHGE_BEGIN

class SimpleMessageManager : public MessageManager {
public:
	SimpleMessageManager();
    ~SimpleMessageManager();

    static SimpleMessageManager* sharedSimpleMessageManager();

    void init();

    /**
     * observer 消息接收者
     * sender   消息发送者
     */
    //receiver对sender发来的type消息可以有多个响应方法，实际中情况会很少
      
    bool registerReceiver(CCObject* receiver,SEL_MessageHandler handle ,unsigned int type ,CCObject* sender ,CCObject*  handleObject);

	bool registerReceiver(CCObject* receiver,SEL_MessageHandler handle,unsigned int type ,CCObject* sender);
    
	/**
	 * 取消接收者的处理方法，该方法注册到发送者的某个消息。
	 */
	void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle);

	/**
	 * 取消接收者注册到某个发送者的某个消息的所有处理方法。
	 */
    void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender);

	/**
	 * 取消接收者注册到某个消息的所有处理方法。
	 */
    void removeReceiver(CCObject* receiver,unsigned int type);

	/**
	 * 取消接收者的所以注册信息。
	 */
    void removeReceiver(CCObject* receiver);
    
	/**
	 * 取消接收者处理某个消息的某个方法。
	 */
    void removeReceiver(CCObject* receiver,unsigned int type ,SEL_MessageHandler handle);
    
	/**
	 * 取消接收者注册到发送者的任意消息的某个处理方法。
	 */
    void removeReceiver(CCObject* receiver,CCObject* sender,SEL_MessageHandler handle);
    
	/**
	 * 取消接收者注册到发送者的所有消息的所有处理方法。
	 */
    void removeReceiver(CCObject* receiver,CCObject* sender);

	/**
	 * 取消接收者注册到任意发送者任意消息的某个处理方法。
	 */
    void removeReceiver(CCObject* receiver,SEL_MessageHandler handle);

	/**
	 * 发送消息。
	 */
	void dispatchMessage(Message* message);

	/**
	 * 发送消息到某个接收者。
	 */
	void dispatchMessage(Message* message ,CCObject*  receiver);

	/**
	 * 发送消息的工具方法。
	 */
    void dispatchMessage(unsigned int type ,CCObject* sender ,CCObject* receiver,CCObject* data);
    
    /**
	 * 发送消息的工具方法。
	 */
    void dispatchMessage(unsigned int type ,CCObject* sender ,CCObject* receiver);

	/**
	 * 发送消息的工具方法。
	 * 数据是一个字典
	 */
	void dispatchMessageWithDictionary(unsigned int type ,CCObject* sender ,CCObject* receiver,CCDictionary* data);

protected:

	void execAllRegisterWithSenderMap(CCDictionary* senderMap,Message* message);

    void execRegisterWithSenderMap(CCDictionary* senderMap,Message* message);

	void execRegisterWithSenderMap(CCDictionary* senderMap,Message* message,CCObject*  receiver);
};

NS_CC_YHGE_END

#endif //YHGE_MESSAGE_SIMPLEMESSAGEMANAGER_H_
