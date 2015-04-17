
#ifndef YHGE_EVENT_STRINGIFYEVENTLISTENERMANAGER_H_
#define YHGE_EVENT_STRINGIFYEVENTLISTENERMANAGER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "Event.h"
#include "EventHandle.h"

NS_CC_YHGE_BEGIN

class StringifyEventListenerManager:public Ref
{
public:
	typedef Vector<EventHandle*> EventHandleList;
	typedef std::unordered_map<std::string, EventHandleList> EventTypeMap;
	typedef std::unordered_map<Ref*, EventTypeMap> EventListenerMap;

    StringifyEventListenerManager();

    ~StringifyEventListenerManager();

    bool init();

    static StringifyEventListenerManager* getInstance();

	static void destroyInstance();

	/**
	 * 添加一个事件监听
	 * 由于只需要目标的id,只要是Object对像就行
	 */
    void addEventListener(Ref* target,const std::string& type,Ref* handleObject,yhge::SEL_EventHandle handle);
    
    /**
	 * 添加一个事件监听
	 * 由于只需要目标的id,只要是Object对像就行
	 */
    void addEventListener(Ref* target,const std::string& type,EventHandle* handler);
    
	/**
	 * 移除一个事件监听
	 * 由于只需要目标的id,只要是Object对像就行
	 */
    void removeEventListener(Ref* target,const std::string& type,Ref* handleObject,yhge::SEL_EventHandle handle);
    
    void removeEventListener(Ref* target,const std::string& type,Ref* handleObject);
    
    void removeEventListener(Ref* target,const std::string& type);
    
    void removeEventListener(Ref* target);

	void removeEventListenerForHandle(Ref* target,const std::string& type,yhge::SEL_EventHandle handle);
    
	/**
	 * 处理事件
	 * 由于只需要目标的id,只要是Object对像就行
	 */
    void handleEvent(Ref* target,yhge::Event* evt);

	/**
	 * 触发事件
	 * 由于事件需要传递，必需是Node
	 */
    void dispatchEvent(Node* target,yhge::Event* evt);

	/**
	 * 触发事件
	 * 把new EventObject和dispatchEvent和起来，提供简便方法
	 * 由于事件需要传递，必需是Node
	 */
    void trigger(Node* target,const std::string& type,Ref* data,bool bubbles);

	
	/**
	 * 触发事件
	 * 普通版，不需要事件传递
	 */
    void dispatchEventWithObject(Ref* target,yhge::Event* evt);

	/**
	 * 触发事件
	 * 把new EventObject和dispatchEvent和起来，提供简便方法
	 * 普通版，不需要事件传递
	 */
    void triggerWithObject(Ref* target,const std::string& type,Ref* data,bool bubbles);

    bool isListened(EventHandleList& listeners,yhge::SEL_EventHandle handle,Ref* handleObject) ;

    EventHandleList& getEventListeners(Ref* target,const std::string& type);

protected:

    void removeListeners(EventHandleList& listeners,Ref* handleObject);
    void removeListeners(EventHandleList& listeners,Ref* handleObject,yhge::SEL_EventHandle handle);
	void removeListenersForHandle(EventHandleList& listeners,yhge::SEL_EventHandle handle);

	void removeListenerMap(EventTypeMap& listenerMap,Ref* handleObject);
	void removeListenerMap(EventTypeMap& listenerMap,Ref* handleObject,yhge::SEL_EventHandle handle);
	void removeListenerMapForHandle(EventTypeMap& listenerMap,yhge::SEL_EventHandle handle);

protected:
	EventListenerMap _listeners;
};
NS_CC_YHGE_END
#endif  // YHGE_EVENT_STRINGIFYEVENTLISTENERMANAGER_H_