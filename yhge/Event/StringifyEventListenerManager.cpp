#include "StringifyEventListenerManager.h"

NS_CC_YHGE_BEGIN

static StringifyEventListenerManager* s_sharedStringifyEventListenerManager=NULL;

StringifyEventListenerManager::StringifyEventListenerManager()
:_pListeners(NULL)
{

}

StringifyEventListenerManager::~StringifyEventListenerManager()
{
	CC_SAFE_RELEASE(_pListeners);
}

bool StringifyEventListenerManager::init()
{
	_pListeners=new CCDictionary();
    return true;
}

StringifyEventListenerManager* StringifyEventListenerManager::sharedStringifyEventListenerManager()
{
    if(!s_sharedStringifyEventListenerManager){
        s_sharedStringifyEventListenerManager=new StringifyEventListenerManager();
        s_sharedStringifyEventListenerManager->init();
    }
    return s_sharedStringifyEventListenerManager;
}

void StringifyEventListenerManager::addEventListener(Ref* target,const char* type,Ref* handleObject,yhge::SEL_EventHandle handle)
{

    unsigned int targetId=target->_uID;

	CCDictionary* targetListeners=static_cast<CCDictionary*>(_pListeners->objectForKey(targetId));
	if(targetListeners==NULL){
		targetListeners=new CCDictionary();
		_pListeners->setObject(targetListeners,targetId);
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
        CCAssert(0,"StringifyEventListenerManager:Handle has register");
    }

}

void StringifyEventListenerManager::addEventListener(Ref* target,const char* type,EventHandle* handler)
{
    unsigned int targetId=target->_uID;

	CCDictionary* targetListeners=static_cast<CCDictionary*>(_pListeners->objectForKey(targetId));
	if(targetListeners==NULL){
		targetListeners=new CCDictionary();
		_pListeners->setObject(targetListeners,targetId);
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

    if(!isListened(eventListeners,handler->getHandle(),handler->getTarget())) {
        eventListeners->addObject(handler);
    }else{
        CCAssert(0,"StringifyEventListenerManager:Handle has register");
    }
}

void StringifyEventListenerManager::removeEventListener(Ref* target,const char* type,Ref* handleObject,yhge::SEL_EventHandle handle)
{
    CCAssert(target!=NULL,"StringifyEventListenerManager::removeEventListener target is null.");
    CCAssert(handleObject!=NULL,"StringifyEventListenerManager::removeEventListener handleObject is null.");

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

void StringifyEventListenerManager::removeEventListener(Ref* target,const char* type,Ref* handleObject)
{
	removeEventListener(target,type,handleObject,NULL);
}

void StringifyEventListenerManager::removeEventListener(Ref* target,const char* type)
{
    CCAssert(target!=NULL,"StringifyEventListenerManager::removeEventListener target is null.");
    CCAssert(type!=NULL,"StringifyEventListenerManager::removeEventListener type is null.");
    CCDictionary* targetListeners=static_cast<CCDictionary*>(_pListeners->objectForKey(target->_uID));
    targetListeners->removeObjectForKey(type);
}

void StringifyEventListenerManager::removeEventListener(Ref* target)
{
    CCAssert(target!=NULL,"StringifyEventListenerManager::removeEventListener target is null.");
    _pListeners->removeObjectForKey(target->_uID);
}

void StringifyEventListenerManager::removeEventListenerForHandle(Ref* target,const char* type,yhge::SEL_EventHandle handle)
{
	CCAssert(target!=NULL,"StringifyEventListenerManager::removeEventListener target is null.");
    CCAssert(handle!=NULL,"StringifyEventListenerManager::removeEventListener handle is null.");

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


void StringifyEventListenerManager::removeListeners(CCArray* listeners,Ref* handleObject)
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

void StringifyEventListenerManager::removeListeners(CCArray* listeners,Ref* handleObject,SEL_EventHandle handle)
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

void StringifyEventListenerManager::removeListenersForHandle(CCArray* listeners,yhge::SEL_EventHandle handle)
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

void StringifyEventListenerManager::removeListenerMap(CCDictionary* listenerMap,Ref* handleObject)
{
	CCDictElement* element = NULL;
    CCArray* listeners=NULL;
    
    CCDICT_FOREACH(listenerMap,element){
        listeners=(CCArray*) element->getObject();
		if(listeners!=NULL)
			removeListeners(listeners,handleObject);
    }
}

void StringifyEventListenerManager::removeListenerMap(CCDictionary* listenerMap,Ref* handleObject,yhge::SEL_EventHandle handle)
{
	CCDictElement* element = NULL;
    CCArray* listeners=NULL;
    
    CCDICT_FOREACH(listenerMap,element){
        listeners=(CCArray*) element->getObject();
		if(listeners!=NULL)
			removeListeners(listeners,handleObject,handle);
    }
}

void StringifyEventListenerManager::removeListenerMapForHandle(CCDictionary* listenerMap,yhge::SEL_EventHandle handle)
{
	CCDictElement* element = NULL;
    CCArray* listeners=NULL;
    
    CCDICT_FOREACH(listenerMap,element){
        listeners=(CCArray*) element->getObject();
		if(listeners!=NULL)
			removeListenersForHandle(listeners,handle);
    }
}


void StringifyEventListenerManager::handleEvent(Ref* target,Event* evt)
{
	CCDictionary* targetListeners=static_cast<CCDictionary*>(_pListeners->objectForKey(target->_uID));
    if(targetListeners) {
		std::string type=evt->getType();
		if(type!="") {
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

void StringifyEventListenerManager::dispatchEvent(CCNode* target,yhge::Event* evt)
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
void StringifyEventListenerManager::trigger(CCNode* target,const char* type,Ref* data,bool bubbles)
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
void StringifyEventListenerManager::triggerWithObject(Ref* target,const char* type,Ref* data,bool bubbles)
{
	yhge::Event* e=new yhge::Event();
	e->initEvent(type,bubbles,true);
    if (data) {
        e->setData(data);
    }
	
    dispatchEventWithObject(target,e);
	e->release();
}

bool StringifyEventListenerManager::isListened(CCArray* listeners,yhge::SEL_EventHandle handle,Ref* handleObject)
{
    Ref* pObj=NULL;
    EventHandle* eventHandle=NULL;

    CCARRAY_FOREACH(listeners,pObj){
        eventHandle=(EventHandle*) pObj;
        if (eventHandle->getHandle()==handle && eventHandle->getTarget()==handleObject) {
			return true;
		}
    }
    return false;
}

CCArray* StringifyEventListenerManager::getEventListeners(Ref* target,const char* type)
{
    CCDictionary* targetListeners=static_cast<CCDictionary*>(_pListeners->objectForKey(target->_uID));
    if(targetListeners && type) {
		//对应的type事件
        return static_cast<CCArray*>(targetListeners->objectForKey(type));
	}
	return NULL;
}



NS_CC_YHGE_END