
#ifndef YHGE_EVENT_CCEVENTLISTENERMANAGER_H_
#define YHGE_EVENT_CCEVENTLISTENERMANAGER_H_

#include "cocos2d.h"
#include "YHGEMacros.h"
#include "Event.h"
#include "EventHandle.h"

NS_CC_YHGE_BEGIN

class EventListenerManager:public CCObject
{
public:
    EventListenerManager();

    ~EventListenerManager();

    bool init();

    static EventListenerManager* sharedEventListenerManager();

    void addEventListener(CCNode* target,const char* type,CCObject* handleObject,yhge::SEL_EventHandle handle);
    
    void removeEventListener(CCNode* target,const char* type,CCObject* handleObject,yhge::SEL_EventHandle handle);
    
    void removeEventListener(CCNode* target,const char* type,CCObject* handleObject);
    
    void removeEventListener(CCNode* target,const char* type);
    
    void removeEventListener(CCNode* target);

	void removeEventListenerForHandle(CCNode* target,const char* type,yhge::SEL_EventHandle handle);
        
    void dispatchEvent(CCNode* target,yhge::Event* evt);

    void handleEvent(CCNode* target,yhge::Event* evt);

    bool isListened(CCArray* listeners,yhge::SEL_EventHandle handle,CCObject* handleObject) ;

    CCArray* getEventListeners(CCNode* target,const char* type);
    
    //把new EventObject和dispatchEvent和起来，提供简便方法
    void trigger(CCNode* target,const char* type,CCObject* data,bool bubbles);
  
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
#endif  // YHGE_EVENT_CCEVENTLISTENERMANAGER_H_