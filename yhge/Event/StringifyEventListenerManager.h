
#ifndef YHGE_EVENT_STRINGIFYEVENTLISTENERMANAGER_H_
#define YHGE_EVENT_STRINGIFYEVENTLISTENERMANAGER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "Event.h"
#include "EventHandle.h"

NS_CC_YHGE_BEGIN

class StringifyEventListenerManager:public CCObject
{
public:
    StringifyEventListenerManager();

    ~StringifyEventListenerManager();

    bool init();

    static StringifyEventListenerManager* sharedStringifyEventListenerManager();

	/**
	 * 添加一个事件监听
	 * 由于只需要目标的id,只要是Object对像就行
	 */
    void addEventListener(CCObject* target,const char* type,CCObject* handleObject,yhge::SEL_EventHandle handle);
    
    /**
	 * 添加一个事件监听
	 * 由于只需要目标的id,只要是Object对像就行
	 */
    void addEventListener(CCObject* target,const char* type,EventHandle* handler);
    
	/**
	 * 移除一个事件监听
	 * 由于只需要目标的id,只要是Object对像就行
	 */
    void removeEventListener(CCObject* target,const char* type,CCObject* handleObject,yhge::SEL_EventHandle handle);
    
    void removeEventListener(CCObject* target,const char* type,CCObject* handleObject);
    
    void removeEventListener(CCObject* target,const char* type);
    
    void removeEventListener(CCObject* target);

	void removeEventListenerForHandle(CCObject* target,const char* type,yhge::SEL_EventHandle handle);
    
	/**
	 * 处理事件
	 * 由于只需要目标的id,只要是Object对像就行
	 */
    void handleEvent(CCObject* target,yhge::Event* evt);

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
    void trigger(CCNode* target,const char* type,CCObject* data,bool bubbles);

	
	/**
	 * 触发事件
	 * 普通版，不需要事件传递
	 */
    void dispatchEventWithObject(CCObject* target,yhge::Event* evt);

	/**
	 * 触发事件
	 * 把new EventObject和dispatchEvent和起来，提供简便方法
	 * 普通版，不需要事件传递
	 */
    void triggerWithObject(CCObject* target,const char* type,CCObject* data,bool bubbles);

    bool isListened(CCArray* listeners,yhge::SEL_EventHandle handle,CCObject* handleObject) ;

    CCArray* getEventListeners(CCObject* target,const char* type);
    

  
protected:

    void removeListeners(CCArray* listeners,CCObject* handleObject);
    void removeListeners(CCArray* listeners,CCObject* handleObject,yhge::SEL_EventHandle handle);
	void removeListenersForHandle(CCArray* listeners,yhge::SEL_EventHandle handle);

	void removeListenerMap(CCDictionary* listenerMap,CCObject* handleObject);
	void removeListenerMap(CCDictionary* listenerMap,CCObject* handleObject,yhge::SEL_EventHandle handle);
	void removeListenerMapForHandle(CCDictionary* listenerMap,yhge::SEL_EventHandle handle);

protected:
	CCDictionary* m_pListeners;
};
NS_CC_YHGE_END
#endif  // YHGE_EVENT_STRINGIFYEVENTLISTENERMANAGER_H_