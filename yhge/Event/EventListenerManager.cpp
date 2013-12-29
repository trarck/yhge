#include "EventListenerManager.h"

NS_CC_YHGE_BEGIN

static EventListenerManager* s_sharedEventListenerManager=NULL;

EventListenerManager::EventListenerManager()
:m_pListeners(NULL)
{

}

EventListenerManager::~EventListenerManager()
{
	CC_SAFE_RELEASE(m_pListeners);
}

bool EventListenerManager::init()
{
	m_pListeners=new CCDictionary();
    return true;
}

EventListenerManager* EventListenerManager::sharedEventListenerManager()
{
    if(!s_sharedEventListenerManager){
        s_sharedEventListenerManager=new EventListenerManager();
        s_sharedEventListenerManager->init();
    }
    return s_sharedEventListenerManager;
}

void EventListenerManager::addEventListener(CCObject* target,const char* type,CCObject* handleObject,yhge::SEL_EventHandle handle)
{

    unsigned int targetId=target->m_uID;

	CCDictionary* targetListeners=static_cast<CCDictionary*>(m_pListeners->objectForKey(targetId));
	if(targetListeners==NULL){
		targetListeners=new CCDictionary();
		m_pListeners->setObject(targetListeners,targetId);
        targetListeners->release();
	}

    CCArray* eventListeners=static_cast<CCArray*>(targetListeners->objectForKey(type));
    if(eventListeners==NULL){
		eventListeners=new CCArray();
		eventListeners->init();
		targetListeners->setObject(eventListeners,type);
        eventListeners->release();
	}

    //is listened. one type event only have a  handle ,have multi-processor function
    //一个事件只有一个触发点，但有很多处理该事件的函数

    if(!isListened(eventListeners,handle,handleObject)) {
        EventHandle* eventHandle=new EventHandle();
	    eventHandle->initWithTarget(handleObject,handle);
        eventListeners->addObject(eventHandle);
        eventHandle->release();
    }else{
        CCAssert(0,"EventListenerManager:Handle has register");
    }

}

void EventListenerManager::removeEventListener(CCObject* target,const char* type,CCObject* handleObject,yhge::SEL_EventHandle handle)
{
    CCAssert(target!=NULL,"EventListenerManager::removeEventListener target is null.");
    CCAssert(handleObject!=NULL,"EventListenerManager::removeEventListener handleObject is null.");

    CCDictionary* targetListeners=static_cast<CCDictionary*>(m_pListeners->objectForKey(target->m_uID));
    if(targetListeners) {
        if(type) {
            //移除对应的type事件
            CCArray* eventListeners=static_cast<CCArray*>(targetListeners->objectForKey(type));
            if(eventListeners) {
                //某事件有处理函数
                if(handle) {
                    //删除事件中的handler
                    removeListeners(eventListeners,handleObject,handle);
                } else {
                    //删除事件中的处理对象为handleObject的注册项
                    removeListeners(eventListeners,handleObject);
                }
            }
        } else {
           //删除target的所有监听者
			if(handle) {
				removeListenerMap(targetListeners,handleObject,handle);
			}else{
				removeListenerMap(targetListeners,handleObject);
			}
        }
    }
}

void EventListenerManager::removeEventListener(CCObject* target,const char* type,CCObject* handleObject)
{
	removeEventListener(target,type,handleObject,NULL);
}

void EventListenerManager::removeEventListener(CCObject* target,const char* type)
{
    CCAssert(target!=NULL,"EventListenerManager::removeEventListener target is null.");
    CCAssert(type!=NULL,"EventListenerManager::removeEventListener type is null.");
    CCDictionary* targetListeners=static_cast<CCDictionary*>(m_pListeners->objectForKey(target->m_uID));
    targetListeners->removeObjectForKey(type);
}

void EventListenerManager::removeEventListener(CCObject* target)
{
    CCAssert(target!=NULL,"EventListenerManager::removeEventListener target is null.");
    m_pListeners->removeObjectForKey(target->m_uID);
}

void EventListenerManager::removeEventListenerForHandle(CCObject* target,const char* type,yhge::SEL_EventHandle handle)
{
	CCAssert(target!=NULL,"EventListenerManager::removeEventListener target is null.");
    CCAssert(handle!=NULL,"EventListenerManager::removeEventListener handle is null.");

    CCDictionary* targetListeners=static_cast<CCDictionary*>(m_pListeners->objectForKey(target->m_uID));
    if(targetListeners) {
        if(type) {
            //移除对应的type事件
            CCArray* eventListeners=static_cast<CCArray*>(targetListeners->objectForKey(type));
            if(eventListeners) {
                //删除事件中的handler
                removeListenersForHandle(eventListeners,handle);
            }
        } else {
           //删除target的所有监听者
		   removeListenerMapForHandle(targetListeners,handle);
        }
    }
}


void EventListenerManager::removeListeners(CCArray* listeners,CCObject* handleObject)
{
    //使用index删除，效率会高些。但要注意删除后的空位置.
    //如果使用object删除，则效率会低些，但不会有空位引发的问题。
    
    CCObject* pObject = NULL;
    if (listeners && listeners->data->num > 0){         
        int len=listeners->data->num;
        CCObject** arr = listeners->data->arr;
        for(int i=0;i<len;){
		    EventHandle* eventHandle=(EventHandle*)(*(arr+i));
		    if (eventHandle->getTarget()==handleObject) {
			    listeners->removeObjectAtIndex(i);
                --len;
		    }else{
                ++i;
            }
	    }
    }
}

void EventListenerManager::removeListeners(CCArray* listeners,CCObject* handleObject,SEL_EventHandle handle)
{
    //使用index删除，效率会高些。但要注意删除后的空位置.
    //如果使用object删除，则效率会低些，但不会有空位引发的问题。

    CCObject* pObject = NULL;
    if (listeners && listeners->data->num > 0){         
        int len=listeners->data->num;
        CCObject** arr = listeners->data->arr;
        for(int i=0;i<len;){
		    EventHandle* eventHandle=(EventHandle*)(*(arr+i));
		    if (eventHandle->getTarget()==handleObject && eventHandle->getHandle()==handle) {
			    listeners->removeObjectAtIndex(i);
                --len;
		    }else{
                ++i;
            }
	    }
    }
}

void EventListenerManager::removeListenersForHandle(CCArray* listeners,yhge::SEL_EventHandle handle)
{
	CCObject* pObject = NULL;
    if (listeners && listeners->data->num > 0){         
        int len=listeners->data->num;
        CCObject** arr = listeners->data->arr;
        for(int i=0;i<len;){
		    EventHandle* eventHandle=(EventHandle*)(*(arr+i));
		    if (eventHandle->getHandle()==handle) {
			    listeners->removeObjectAtIndex(i);
                --len;
		    }else{
                ++i;
            }
	    }
    }
}

void EventListenerManager::removeListenerMap(CCDictionary* listenerMap,CCObject* handleObject)
{
	CCDictElement* element = NULL;
    CCArray* listeners=NULL;
    
    CCDICT_FOREACH(listenerMap,element){
        listeners=(CCArray*) element->getObject();
		if(listeners!=NULL)
			removeListeners(listeners,handleObject);
    }
}

void EventListenerManager::removeListenerMap(CCDictionary* listenerMap,CCObject* handleObject,yhge::SEL_EventHandle handle)
{
	CCDictElement* element = NULL;
    CCArray* listeners=NULL;
    
    CCDICT_FOREACH(listenerMap,element){
        listeners=(CCArray*) element->getObject();
		if(listeners!=NULL)
			removeListeners(listeners,handleObject,handle);
    }
}

void EventListenerManager::removeListenerMapForHandle(CCDictionary* listenerMap,yhge::SEL_EventHandle handle)
{
	CCDictElement* element = NULL;
    CCArray* listeners=NULL;
    
    CCDICT_FOREACH(listenerMap,element){
        listeners=(CCArray*) element->getObject();
		if(listeners!=NULL)
			removeListenersForHandle(listeners,handle);
    }
}


void EventListenerManager::handleEvent(CCObject* target,Event* evt)
{
	CCDictionary* targetListeners=static_cast<CCDictionary*>(m_pListeners->objectForKey(target->m_uID));
    if(targetListeners) {
		std::string type=evt->getType();
		if(type!="") {
			//执行对应的type事件
            CCArray* eventListeners=static_cast<CCArray*>(targetListeners->objectForKey(type));
            if(eventListeners) {
				CCObject* pObj=NULL;
				EventHandle* eventHandle=NULL;
                CCARRAY_FOREACH(eventListeners,pObj){
					eventHandle=static_cast<EventHandle*>(pObj);
					eventHandle->execute(evt);
				}
            }
		}
	}
}

void EventListenerManager::dispatchEvent(CCNode* target,yhge::Event* evt)
{
    // Capture no
    
    // Target
    //event.currentTarget=obj;
    handleEvent(target,evt);
    // Bubble
	CCNode* parent=target->getParent();
    while(parent && !evt->isDispatchStopped()){
        //event.currentTarget=parent;
        handleEvent(parent,evt);
        parent=parent->getParent();
    }
}

//把new EventObject和dispatchEvent和起来，提供简便方法
void EventListenerManager::trigger(CCNode* target,const char* type,CCObject* data,bool bubbles)
{    
    yhge::Event* e=new yhge::Event();
	e->initEvent(type,bubbles,true);
    if (data) {
        e->setData(data);
    }
	
    dispatchEvent(target,e);
	e->release();
}

/**
	* 触发事件
	* 普通版，不需要事件传递
	*/
void EventListenerManager::dispatchEventWithObject(CCObject* target,yhge::Event* evt)
{
	handleEvent(target,evt);
}

/**
	* 触发事件
	* 把new EventObject和dispatchEvent和起来，提供简便方法
	* 普通版，不需要事件传递
	*/
void EventListenerManager::triggerWithObject(CCObject* target,const char* type,CCObject* data,bool bubbles)
{
	yhge::Event* e=new yhge::Event();
	e->initEvent(type,bubbles,true);
    if (data) {
        e->setData(data);
    }
	
    dispatchEventWithObject(target,e);
	e->release();
}

bool EventListenerManager::isListened(CCArray* listeners,yhge::SEL_EventHandle handle,CCObject* handleObject)
{
    CCObject* pObj=NULL;
    EventHandle* eventHandle=NULL;

    CCARRAY_FOREACH(listeners,pObj){
        eventHandle=(EventHandle*) pObj;
        if (eventHandle->getHandle()==handle && eventHandle->getTarget()==handleObject) {
			return true;
		}
    }
    return false;
}

CCArray* EventListenerManager::getEventListeners(CCObject* target,const char* type)
{
    CCDictionary* targetListeners=static_cast<CCDictionary*>(m_pListeners->objectForKey(target->m_uID));
    if(targetListeners && type) {
		//对应的type事件
        return static_cast<CCArray*>(targetListeners->objectForKey(type));
	}
	return NULL;
}



NS_CC_YHGE_END