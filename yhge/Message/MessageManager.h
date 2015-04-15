//
//  TODO:对消息优先级的支持
//

#ifndef YHGE_MESSAGE_MESSAGEMANAGER_H_
#define YHGE_MESSAGE_MESSAGEMANAGER_H_

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
class MessageManager : public Ref {

public:

	typedef Vector<MessageHandler*> HandleList;
	typedef std::unordered_map<Ref*,HandleList> SenderMap;
	typedef std::unordered_map<Ref*,SenderMap> ReceiverMap;
	typedef std::unordered_map<unsigned int,ReceiverMap> MessageMap;

    MessageManager();

    ~MessageManager();

	static MessageManager* getInstance();
	static void destroyInstance();

    bool init();
    
    /**
     * observer 消息接收者
     * sender   消息发送者
     */
    //receiver对sender发来的type消息可以有多个响应方法，实际中情况会很少
    
    bool registerReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle ,Ref*  handleObject);

	bool registerReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle);
	
	bool registerReceiver(Ref* receiver ,unsigned int type ,Ref* sender,MessageHandler* handler);
	
	/**
	 * 检查是否已经注册某个消息。
	 */
	bool isRegisterReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle ,Ref*  handleObject);

	bool isRegisterReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle);

	/**
	 * 取消注册到接收者的处理对象的处理方法，该方法注册到发送者的某个消息。
	 */
	void removeReceiver(Ref* receiver,unsigned int type ,Ref* sender,SEL_MessageHandler handle,Ref*  handleObject);

    /**
	 * 取消接收者的处理方法，该方法注册到发送者的某个消息。
	 */
	void removeReceiver(Ref* receiver,unsigned int type ,Ref* sender,SEL_MessageHandler handle);

	/**
	 * 取消接收者注册到某个发送者的某个消息的所有处理方法。
	 */
    void removeReceiver(Ref* receiver,unsigned int type ,Ref* sender);

	/**
	 * 取消接收者注册到某个消息的所有处理方法。
	 */
    void removeReceiver(Ref* receiver,unsigned int type);

	/**
	 * 取消接收者的所有注册信息。
	 */
    void removeReceiver(Ref* receiver);
    
	/**
	 * 取消接收者处理某个消息的某个方法。
	 */
    void removeReceiver(Ref* receiver,unsigned int type ,SEL_MessageHandler handle);
    
	/**
	 * 取消接收者注册到发送者的任意消息的某个处理方法。
	 */
    void removeReceiver(Ref* receiver,Ref* sender,SEL_MessageHandler handle);
    
	/**
	 * 取消接收者注册到发送者的所有消息的所有处理方法。
	 */
    void removeReceiver(Ref* receiver,Ref* sender);

	/**
	 * 取消接收者注册到任意发送者任意消息的某个处理方法。
	 */
    void removeReceiver(Ref* receiver,SEL_MessageHandler handle);
   	
    /**
	 * 取消注册到接收者的处理对象的所有处理方法，该方法注册到发送者的某个消息。
	 */
	void removeReceiverAllHanldes(Ref* receiver,unsigned int type ,Ref* sender,Ref*  handleObject);

    /**
	 * 取消接收者处理某个消息的所有方法。
	 */
	void removeReceiverAllHanldes(Ref* receiver,unsigned int type ,Ref*  handleObject);

    /**
	 * 取消接收者注册到发送者的任意消息的所有处理方法。
	 */
    void removeReceiverAllHanldes(Ref* receiver,Ref* sender,Ref*  handleObject);

    /**
	 * 取消接收者注册到任意发送者任意消息的所有处理方法。
	 */
	void removeReceiverAllHanldes(Ref* receiver,Ref*  handleObject);

	/**
	 * 发送消息。
	 */
	void dispatchMessage(Message* message);

	/**
	 * 发送消息到某个接收者。
	 */
	void dispatchMessage(Message* message ,Ref*  receiver);


	/**
	 * 发送消息的工具方法。
	 */
    void dispatchMessage(unsigned int type ,Ref* sender ,Ref* receiver,Ref* data);
    
    /**
	 * 发送消息的工具方法。
	 */
    void dispatchMessage(unsigned int type ,Ref* sender ,Ref* receiver);
         
	enum{
		GlobalMessageType=0
	};

	inline Ref* getGlobalObject()
	{
		return _globalObject;
	}

protected:
    // /**
	// * 添加接收者的注册表。
	// */
	//void addReceiverMap(Ref* receiver,SEL_MessageHandler handle ,unsigned int type ,Ref* sender ,Ref*  handleObject);
    void dispathMessageToAllReceiverWithSender(Message* message,ReceiverMap& msgData,Ref* sender);
    void dispatchMessageMap(ReceiverMap& msgData,Message* message);

    /**
	 * 删除接收者的注册列表。
	 */
	void removeReceiverData(SenderMap& receiverMap,SEL_MessageHandler handle,Ref* handleObject);

    /**
	 * 删除接收者的注册列表。
	 */
	void removeReceiverData(SenderMap& receiverMap,SEL_MessageHandler handle);

	/**
	 * 删除接收者的注册列表。
	 */
	void removeReceiverData(SenderMap& receiverMap);

    /**
	 * 删除接收者的注册列表。
	 */
	void removeReceiverDataForTarget(SenderMap& receiverMap,Ref* handleObject);

    /**
	 * 删除接收者的处理方法列表的处理方法为参数指定的函数。
	 */
	void removeHandleList(HandleList& handleList,SEL_MessageHandler handle,Ref* handleObject);
	/**
	 * 删除接收者的处理方法列表的处理方法为参数指定的函数。
	 */
	void removeHandleList(HandleList& handleList,SEL_MessageHandler handle);

	/**
	 * 删除接收者的处理方法列表。
	 */
	void removeHandleList(HandleList& handleList);

    /**
	 * 删除接收者的处理方法列表的处理方法为参数指定的函数。
	 */
	void removeHandleListForTarget(HandleList& handleList,Ref* handleObject);

	/**
	 * 执行接收者的处理列表的所有处理方法。
	 */
	void execHandleList(HandleList& handleList ,Message* message);
    
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
//	void execRegisterWithSenderMap(CCDictionary* senderMap,Message* message,Ref*  receiver);

	/**
	 * 消息表
	 */
    MessageMap _messages;

	/**
	 * 消息的全局对像
	 */
	Ref* _globalObject;

	/**
	 * 空对像，用作key
	 */
	Ref* _nullObject;

	///**
	// * 消息的注册表
	// */
	//CCDictionary* _regiesterMap;
};

NS_CC_YHGE_END

#endif // YHGE_MESSAGE_MESSAGEMANAGER_H_