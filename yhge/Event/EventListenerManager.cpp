#include "EventListenerManager.h"

NS_CC_YHGE_BEGIN

static EventListenerManager* s_sharedEventListenerManager=NULL;

EventListenerManager::EventListenerManager()
{

}

EventListenerManager::~EventListenerManager()
{
}

bool EventListenerManager::init()
{
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

void EventListenerManager::addEventListener(Ref* target,int type,Ref* handleObject,yhge::SEL_EventHandle handle)
{

    EventHandleList eventListeners=_listeners[target][type];
  

    //is listened. one type event only have a  handle ,have multi-processor function
    //一个事件只有一个触发点，但有很多处理该事件的函数

    if(!isListened(eventListeners,handle,handleObject)) {
        EventHandle* eventHandle=new EventHandle();
	    eventHandle->initWithTarget(handleObject,handle);
		_listeners[target][type].pushBack(eventHandle);
        eventHandle->release();
    }else{
        CCASSERT(0,"EventListenerManager:Handle has register");
    }
}

void EventListenerManager::addEventListener(Ref* target,int type,EventHandle* handler)
{

	EventHandleList eventListeners = _listeners[target][type];
    //is listened. one type event only have a  handle ,have multi-processor function
    //一个事件只有一个触发点，但有很多处理该事件的函数

    if(!isListened(eventListeners,handler->getHandle(),handler->getTarget())) {
		_listeners[target][type]->addObject(handler);
    }else{
        CCASSERT(0,"EventListenerManager:Handle has register");
    }
}

void EventListenerManager::removeEventListener(Ref* target,int type,Ref* handleObject,yhge::SEL_EventHandle handle)
{
    CCASSERT(target!=NULL,"EventListenerManager::removeEventListener target is null.");
    CCASSERT(handleObject!=NULL,"EventListenerManager::removeEventListener handleObject is null.");

    CCDictionary* targetListeners=static_cast<CCDictionary*>(_pListeners->objectForKey(target->_uID));
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

void EventListenerManager::removeEventListener(Ref* target,int type,Ref* handleObject)
{
	removeEventListener(target,type,handleObject,NULL);
}

void EventListenerManager::removeEventListener(Ref* target,int type)
{
    CCASSERT(target!=NULL,"EventListenerManager::removeEventListener target is null.");
    CCDictionary* targetListeners=static_cast<CCDictionary*>(_pListeners->objectForKey(target->_uID));
    targetListeners->removeObjectForKey(type);
}

void EventListenerManager::removeEventListener(Ref* target)
{
    CCASSERT(target!=NULL,"EventListenerManager::removeEventListener target is null.");
    _pListeners->removeObjectForKey(target->_uID);
}

void EventListenerManager::removeEventListenerForHandle(Ref* target,int type,yhge::SEL_EventHandle handle)
{
	CCASSERT(target!=NULL,"EventListenerManager::removeEventListener target is null.");
    CCASSERT(handle!=NULL,"EventListenerManager::removeEventListener handle is null.");

    CCDictionary* targetListeners=static_cast<CCDictionary*>(_pListeners->objectForKey(target->_uID));
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


void EventListenerManager::removeListeners(CCArray* listeners,Ref* handleObject)
{
    //使用index删除，效率会高些。但要注意删除后的空位置.
    //如果使用object删除，则效率会低些，但不会有空位引发的问题。
    
    if (listeners && listeners->data->num > 0){
        int len=listeners->data->num;
        Ref** arr = listeners->data->arr;
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

void EventListenerManager::removeListeners(CCArray* listeners,Ref* handleObject,SEL_EventHandle handle)
{
    //使用index删除，效率会高些。但要注意删除后的空位置.
    //如果使用object删除，则效率会低些，但不会有空位引发的问题。

    if (listeners && listeners->data->num > 0){         
        int len=listeners->data->num;
        Ref** arr = listeners->data->arr;
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
    if (listeners && listeners->data->num > 0){
        int len=listeners->data->num;
        Ref** arr = listeners->data->arr;
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

void EventListenerManager::removeListenerMap(CCDictionary* listenerMap,Ref* handleObject)
{
	CCDictElement* element = NULL;
    CCArray* listeners=NULL;
    
    CCDICT_FOREACH(listenerMap,element){
        listeners=(CCArray*) element->getObject();
		if(listeners!=NULL)
			removeListeners(listeners,handleObject);
    }
}

void EventListenerManager::removeListenerMap(CCDictionary* listenerMap,Ref* handleObject,yhge::SEL_EventHandle handle)
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


void EventListenerManager::handleEvent(Ref* target,Event* evt)
{
	CCDictionary* targetListeners=static_cast<CCDictionary*>(_pListeners->objectForKey(target->_uID));
    if(targetListeners) {
		int type=evt->getIntType();
		if(type!=0) {
			//执行对应的type事件
            CCArray* eventListeners=static_cast<CCArray*>(targetListeners->objectForKey(type));
            if(eventListeners) {
				Ref* pObj=NULL;
				EventHandle* eventHandle=NULL;
                CCARRAY_FOREACH(eventListeners,pObj){
					eventHandle=static_cast<EventHandle*>(pObj);
					eventHandle->execute(evt);
				}
            }
		}
	}
}

void EventListenerManager::dispatchEvent(Node* target,yhge::Event* evt)
{
    // Capture no
    
    // Target
    //event.currentTarget=obj;
    handleEvent(target,evt);
    // Bubble
	Node* parent=target->getParent();
    while(parent && !evt->isDispatchStopped()){
        //event.currentTarget=parent;
        handleEvent(parent,evt);
        parent=parent->getParent();
    }
}

//把new EventObject和dispatchEvent和起来，提供简便方法
void EventListenerManager::trigger(Node* target,int type,Ref* data,bool bubbles)
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
void EventListenerManager::dispatchEventWithObject(Ref* target,yhge::Event* evt)
{
	handleEvent(target,evt);
}

/**
	* 触发事件
	* 把new EventObject和dispatchEvent和起来，提供简便方法
	* 普通版，不需要事件传递
	*/
void EventListenerManager::triggerWithObject(Ref* target,int type,Ref* data,bool bubbles)
{
	yhge::Event* e=new yhge::Event();
	e->initEvent(type,bubbles,true);
    if (data) {
        e->setData(data);
    }
	
    dispatchEventWithObject(target,e);
	e->release();
}

bool EventListenerManager::isListened(EventHandleList& listeners, yhge::SEL_EventHandle handle, Ref* handleObject)
{
	EventHandle* eventHandle = NULL;

	for (EventHandleList::iterator iter = listeners.begin(); iter != listeners.end(); ++iter){
		eventHandle = *iter;
		if (eventHandle->getHandle() == handle && eventHandle->getTarget() == handleObject) {
			return true;
		}
	}

    return false;
}

EventHandleList& EventListenerManager::getEventListeners(Ref* target, int type)
{
	return _listeners[target][type];
}

NS_CC_YHGE_END