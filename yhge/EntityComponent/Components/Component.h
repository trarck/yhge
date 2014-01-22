#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_COMPONENT_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_COMPONENT_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/message.h>


NS_CC_YHGE_BEGIN

class Entity;

/**
 * 组件系统基类
 */
class Component : public CCObject
{
public:
    
    Component();
    
    Component(const std::string& name);
    
    virtual ~Component();
    
    virtual bool init(void);  
    
    /**
     * 设置
     * 在把组件添加到entity之前调用
     * 由于组件不能被重用，所以在整个生命期只调用一次。
     */
	virtual void setup(void);
    
    /**
     * 清理
     * 在组件被从entity移除前调用
     */
	virtual void cleanup(void);

    /**
     * 注册消息
     */
    virtual bool registerMessages();
    
    /**
     * 清理消息
     */
	virtual void cleanupMessages();
    
    /**
     * 组件被添加到entity
     */
    virtual void onAddedToEntity();
    
    /**
     * 组件从entity移除
     */
    virtual void onRemovedFromEntity();
    
    //====================消息操作================//
    static inline MessageManager* getMessageManager()
    {
        return MessageManager::defaultManager();
    }
//    
//    static inline bool registerReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle)
//    {
//        return MessageManager::defaultManager()->registerReceiver(receiver, type, sender, handle,receiver);
//    }
//    
//    static inline bool registerReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle ,CCObject*  handleObject)
//    {
//        return MessageManager::defaultManager()->registerReceiver(receiver, type, sender, handle,handleObject);
//    }
//    
//    /**
//	 * 取消注册到接收者的处理对象的处理方法，该方法注册到发送者的某个消息。
//	 */
//    static inline void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle,CCObject*  handleObject)
//    {
//        MessageManager::defaultManager()->removeReceiver(receiver, type, sender, handle,handleObject);
//    }
//
//	static inline void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle)
//    {
//        MessageManager::defaultManager()->removeReceiver(receiver, type, sender, handle);
//    }
//    
//    static inline void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender)
//    {
//        MessageManager::defaultManager()->removeReceiver(receiver, type, sender);
//    }
//    
//    static inline void removeReceiver(CCObject* receiver,unsigned int type)
//    {
//        MessageManager::defaultManager()->removeReceiver(receiver, type);
//    }
//    
//    static inline void removeReceiver(CCObject* receiver)
//    {
//        MessageManager::defaultManager()->removeReceiver(receiver);
//    }
//    
//    /**
//	 * 发送消息。
//	 */
//	static inline void dispatchMessage(Message* message)
//    {
//        MessageManager::defaultManager()->dispatchMessage(message);
//    }
//    
//    
//	/**
//	 * 发送消息的工具方法。
//	 */
//    static inline void dispatchMessage(unsigned int type ,CCObject* sender ,CCObject* receiver,CCObject* data)
//    {
//        MessageManager::defaultManager()->dispatchMessage(type, sender, receiver, data);
//    }
//    
//    /**
//	 * 发送消息的工具方法。
//	 */
//    static inline void dispatchMessage(unsigned int type ,CCObject* sender ,CCObject* receiver)
//    {
//        MessageManager::defaultManager()->dispatchMessage(type, sender, receiver);
//    }
    
    //弱连接
	inline void setOwner(Entity* owner)
	{
		m_owner = owner;
	}

	inline Entity* getOwner()
	{
		return m_owner;
	}

	inline void setName(const std::string& name)
	{
		m_name = name;
	}

	inline const std::string& getName()
	{
		return m_name;
	}
    
protected:
    
    //名称
    std::string m_name;
    
    //弱引用
    Entity* m_owner;
    
	
};

NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_COMPONENTS_COMPONENT_H_
