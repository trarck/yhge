#include "StringifyEventListenerManager.h"

NS_CC_YHGE_BEGIN

static StringifyEventListenerManager* s_sharedStringifyEventListenerManager=NULL;

StringifyEventListenerManager::StringifyEventListenerManager()
{

}

StringifyEventListenerManager::~StringifyEventListenerManager()
{

}

bool StringifyEventListenerManager::init()
{
    return true;
}

StringifyEventListenerManager* StringifyEventListenerManager::getInstance()
{
    if(!s_sharedStringifyEventListenerManager){
        s_sharedStringifyEventListenerManager=new StringifyEventListenerManager();
        s_sharedStringifyEventListenerManager->init();
    }
    return s_sharedStringifyEventListenerManager;
}

void StringifyEventListenerManager::destroyInstance()
{
	CC_SAFE_RELEASE_NULL(s_sharedStringifyEventListenerManager);
}

void StringifyEventListenerManager::addEventListener(Ref* target,const std::string& type,Ref* handleObject,yhge::SEL_EventHandle handle)
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

void StringifyEventListenerManager::addEventListener(Ref* target,const std::string& type,EventHandle* handler)
{
	EventHandleList eventListeners = _listeners[target][type];

    //is listened. one type event only have a  handle ,have multi-processor function
    //一个事件只有一个触发点，但有很多处理该事件的函数
	
    if(!isListened(eventListeners,handler->getHandle(),handler->getTarget())) {
		_listeners[target][type].pushBack(handler);
    }else{
        CCASSERT(0,"EventListenerManager:Handle has register");
    }
}

void StringifyEventListenerManager::removeEventListener(Ref* target,const std::string& type,Ref* handleObject,yhge::SEL_EventHandle handle)
{
    CCAssert(target!=NULL,"StringifyEventListenerManager::removeEventListener target is null.");
    CCAssert(handleObject!=NULL,"StringifyEventListenerManager::removeEventListener handleObject is null.");

    EventListenerMap::iterator targetListenersIter=_listeners.find(target);

    if(targetListenersIter!=_listeners.end()) {
        if(!type.empty()) {
            //移除对应的type事件
			EventTypeMap::iterator eventListenersItor=targetListenersIter->second.find(type);

            if(eventListenersItor!=targetListenersIter->second.end()) {
                //某事件有处理函数
                if(handle) {
                    //删除事件中的handler
                    removeListeners(eventListenersItor->second,handleObject,handle);
                } else {
                    //删除事件中的处理对象为handleObject的注册项
                    removeListeners(eventListenersItor->second,handleObject);
                }

				if(eventListenersItor->second.empty()){
					targetListenersIter->second.erase(eventListenersItor);
				}
            }
        } else {
           //删除target的所有监听者
			if(handle) {
				removeListenerMap(targetListenersIter->second,handleObject,handle);
			}else{
				removeListenerMap(targetListenersIter->second,handleObject);
			}
        }

		
		if(targetListenersIter->second.empty()){
			_listeners.erase(targetListenersIter);
		}
    }
}

void StringifyEventListenerManager::removeEventListener(Ref* target,const std::string& type,Ref* handleObject)
{
	removeEventListener(target,type,handleObject,NULL);
}

void StringifyEventListenerManager::removeEventListener(Ref* target,const std::string& type)
{
    CCAssert(target!=NULL,"StringifyEventListenerManager::removeEventListener target is null.");
		
	EventListenerMap::iterator targetListenersIter=_listeners.find(target);

	if(targetListenersIter!=_listeners.end()){
		EventTypeMap::iterator eventListenersItor=targetListenersIter->second.find(type);
		if(eventListenersItor!=targetListenersIter->second.end()) {
			targetListenersIter->second.erase(eventListenersItor);
		}

		if(targetListenersIter->second.empty()){
			_listeners.erase(targetListenersIter);
		}
	}
}

void StringifyEventListenerManager::removeEventListener(Ref* target)
{
    CCAssert(target!=NULL,"StringifyEventListenerManager::removeEventListener target is null.");
    EventListenerMap::iterator targetListenersIter=_listeners.find(target);

	if(targetListenersIter!=_listeners.end()){
		_listeners.erase(targetListenersIter);
	}
}

void StringifyEventListenerManager::removeEventListenerForHandle(Ref* target,const std::string& type,yhge::SEL_EventHandle handle)
{
	CCAssert(target!=NULL,"StringifyEventListenerManager::removeEventListener target is null.");
    CCAssert(handle!=NULL,"StringifyEventListenerManager::removeEventListener handle is null.");

    EventListenerMap::iterator targetListenersIter=_listeners.find(target);

    if(targetListenersIter!=_listeners.end()) {
        if(!type.empty()) {
            //移除对应的type事件
            EventTypeMap::iterator eventListenersItor=targetListenersIter->second.find(type);

            if(eventListenersItor!=targetListenersIter->second.end()) {
                //删除事件中的handler
                removeListenersForHandle(eventListenersItor->second,handle);

				if(eventListenersItor->second.empty()){
					targetListenersIter->second.erase(eventListenersItor);
				}
            }
        } else {
           //删除target的所有监听者
		   removeListenerMapForHandle(targetListenersIter->second,handle);
        }

		if(targetListenersIter->second.empty()){
			_listeners.erase(targetListenersIter);
		}
    }
}


void StringifyEventListenerManager::removeListeners(EventHandleList& listeners,Ref* handleObject)
{
    //使用index删除，效率会高些。但要注意删除后的空位置.
    //如果使用object删除，则效率会低些，但不会有空位引发的问题。
    for(EventHandleList::iterator iter=listeners.begin();iter!=listeners.end();){
		if ((*iter)->getTarget()==handleObject) {
			iter=listeners.erase(iter);
		}else{
            ++iter;
        }
	}
}

void StringifyEventListenerManager::removeListeners(EventHandleList& listeners,Ref* handleObject,SEL_EventHandle handle)
{
    //使用index删除，效率会高些。但要注意删除后的空位置.
    //如果使用object删除，则效率会低些，但不会有空位引发的问题。

    for(EventHandleList::iterator iter=listeners.begin();iter!=listeners.end();){
		if ((*iter)->getTarget()==handleObject && (*iter)->getHandle()==handle) {
			iter=listeners.erase(iter);
		}else{
            ++iter;
        }
	}
}

void StringifyEventListenerManager::removeListenersForHandle(EventHandleList& listeners,yhge::SEL_EventHandle handle)
{
    for(EventHandleList::iterator iter=listeners.begin();iter!=listeners.end();){
		if ((*iter)->getHandle()==handle) {
			iter=listeners.erase(iter);
		}else{
            ++iter;
        }
	}
}

void StringifyEventListenerManager::removeListenerMap(EventTypeMap& listenerMap,Ref* handleObject)
{
	for(EventTypeMap::iterator iter=listenerMap.begin();iter!=listenerMap.end();++iter){
		removeListeners(iter->second,handleObject);
	}
}

void StringifyEventListenerManager::removeListenerMap(EventTypeMap& listenerMap,Ref* handleObject,yhge::SEL_EventHandle handle)
{
	for(EventTypeMap::iterator iter=listenerMap.begin();iter!=listenerMap.end();++iter){
		removeListeners(iter->second,handleObject,handle);
	}
}

void StringifyEventListenerManager::removeListenerMapForHandle(EventTypeMap& listenerMap,yhge::SEL_EventHandle handle)
{
	for(EventTypeMap::iterator iter=listenerMap.begin();iter!=listenerMap.end();++iter){
		removeListenersForHandle(iter->second,handle);
	}
}


void StringifyEventListenerManager::handleEvent(Ref* target,Event* evt)
{
	EventListenerMap::iterator targetListenersIter=_listeners.find(target);

    if(targetListenersIter!=_listeners.end()) {
		std::string type=evt->getStrType();
		if(!type.empty()) {
			//执行对应的type事件
            EventTypeMap::iterator eventListenersItor=targetListenersIter->second.find(type);

            if(eventListenersItor!=targetListenersIter->second.end()) {
				//copy listener list
				EventHandleList eventListeners=eventListenersItor->second;

				for(EventHandleList::iterator iter=eventListeners.begin();iter!=eventListeners.end();++iter){
					(*iter)->execute(evt);
				}
            }
		}
	}
}

void StringifyEventListenerManager::dispatchEvent(Node* target,yhge::Event* evt)
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
void StringifyEventListenerManager::trigger(Node* target,const std::string& type,Ref* data,bool bubbles)
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
void StringifyEventListenerManager::dispatchEventWithObject(Ref* target,yhge::Event* evt)
{
	handleEvent(target,evt);
}

/**
	* 触发事件
	* 把new EventObject和dispatchEvent和起来，提供简便方法
	* 普通版，不需要事件传递
	*/
void StringifyEventListenerManager::triggerWithObject(Ref* target,const std::string& type,Ref* data,bool bubbles)
{
	yhge::Event* e=new yhge::Event();
	e->initEvent(type,bubbles,true);
    if (data) {
        e->setData(data);
    }
	
    dispatchEventWithObject(target,e);
	e->release();
}

bool StringifyEventListenerManager::isListened(EventHandleList& listeners,yhge::SEL_EventHandle handle,Ref* handleObject)
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

StringifyEventListenerManager::EventHandleList& StringifyEventListenerManager::getEventListeners(Ref* target,const std::string& type)
{
    return _listeners[target][type];
}

NS_CC_YHGE_END