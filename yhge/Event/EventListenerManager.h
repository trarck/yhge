
#ifndef YHGE_EVENT_EVENTLISTENERMANAGER_H_
#define YHGE_EVENT_EVENTLISTENERMANAGER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "Event.h"
#include "EventHandle.h"

NS_CC_YHGE_BEGIN

class EventListenerManager:public Ref
{
public:
    EventListenerManager();

    ~EventListenerManager();

    bool init();

    static EventListenerManager* sharedEventListenerManager();

	/**
	 * 添加一个事件监听
	 * 由于只需要目标的id,只要是Object对像就行
	 */
    void addEventListener(Ref* target,int type,Ref* handleObject,yhge::SEL_EventHandle handle);
    
    /**
	 * 添加一个事件监听
	 * 由于只需要目标的id,只要是Object对像就行
	 */
    void addEventListener(Ref* target,int type,EventHandle* handler);

	/**
	 * 移除一个事件监听
	 * 由于只需要目标的id,只要是Object对像就行
	 */
    void removeEventListener(Ref* target,int type,Ref* handleObject,yhge::SEL_EventHandle handle);
    
    void removeEventListener(Ref* target,int type,Ref* handleObject);
    
    void removeEventListener(Ref* target,int type);
    
    void removeEventListener(Ref* target);

	void removeEventListenerForHandle(Ref* target,int type,yhge::SEL_EventHandle handle);
    
	/**
	 * 处理事件
	 * 由于只需要目标的id,只要是Object对像就行
	 */
    void handleEvent(Ref* target,yhge::Event* evt);

	/**
	 * 触发事件
	 * 由于事件需要传递，必需是CCNode
	 */
    void dispatchEvent(CCNode* target,yhge::Event* evt);

	/**
	 * 触发事件
	 * 把new EventObject和dispatchEvent和起来，提供简便方法
	 * 由于事件需要传递，必需是CCNode
	 */
    void trigger(CCNode* target,int type,Ref* data,bool bubbles);

	
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
    void triggerWithObject(Ref* target,int type,Ref* data,bool bubbles);

    bool isListened(CCArray* listeners,yhge::SEL_EventHandle handle,Ref* handleObject) ;

    CCArray* getEventListeners(Ref* target,int type);
    

  
protected:

    void removeListeners(CCArray* listeners,Ref* handleObject);
    void removeListeners(CCArray* listeners,Ref* handleObject,yhge::SEL_EventHandle handle);
	void removeListenersForHandle(CCArray* listeners,yhge::SEL_EventHandle handle);

	void removeListenerMap(CCDictionary* listenerMap,Ref* handleObject);
	void removeListenerMap(CCDictionary* listenerMap,Ref* handleObject,yhge::SEL_EventHandle handle);
	void removeListenerMapForHandle(CCDictionary* listenerMap,yhge::SEL_EventHandle handle);

protected:
	CCDictionary* m_pListeners;
};
NS_CC_YHGE_END
#endif  // YHGE_EVENT_EVENTLISTENERMANAGER_H_