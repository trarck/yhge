//
//  MessageManager.m
//  Message
//
//  Created by trarck on 11-11-27.
//

#include "MessageManager.h"

NS_CC_YHGE_BEGIN

const int kNullObjectId=0;

static MessageManager* s_sharedMessageManagerInstance=NULL;

MessageManager::MessageManager()
:m_messages(NULL)
,m_globalObject(NULL)
{
	//CCLOG("MessageManager create");
}

MessageManager::~MessageManager()
{
	//CCLOG("MessageManager destroy begin");
	CC_SAFE_RELEASE_NULL(m_messages);
	CC_SAFE_RELEASE_NULL(m_globalObject);
	//CC_SAFE_RELEASE(m_regiesterMap);
	//CCLOG("MessageManager destroy end");
}

MessageManager* MessageManager::defaultManager(void)
{
	if (!s_sharedMessageManagerInstance) {
		s_sharedMessageManagerInstance=new MessageManager();
		s_sharedMessageManagerInstance->init();
	}
	return s_sharedMessageManagerInstance;
}

bool MessageManager::init()
{
	m_messages=new CCDictionary();
	m_globalObject=new Ref();
	return true;
}

bool MessageManager::registerReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle ,Ref*  handleObject)
{
	CCAssert(receiver!=NULL,"MessageManage:registerReceiver:receiver can't be null");
	CCAssert(handle!=NULL,"MessageManage:registerReceiver:handle");
	CCAssert(handleObject!=NULL,"MessageManage:registerReceiver:handleObject");

	//type等于0，则所有消息都会发送
	//register for type
	CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
	if (msgMap==NULL) {
		msgMap=new CCDictionary();
		m_messages->setObject(msgMap,type);
		msgMap->release();
	}
    //register for receiver
	unsigned int receiverKey=receiver->m_uID;
    CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiverKey);
	if (!receiverMap) {
		receiverMap=new CCDictionary();
	    msgMap->setObject(receiverMap ,receiverKey);
		receiverMap->release();
	}

	//register for sender
	//sender 为空，则注册到全局对象上
	unsigned int senderKey=sender==NULL?kNullObjectId:sender->m_uID;
	CCArray *handleList=(CCArray*)receiverMap->objectForKey(senderKey);
	if (!handleList) {
        handleList=new CCArray();
		receiverMap->setObject(handleList,senderKey);
		handleList->release();
	}

#ifdef MESSAGE_REGIEST_REPEAT
	MessageHandler *handler=new MessageHandler();
	handler->initWithTarget(handleObject,handle);
	handleList->addObject(handler);
	handler->release();
	
	return true;
	
#else
	//检查是否已经注册过
    bool isRegisted=false;
    Ref* pObject = NULL;
    CCARRAY_FOREACH(handleList,pObject){
        MessageHandler* handler=(MessageHandler*) pObject;
        if (handler->getHandle()==handle && handler->getTarget()==handleObject) {
			CCAssert(0,"Handle has register");
            isRegisted=true;
            break;
		}
    }

    if(!isRegisted){
       
        //register for handler
        MessageHandler *handler=new MessageHandler();
        handler->initWithTarget(handleObject,handle);
        handleList->addObject(handler);
        handler->release();
    }
	return !isRegisted;
#endif
}

//使receiver可以接收sender发送过来的叫type的消息，并用handle来处理
//关注的对象是receiver
bool MessageManager::registerReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle)
{
	return registerReceiver(receiver,type ,sender  ,handle,receiver);
}

bool MessageManager::registerReceiver(Ref* receiver ,unsigned int type ,Ref* sender,MessageHandler* handler)
{
	CCAssert(receiver!=NULL,"MessageManage:registerReceiver:receiver can't be null");
	CCAssert(handler!=NULL,"MessageManage:registerReceiver:handle");

	//type等于0，则所有消息都会发送
	//register for type
	CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
	if (msgMap==NULL) {
		msgMap=new CCDictionary();
		m_messages->setObject(msgMap,type);
		msgMap->release();
	}
    //register for receiver
	unsigned int receiverKey=receiver->m_uID;
    CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiverKey);
	if (!receiverMap) {
		receiverMap=new CCDictionary();
	    msgMap->setObject(receiverMap ,receiverKey);
		receiverMap->release();
	}

	//register for sender
	//sender 为空，则注册到全局对象上
	unsigned int senderKey=sender==NULL?kNullObjectId:sender->m_uID;
	CCArray *handleList=(CCArray*)receiverMap->objectForKey(senderKey);
	if (!handleList) {
        handleList=new CCArray();
		receiverMap->setObject(handleList,senderKey);
		handleList->release();
	}

#ifdef MESSAGE_REGIEST_REPEAT
	handleList->addObject(handler);
	return true;
#else
	//检查是否已经注册过
    bool isRegisted=false;
    Ref* pObject = NULL;
    MessageHandler* handlerItem=NULL;
    CCARRAY_FOREACH(handleList,pObject){
        handlerItem=(MessageHandler*) pObject;
        if (handler->getTarget()==handlerItem->getTarget() && handler->getHandle()==handlerItem->getHandle()) {
			CCAssert(0,"Handle has register");
            isRegisted=true;
            break;
		}
    }

    if(!isRegisted){
        //register for handler
        handleList->addObject(handler);
    }
	return !isRegisted;
#endif
}

/**
 * 检查是否已经注册某个消息。
 */
bool MessageManager::isRegisterReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle ,Ref*  handleObject)
{
	CCAssert(receiver!=NULL,"MessageManage:registerReceiver:receiver can't be null");
	CCAssert(handle!=NULL,"MessageManage:registerReceiver:handle");
	CCAssert(handleObject!=NULL,"MessageManage:registerReceiver:handleObject");

	//type等于0，则所有消息都会发送
	//register for type
	CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
	if (msgMap==NULL) {
		return false;
	}
    //register for receiver
	unsigned int receiverKey=receiver->m_uID;
    CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiverKey);
	if (!receiverMap) {
		return false;
	}

	//register for sender
	//sender 为空，则注册到全局对象上
	unsigned int senderKey=sender==NULL?kNullObjectId:sender->m_uID;
	CCArray *handleList=(CCArray*)receiverMap->objectForKey(senderKey);
	if (!handleList) {
       return false;
	}

	bool isRegisted=false;
    Ref* pObject = NULL;
    CCARRAY_FOREACH(handleList,pObject){
        MessageHandler* handler=(MessageHandler*) pObject;
        if (handler->getHandle()==handle && handler->getTarget()==handleObject) {
            isRegisted=true;
            break;
		}
    }

	return isRegisted;
}

bool MessageManager::isRegisterReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle)
{
	return isRegisterReceiver(receiver,type,sender,handle,receiver);
}

/**
 * 取消注册到接收者的处理对象的处理方法，该方法注册到发送者的某个消息。
 * 如果消息类型是AllMessage，则只取消对AllMessage注册的项
 */
void MessageManager::removeReceiver(Ref* receiver,unsigned int type ,Ref* sender,SEL_MessageHandler handle,Ref*  handleObject)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	CCAssert(handle!=NULL,"MessageManager:removeReceiver:handle can't be null!");
    CCAssert(handleObject!=NULL,"MessageManager:removeReceiver:handleObject can't be null!");
    
    CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

    if(msgMap){
        CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(receiverMap){
            if(sender){
                //移除注册到sender的记录
                CCArray* handleList=(CCArray*)receiverMap->objectForKey(sender->m_uID);
                if(handleList){
                    removeHandleList(handleList, handle,handleObject);
					//删除没有数据的记录
					if(handleList->count()==0){
						receiverMap->removeObjectForKey(sender->m_uID);
					}
                }
            }else{
                //移除所有receiver记录
                removeReceiverMap(receiverMap, handle,handleObject);
            }
			//删除没有数据的记录
			if(receiverMap->count()==0){
				msgMap->removeObjectForKey(receiver->m_uID);
			}
        }
    }
}

/**
 * 取消接收者的处理方法，该方法注册到发送者的某个消息。
 */
void MessageManager::removeReceiver(Ref* receiver,unsigned int type ,Ref* sender,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	CCAssert(handle!=NULL,"MessageManager:removeReceiver:handle can't be null!");

    CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

    if(msgMap){
        CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(receiverMap){
            if(sender){
                //移除注册到sender的记录
                CCArray* handleList=(CCArray*)receiverMap->objectForKey(sender->m_uID);
                if(handleList){
                    removeHandleList(handleList, handle);
					//删除没有数据的记录
					if(handleList->count()==0){
						receiverMap->removeObjectForKey(sender->m_uID);
					}
                }
            }else{
                //移除所有receiver记录
                removeReceiverMap(receiverMap, handle);
            }
			//删除没有数据的记录
			if(receiverMap->count()==0){
				msgMap->removeObjectForKey(receiver->m_uID);
			}
        }
    }
}

/**
 * 取消接收者注册到某个发送者的某个消息的所有处理方法。
 */
void MessageManager::removeReceiver(Ref* receiver,unsigned int type ,Ref* sender)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");

    CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

    if(msgMap){
        CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(receiverMap){
            if(sender){
                //移除注册到sender的记录
                CCArray* handleList=(CCArray*)receiverMap->objectForKey(sender->m_uID);
                if(handleList){
                     removeHandleList(handleList);
					 //删除没有数据的记录
					 receiverMap->removeObjectForKey(sender->m_uID);
                }
	        }else{
                //移除所有receiver记录
                removeReceiverMap(receiverMap);
            }
			//删除没有数据的记录
			if(receiverMap->count()==0){
				msgMap->removeObjectForKey(receiver->m_uID);
			}
        }
    }
}

/**
 * 取消接收者注册到某个消息的所有处理方法。
 */
void MessageManager::removeReceiver(Ref* receiver,unsigned int type)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");

	 CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

    if(msgMap){
        CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(receiverMap){
            //移除所有receiver记录
            removeReceiverMap(receiverMap);
			//删除没有数据的记录
			msgMap->removeObjectForKey(receiver->m_uID);
        }
    }
}

/**
 * 取消接收者的所以注册信息。
 */
void MessageManager::removeReceiver(Ref* receiver)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
    
    CCDictElement* msgMapElement = NULL;
    CCDictionary* msgMap=NULL;
	CCDictionary* receiverMap=NULL;
    
    CCDICT_FOREACH(m_messages,msgMapElement){
        msgMap=(CCDictionary*) msgMapElement->getObject();
        receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(receiverMap){
            //移除所有receiver记录
            removeReceiverMap(receiverMap);
			//删除没有数据的记录
			msgMap->removeObjectForKey(receiver->m_uID);
        }
    }
}

void MessageManager::removeReceiver(Ref* receiver,unsigned int type ,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	CCAssert(handle!=NULL,"MessageManager:removeReceiver:handle can't be null!");
    
    CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

    if(msgMap){
        CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(receiverMap){
            //移除所有receiver记录
            removeReceiverMap(receiverMap,handle);
			//删除没有数据的记录
			if(receiverMap->count()==0){
				msgMap->removeObjectForKey(receiver->m_uID);
			}
        }
    }
}

void MessageManager::removeReceiver(Ref* receiver,Ref* sender,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	CCAssert(sender!=NULL,"MessageManager:removeReceiver:sender can't be null!");
	CCAssert(handle!=NULL,"MessageManager:removeReceiver:handle can't be null!");

    CCDictElement* msgMapElement = NULL;
    CCDictionary* msgMap=NULL;
	CCDictionary* receiverMap=NULL;
    CCArray* handleList=NULL;

    CCDICT_FOREACH(m_messages,msgMapElement){
        msgMap=(CCDictionary*) msgMapElement->getObject();
        receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(receiverMap){
            handleList=(CCArray*)receiverMap->objectForKey(sender->m_uID);
            if(handleList){
                //移除所有receiver记录
                removeHandleList(handleList,handle);
				//删除没有数据的记录
				if(handleList->count()==0){
					receiverMap->removeObjectForKey(sender->m_uID);
				}
            }
			//删除没有数据的记录
			if(receiverMap->count()==0){
				msgMap->removeObjectForKey(receiver->m_uID);
			}
        }
    }
}

void MessageManager::removeReceiver(Ref* receiver,Ref* sender)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
    CCAssert(sender!=NULL,"MessageManager:removeReceiver:sender can't be null!");

    CCDictElement* msgMapElement = NULL;
    CCDictionary* msgMap=NULL;
	CCDictionary* receiverMap=NULL;
    CCArray* handleList=NULL;

    CCDICT_FOREACH(m_messages,msgMapElement){
        msgMap=(CCDictionary*) msgMapElement->getObject();
        receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(receiverMap){
            handleList=(CCArray*)receiverMap->objectForKey(sender->m_uID);
            if(handleList){
                //移除所有receiver记录
                removeHandleList(handleList);
				//删除没有数据的记录
				receiverMap->removeObjectForKey(sender->m_uID);
			}

			//删除没有数据的记录
			if(receiverMap->count()==0){
				msgMap->removeObjectForKey(receiver->m_uID);
			}
        }
    }
}

void MessageManager::removeReceiver(Ref* receiver,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	CCAssert(handle!=NULL,"MessageManager:removeReceiver:handle can't be null!");

    CCDictElement* msgMapElement = NULL;
    CCDictionary* msgMap=NULL;
	CCDictionary* receiverMap=NULL;

    CCDICT_FOREACH(m_messages,msgMapElement){
        msgMap=(CCDictionary*) msgMapElement->getObject();
        receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(receiverMap){
             //移除所有receiver记录
             removeReceiverMap(receiverMap,handle);

			//删除没有数据的记录
			if(receiverMap->count()==0){
				msgMap->removeObjectForKey(receiver->m_uID);
			}
        }
    }
}

/**
 * 取消注册到接收者的处理对象的所有处理方法，该方法注册到发送者的某个消息。
 */
void MessageManager::removeReceiverAllHanldes(Ref* receiver,unsigned int type ,Ref* sender,Ref*  handleObject)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
    CCAssert(handleObject!=NULL,"MessageManager:removeReceiver:handleObject can't be null!");

    CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

    if(msgMap){
        CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(receiverMap){
            if(sender){
                //移除注册到sender的记录
                CCArray* handleList=(CCArray*)receiverMap->objectForKey(sender->m_uID);
                if(handleList){
                    removeHandleListForTarget(handleList, handleObject);
					//删除没有数据的记录
					if(handleList->count()==0){
						receiverMap->removeObjectForKey(sender->m_uID);
					}
                }
            }else{
                //移除所有receiver记录
                removeReceiverMapForTarget(receiverMap, handleObject);
            }

			//删除没有数据的记录
			if(receiverMap->count()==0){
				msgMap->removeObjectForKey(receiver->m_uID);
			}
        }
    }
}

/**
 * 取消接收者处理某个消息的所有方法。
 */
void MessageManager::removeReceiverAllHanldes(Ref* receiver,unsigned int type ,Ref*  handleObject)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
    CCAssert(handleObject!=NULL,"MessageManager:removeReceiver:handleObject can't be null!");

    CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

    if(msgMap){
        CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(receiverMap){
            //移除所有receiver记录
            removeReceiverMapForTarget(receiverMap,handleObject);
			//删除没有数据的记录
			if(receiverMap->count()==0){
				msgMap->removeObjectForKey(receiver->m_uID);
			}
        }
    }
}

/**
 * 取消接收者注册到发送者的任意消息的所有处理方法。
 */
void MessageManager::removeReceiverAllHanldes(Ref* receiver,Ref* sender,Ref*  handleObject)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	CCAssert(sender!=NULL,"MessageManager:removeReceiver:sender can't be null!");
	CCAssert(handleObject!=NULL,"MessageManager:removeReceiver:handleObject can't be null!");

    CCDictElement* msgMapElement = NULL;
    CCDictionary* msgMap=NULL;
	CCDictionary* receiverMap=NULL;
    CCArray* handleList=NULL;

    CCDICT_FOREACH(m_messages,msgMapElement){
        msgMap=(CCDictionary*) msgMapElement->getObject();
        receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(receiverMap){
            handleList=(CCArray*)receiverMap->objectForKey(sender->m_uID);
            if(handleList){
                //移除所有receiver记录
                removeHandleListForTarget(handleList,handleObject);

				//删除没有数据的记录
				if(handleList->count()==0){
					receiverMap->removeObjectForKey(sender->m_uID);
				}
            }

			//删除没有数据的记录
			if(receiverMap->count()==0){
				msgMap->removeObjectForKey(receiver->m_uID);
			}
        }
    }
}

/**
 * 取消接收者注册到任意发送者任意消息的所有处理方法。
 */
void MessageManager::removeReceiverAllHanldes(Ref* receiver,Ref*  handleObject)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	CCAssert(handleObject!=NULL,"MessageManager:removeReceiver:handleObject can't be null!");

    CCDictElement* msgMapElement = NULL;
    CCDictionary* msgMap=NULL;
	CCDictionary* receiverMap=NULL;

    CCDICT_FOREACH(m_messages,msgMapElement){
        msgMap=(CCDictionary*) msgMapElement->getObject();
        receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(receiverMap){
             //移除所有receiver记录
             removeReceiverMapForTarget(receiverMap,handleObject);
			 //删除没有数据的记录
			if(receiverMap->count()==0){
				msgMap->removeObjectForKey(receiver->m_uID);
			}
        }
    }
}

void MessageManager::removeReceiverMap(CCDictionary* receiverMap,SEL_MessageHandler handle,Ref* handleObject){
	CCAssert(receiverMap!=NULL,"MessageManager:removeReceiverMap:receiverMap can't be null!");

    CCDictElement* msgMapElement = NULL;
    CCArray* handleList=NULL;

    CCDICT_FOREACH(receiverMap,msgMapElement){
        //移除所有receiver记录
        handleList=(CCArray*)msgMapElement->getObject();
        removeHandleList(handleList,handle,handleObject);
		//删除没有数据的记录
		if(handleList->count()==0){
			receiverMap->removeObjectForKey(msgMapElement->getIntKey());
		}
    }
}

void MessageManager::removeReceiverMap(CCDictionary* receiverMap,SEL_MessageHandler handle){
	CCAssert(receiverMap!=NULL,"MessageManager:removeReceiverMap:receiverMap can't be null!");

    CCDictElement* msgMapElement = NULL;
    CCArray* handleList=NULL;

    CCDICT_FOREACH(receiverMap,msgMapElement){
        //移除所有receiver记录
        handleList=(CCArray*)msgMapElement->getObject();
        removeHandleList(handleList,handle);
		//删除没有数据的记录
		if(handleList->count()==0){
			receiverMap->removeObjectForKey(msgMapElement->getIntKey());
		}
    }
}

void MessageManager::removeReceiverMap(CCDictionary* receiverMap){
	CCAssert(receiverMap!=NULL,"MessageManager:removeReceiverMap:receiverMap can't be null!");
    receiverMap->removeAllObjects();
}

/**
 * 删除接收者的注册列表。
 */
void MessageManager::removeReceiverMapForTarget(CCDictionary* receiverMap,Ref* handleObject)
{
    CCAssert(receiverMap!=NULL,"MessageManager:removeReceiverMap:receiverMap can't be null!");

    CCDictElement* msgMapElement = NULL;
    CCArray* handleList=NULL;

    CCDICT_FOREACH(receiverMap,msgMapElement){
        //移除所有receiver记录
        handleList=(CCArray*)msgMapElement->getObject();
        removeHandleListForTarget(handleList,handleObject);
		//删除没有数据的记录
		if(handleList->count()==0){
			receiverMap->removeObjectForKey(msgMapElement->getIntKey());
		}
    }
}

void MessageManager::removeHandleList(CCArray* handleList,SEL_MessageHandler handle,Ref* handleObject){

    if (handleList && handleList->data->num > 0){
        int len=handleList->data->num;
        Ref** arr = handleList->data->arr;
        for(int i=0;i<len;){
		    MessageHandler* handler=(MessageHandler*)(*(arr+i));
		    if (handler->getTarget()==handleObject && handler->getHandle()==handle) {
			    handleList->removeObjectAtIndex(i);
                --len;
                //这里可以优化，handleList的handle和handleObject是唯一的，一但在for循环中找到，就可以直接break，因为后面不会存在同样的元素。
                //这里的handle和handleObject都不为空。通过调用的asset得以保证
                break;
		    }else{
                ++i;
            }
	    }
    }
}

void MessageManager::removeHandleList(CCArray* handleList,SEL_MessageHandler handle){
	if (handleList && handleList->data->num > 0){         
        int len=handleList->data->num;
        Ref** arr = handleList->data->arr;
        for(int i=0;i<len;){
		    MessageHandler* handler=(MessageHandler*)(*(arr+i));
		    if (handler->getHandle()==handle) {
			    handleList->removeObjectAtIndex(i);
                --len;
		    }else{
                ++i;
            }
	    }
    }
}

void MessageManager::removeHandleList(CCArray* handleList){
    handleList->removeAllObjects();
}

/**
 * 删除接收者的处理方法列表的处理方法为参数指定的函数。
 */
void MessageManager::removeHandleListForTarget(CCArray* handleList,Ref* handleObject)
{
    if (handleList && handleList->data->num > 0){         
        int len=handleList->data->num;
        Ref** arr = handleList->data->arr;
        for(int i=0;i<len;){
		    MessageHandler* handler=(MessageHandler*)(*(arr+i));
		    if (handler->getTarget()==handleObject) {
			    handleList->removeObjectAtIndex(i);
                --len;
		    }else{
                ++i;
            }
	    }
    }
}


void MessageManager::dispatchMessage(Message* message)
{
	CCAssert(message!=NULL,"MessageManager:dispatchMessage:message can't be null!");

	//CCAssert(message.type!=0,)
	//如果message的type不为0，则需要执行一个type为global的所有消息
	if (message->getType()!=GlobalMessageType) {
		//message for global
		CCDictionary* msgMap=(CCDictionary*)m_messages->objectForKey(GlobalMessageType);
		if (msgMap) {
            dispatchMessageMap(msgMap,message);
		}
	}
	
	//message for type
	CCDictionary* msgMap= (CCDictionary*)m_messages->objectForKey(message->getType());
	if (msgMap) {
		dispatchMessageMap(msgMap,message);
	}
}


//适应message中没有receiver的情况
void MessageManager::dispatchMessage(Message* message ,Ref*  receiver)
{
	CCAssert(message!=NULL,"MessageManager:dispatchMessage:message can't be null!");
	CCAssert(receiver!=NULL,"MessageManager:dispatchMessage:receiver can't be null!");
    message->setReceiver(receiver);
    dispatchMessage(message);
}


void MessageManager::dispatchMessage(unsigned int type ,Ref* sender ,Ref* receiver,Ref* data)
{
	Message* message=new Message();
	message->initWithType(type ,sender ,receiver ,data);
	dispatchMessage(message);
	message->release();
}

void MessageManager::dispatchMessage(unsigned int type ,Ref* sender ,Ref* receiver)
{
	Message* message=new Message();
	message->initWithType(type ,sender ,receiver);
	dispatchMessage(message);
	message->release();
}

void MessageManager::dispatchMessageMap(CCDictionary* msgMap,Message* message)
{
    CCAssert(msgMap!=NULL,"MessageManager:dispatchMessageMap:msgMap can't be null!");
    Ref* receiver=message->getReceiver();
    Ref* sender=message->getSender();
    if(receiver){
            CCDictionary* receiverMap=(CCDictionary *)msgMap->objectForKey(receiver->m_uID);
            if(receiverMap){
                CCArray* handleList=NULL;
                if(sender){
                    //执行注册到送送者为sender的消息的处理方法
                    handleList=(CCArray *)receiverMap->objectForKey(sender->m_uID);
                    if(handleList)
                        execHandleList(handleList,message);
//                        //执行注册到送送者为null的消息的处理方法
//
//                    }else{
//                        //执行注册到送送者为null的消息的处理方法
//                    }
                }

                //执行注册到送送者为null的消息的处理方法
                handleList=(CCArray *)receiverMap->objectForKey(kNullObjectId);
                if(handleList)
                    execHandleList(handleList,message);
            }
    }else{
            //发送到注册时的接收者为sender的所有接收者
            dispathMessageToAllReceiverWithSender(message,msgMap,sender);
    }
}

void MessageManager::dispathMessageToAllReceiverWithSender(Message* message,CCDictionary* msgMap,Ref* sender)
{
    CCAssert(msgMap!=NULL,"MessageManager:dispatchMessageMap:msgMap can't be null!");

    int senderKey=sender==NULL?kNullObjectId:sender->m_uID;

    CCDictElement* pElement = NULL;
    CCDictionary* receiverMap=NULL;
    CCArray* handleList=NULL;

    CCDICT_FOREACH(msgMap,pElement){
        receiverMap=(CCDictionary*)pElement->getObject();
        handleList=(CCArray*)receiverMap->objectForKey(senderKey);
        if(handleList)
            execHandleList(handleList,message);
    }
}

void MessageManager::execHandleList(CCArray* handleList ,Message* message)
{
	CCAssert(handleList!=NULL,"MessageManager:execHandleList:handleList can't be null!");
	Ref* pObject = NULL;
	//为了安全执行handler，需要一份handleList的复制。
	//在执行handle的时间，有可能会调用反注册函数。
	//如果反注册函数和当前handleList相关，则下面的执行会出错。
	CCArray* handleListCopy=new CCArray();
	handleListCopy->initWithArray(handleList);
    CCARRAY_FOREACH(handleListCopy,pObject){
        MessageHandler* handler=(MessageHandler*) pObject;
        //TODO 不执行删除的消息。在执行消息的时候，可能会调用到(直接或间接)反注册函数，把消息接收处理列表删除。
        //如果删除，这里的handler的retain就是1否则大于1.
        //所以这里可以加个判断，如果等于1，表示被删除，可以不执行。
        //给manager设置个开关，来决定执不执行删除了的消息。通常执行删除的消息也不会有什么逻辑问题，目前就不加这个开关。
		handler->execute(message);
    }
	handleListCopy->release();
}

//
//void MessageManager::execAllRegisterWithSenderMap(CCDictionary* senderMap,Message* message)
//{
//	CCAssert(senderMap!=NULL,"MessageManager:execAllRegisterWithSenderMap:senderMap can't be null!");
//	//send to all
//	CCDictElement* pElement = NULL;
//	CCDICT_FOREACH(senderMap,pElement){
//		execRegisterReceiverList((CCArray*)pElement->getObject(),message);
//	}
//}
//
//void MessageManager::execRegisterWithSenderMap(CCDictionary* senderMap,Message* message)
//{
//	Ref* receiver=message->getReceiver();
//	if (receiver) {
//		//message for receiver
//		CCArray* receiverList=(CCArray*)senderMap->objectForKey(receiver->m_uID);
//		if(receiverList) execRegisterReceiverList(receiverList,message);
//	}else {
//		//send to all receiver
//		execAllRegisterWithSenderMap(senderMap ,message);
//	}
//}
//
//void MessageManager::execRegisterWithSenderMap(CCDictionary* senderMap,Message* message,Ref*  receiver)
//{
//	CCAssert(senderMap!=NULL,"MessageManager:execRegisterWithSenderMap:senderMap can't be null!");
//	CCAssert(receiver!=NULL,"MessageManager:execRegisterWithSenderMap:receiver can't be null!");
//	CCArray* receiverList=(CCArray*)senderMap->objectForKey(receiver->m_uID);
//	if(receiverList) 
//		execRegisterReceiverList(receiverList,message);
//}

NS_CC_YHGE_END
