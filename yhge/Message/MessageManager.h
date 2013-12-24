//
//  TODO:对消息优先级的支持
//

#ifndef YHGE_MESSAGE_MESSAGEMANAGER_H_
#define YHGE_MESSAGE_MESSAGEMANAGER_H_

#include "cocos2d.h"
#include "YHGEMacros.h"
#include "Message.h"
#include "MessageHandler.h"

NS_CC_YHGE_BEGIN

/**
 * 消息管理类
 * 存储结构hash(消息).hash(接收者).hash(发送者).array(处理单元)
 * 这种方式对取消注册消息友好，但对发送时，接收者为空性能会有影响。
 * 可以使用GlobalObject代替空的接收者，注册消息时，则要注册接收者为GlobalObject(其它对象为收不到接收者是GlobalObject)。
 * 这样需要对消息把控能力强，知道什么时候发全局，什么时候发给具体对象。
 */
class MessageManager : public CCObject {

public:

    MessageManager();

    ~MessageManager();

    static MessageManager* defaultManager();

    bool init();
    
    /**
     * observer 消息接收者
     * sender   消息发送者
     */
    //receiver对sender发来的type消息可以有多个响应方法，实际中情况会很少
    
    bool registerReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle ,CCObject*  handleObject);

	bool registerReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle);
	
	bool registerReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,MessageHandler* handler);
	
	/**
	 * 检查是否已经注册某个消息。
	 */
	bool isRegisterReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle ,CCObject*  handleObject);

	bool isRegisterReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle);

	/**
	 * 取消注册到接收者的处理对象的处理方法，该方法注册到发送者的某个消息。
	 */
	void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle,CCObject*  handleObject);

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
	 * 取消注册到接收者的处理对象的所有处理方法，该方法注册到发送者的某个消息。
	 */
	void removeReceiverAllHanldes(CCObject* receiver,unsigned int type ,CCObject* sender,CCObject*  handleObject);

    /**
	 * 取消接收者处理某个消息的所有方法。
	 */
	void removeReceiverAllHanldes(CCObject* receiver,unsigned int type ,CCObject*  handleObject);

    /**
	 * 取消接收者注册到发送者的任意消息的所有处理方法。
	 */
    void removeReceiverAllHanldes(CCObject* receiver,CCObject* sender,CCObject*  handleObject);

    /**
	 * 取消接收者注册到任意发送者任意消息的所有处理方法。
	 */
	void removeReceiverAllHanldes(CCObject* receiver,CCObject*  handleObject);

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
         
	enum{
		GlobalMessageType=0
	};

	inline CCObject* getGlobalObject()
	{
		return m_globalObject;
	}

protected:
    // /**
	// * 添加接收者的注册表。
	// */
	//void addReceiverMap(CCObject* receiver,SEL_MessageHandler handle ,unsigned int type ,CCObject* sender ,CCObject*  handleObject);
    void dispathMessageToAllReceiverWithSender(Message* message,CCDictionary* msgMap,CCObject* sender);
    void dispatchMessageMap(CCDictionary* msgMap,Message* message);

    /**
	 * 删除接收者的注册列表。
	 */
	void removeReceiverMap(CCDictionary* receiverMap,SEL_MessageHandler handle,CCObject* handleObject);

    /**
	 * 删除接收者的注册列表。
	 */
	void removeReceiverMap(CCDictionary* receiverMap,SEL_MessageHandler handle);

	/**
	 * 删除接收者的注册列表。
	 */
	void removeReceiverMap(CCDictionary* receiverMap);

    /**
	 * 删除接收者的注册列表。
	 */
	void removeReceiverMapForTarget(CCDictionary* receiverMap,CCObject* handleObject);

    /**
	 * 删除接收者的处理方法列表的处理方法为参数指定的函数。
	 */
	void removeHandleList(CCArray* handleList,SEL_MessageHandler handle,CCObject* handleObject);
	/**
	 * 删除接收者的处理方法列表的处理方法为参数指定的函数。
	 */
	void removeHandleList(CCArray* handleList,SEL_MessageHandler handle);

	/**
	 * 删除接收者的处理方法列表。
	 */
	void removeHandleList(CCArray* handleList);

    /**
	 * 删除接收者的处理方法列表的处理方法为参数指定的函数。
	 */
	void removeHandleListForTarget(CCArray* handleList,CCObject* handleObject);

	/**
	 * 执行接收者的处理列表的所有处理方法。
	 */
	void execHandleList(CCArray* handleList ,Message* message);
    
//	/**
//	 * 按发送者表执行消息处理函数。
//	 */
//	void execAllRegisterWithSenderMap(CCDictionary* senderMap,Message* message);
//
//	/**
//	 * 如果消息有接收者，则处理接收列表的方法
//	 * 如果没有，则按发送者表执行消息处理函数。
//	 * 
//	 */
//    void execRegisterWithSenderMap(CCDictionary* senderMap,Message* message);
//
//	/**
//	 * 如果消息有接收者，则处理接收列表的方法
//	 * 如果没有，则按发送者表执行消息处理函数。
//	 * 接收者是指定的，与消息里定义的无关
//	 */
//	void execRegisterWithSenderMap(CCDictionary* senderMap,Message* message,CCObject*  receiver);

	/**
	 * 消息表
	 */
    CCDictionary* m_messages;

	/**
	 * 消息的全局对像
	 */
	CCObject* m_globalObject;

	///**
	// * 消息的注册表
	// */
	//CCDictionary* m_regiesterMap;
};

NS_CC_YHGE_END

#endif // YHGE_MESSAGE_MESSAGEMANAGER_H_