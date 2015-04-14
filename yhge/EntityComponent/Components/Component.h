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
class Component : public Ref
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
    
    /**
     * 组件更新。
     * 不是所有组件都需要更新，不需要更新的组件可以忽略该方法。
     */
    virtual void update(float delta);
    
    //====================消息操作================//
    static inline MessageManager* getMessageManager()
    {
        return MessageManager::defaultManager();
    }
//    
//    static inline bool registerReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle)
//    {
//        return MessageManager::defaultManager()->registerReceiver(receiver, type, sender, handle,receiver);
//    }
//    
//    static inline bool registerReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle ,Ref*  handleObject)
//    {
//        return MessageManager::defaultManager()->registerReceiver(receiver, type, sender, handle,handleObject);
//    }
//    
//    /**
//	 * 取消注册到接收者的处理对象的处理方法，该方法注册到发送者的某个消息。
//	 */
//    static inline void removeReceiver(Ref* receiver,unsigned int type ,Ref* sender,SEL_MessageHandler handle,Ref*  handleObject)
//    {
//        MessageManager::defaultManager()->removeReceiver(receiver, type, sender, handle,handleObject);
//    }
//
//	static inline void removeReceiver(Ref* receiver,unsigned int type ,Ref* sender,SEL_MessageHandler handle)
//    {
//        MessageManager::defaultManager()->removeReceiver(receiver, type, sender, handle);
//    }
//    
//    static inline void removeReceiver(Ref* receiver,unsigned int type ,Ref* sender)
//    {
//        MessageManager::defaultManager()->removeReceiver(receiver, type, sender);
//    }
//    
//    static inline void removeReceiver(Ref* receiver,unsigned int type)
//    {
//        MessageManager::defaultManager()->removeReceiver(receiver, type);
//    }
//    
//    static inline void removeReceiver(Ref* receiver)
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
//    static inline void dispatchMessage(unsigned int type ,Ref* sender ,Ref* receiver,Ref* data)
//    {
//        MessageManager::defaultManager()->dispatchMessage(type, sender, receiver, data);
//    }
//    
//    /**
//	 * 发送消息的工具方法。
//	 */
//    static inline void dispatchMessage(unsigned int type ,Ref* sender ,Ref* receiver)
//    {
//        MessageManager::defaultManager()->dispatchMessage(type, sender, receiver);
//    }
    
public:
    
	inline void setName(const std::string& name)
	{
		_name = name;
	}
    
	inline const std::string& getName()
	{
		return _name;
	}
    
    //弱连接
	inline void setOwner(Entity* owner)
	{
		_owner = owner;
	}

	inline Entity* getOwner()
	{
		return _owner;
	}
    
    inline void setType(int type)
    {
        _type = type;
    }
    
    inline int getType()
    {
        return _type;
    }
    
protected:
    
    //名称
    std::string _name;
    
    //弱引用
    Entity* _owner;
    
    //类型。用于标识组件。有的时候只使用名子无法定位具体类型，通常使用type来辅助确定。其值由具体游戏定义。
    int _type;
    
	
};

NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_COMPONENTS_COMPONENT_H_
