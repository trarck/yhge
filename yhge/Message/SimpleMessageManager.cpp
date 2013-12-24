//
//  MessageManager.m
//  Message
//
//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "SimpleMessageManager.h"

NS_CC_YHGE_BEGIN

static SimpleMessageManager* s_sharedSimpleMessageManagerInstance=NULL;

SimpleMessageManager* SimpleMessageManager::sharedSimpleMessageManager(void)
{
	if (!s_sharedSimpleMessageManagerInstance) {
		s_sharedSimpleMessageManagerInstance=new SimpleMessageManager();
		s_sharedSimpleMessageManagerInstance->init();
	}
	return s_sharedSimpleMessageManagerInstance;
}


SimpleMessageManager::SimpleMessageManager()
{

}

SimpleMessageManager::~SimpleMessageManager()
{
	CC_SAFE_RELEASE(m_messages);
	CC_SAFE_RELEASE(m_globalObject);
}



void SimpleMessageManager::init()
{
	m_messages=new CCDictionary();
	m_globalObject=new CCObject();
}


//使receiver可以接收sender发送过来的叫type的消息，并用handle来处理
//关注的对象是receiver
//type,sender,receiver,handle唯一，同一接收者的同一个消息只有一个处理函数
bool SimpleMessageManager::registerReceiver(CCObject* receiver,SEL_MessageHandler handle ,unsigned int type ,CCObject* sender ,CCObject*  handleObject)
{
	CCAssert(receiver!=NULL,"SimpleMessageManager:registerReceiver:receiver can't be null");
	CCAssert(handle!=NULL,"SimpleMessageManager:registerReceiver:handle");
	CCAssert(handleObject!=NULL,"SimpleMessageManager:registerReceiver:handleObject");
	
	//type等于0，则所有消息都会发送
	//register for type
	CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
	if (!msgMap) {
		msgMap=new CCDictionary();
		m_messages->setObject(msgMap,type);
		msgMap->release();
	}
	//register for sender
	//sender 为空，则注册到全局对象上
	sender=sender==NULL?m_globalObject:sender;
	unsigned int senderKey=sender->m_uID;
	CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(senderKey);
	if (!senderMap) {
		senderMap=new CCDictionary();
	    msgMap->setObject(senderMap ,senderKey);
		senderMap->release();
	}
	//register for receiver
	//检查是否已经注册过
	MessageHandler* handler=(MessageHandler*)senderMap->objectForKey(receiver->m_uID);
//	CCAssert(!handler,"SimpleMessageManager:registerReceiver:Handle has register");
    bool isRegisted=false;
	if(!handler){
		//register for handler
		handler=new MessageHandler();
		handler->initWithTarget(handleObject,handle);
		senderMap->setObject(handler ,receiver->m_uID);
		handler->release();
	}else {
        isRegisted=true;
    }
    return !isRegisted;
}

bool SimpleMessageManager::registerReceiver(CCObject* receiver,SEL_MessageHandler handle,unsigned int type ,CCObject* sender)
{
	return registerReceiver(receiver ,handle,type ,sender ,receiver);
}


void SimpleMessageManager::removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle)
{
	removeReceiver(receiver,type,sender);
}

void SimpleMessageManager::removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender)
{
	CCAssert(receiver!=NULL,"SimpleMessageManager:removeReceiver:receiver can't be null!");
	CCAssert(sender!=NULL,"SimpleMessageManager:removeReceiver:receiver can't be null!");

	//message for type
	CCDictionary* msgMap=(CCDictionary*)m_messages->objectForKey(type);
	if (msgMap) {
		//message for sender
		CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
		if (senderMap) {
			//message for receiver
			senderMap->removeObjectForKey(receiver->m_uID);
		}
	}
}

void SimpleMessageManager::removeReceiver(CCObject* receiver,unsigned int type ,SEL_MessageHandler handle)
{
    removeReceiver(receiver,type);
}

void SimpleMessageManager::removeReceiver(CCObject* receiver,unsigned int type)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");

	CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
	if(msgMap){
        //删除消息type中接收者为ceceiver的注册信息
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(msgMap,pElement){
            CCDictionary *senderMap=(CCDictionary*)pElement->getObject();
            senderMap->removeObjectForKey(receiver->m_uID);
        }
    }
}

void SimpleMessageManager::removeReceiver(CCObject* receiver)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
    
    CCDictElement* msgMapElement = NULL;
    CCDictElement* senderMapElement = NULL;
    CCDictionary* msgMap=NULL;
	CCDictionary* senderMap=NULL;
    
    CCDICT_FOREACH(m_messages,msgMapElement){
        msgMap=(CCDictionary*) msgMapElement->getObject();
        
        CCDICT_FOREACH(msgMap,senderMapElement){
            senderMap=(CCDictionary*)senderMapElement->getObject();
            
            senderMap->removeObjectForKey(receiver->m_uID);
        }
    }
}


void SimpleMessageManager::removeReceiver(CCObject* receiver,CCObject* sender,SEL_MessageHandler handle)
{
    removeReceiver(receiver,sender);
}

void SimpleMessageManager::removeReceiver(CCObject* receiver,CCObject* sender)
{
    CCAssert(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
    CCAssert(sender!=NULL,"MessageManager:removeReceiver:sender can't be null!");

    //if(sender==NULL){
    //    removeReceiver(receiver);
    //}else {
        CCDictElement* msgMapElement = NULL;
        
        CCDICT_FOREACH(m_messages,msgMapElement){
            CCDictionary *msgMap=(CCDictionary*) msgMapElement->getObject();
            CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
            senderMap->removeObjectForKey(receiver->m_uID);
        }
    //}
}

void SimpleMessageManager::removeReceiver(CCObject* receiver,SEL_MessageHandler handle)
{
   removeReceiver(receiver);
}

//
void SimpleMessageManager::dispatchMessage(Message* message)
{
	CCObject* sender;
	//CCAssert(message.type!=0,)
	//如果message的type不为0，则需要执行一个type为global的所有消息
	if (message->getType()!=GlobalMessageType) {
		//message for global
		CCDictionary* msgMap=(CCDictionary*)m_messages->objectForKey(GlobalMessageType);
		if (msgMap) {
			//parse for sender
			//如果sender不为空，则还要触发一次全局消息。
			sender=message->getSender();
			if (sender) {
				//执行注册到sender的消息的处理方法
				CCDictionary* senderMap=(CCDictionary *)msgMap->objectForKey(sender->m_uID);
				//如果注册则执行
				if (senderMap)  execRegisterWithSenderMap(senderMap ,message);
				//执行注册到global的消息的处理方法
				CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
				//如果注册则执行
				if (globalMap)  execRegisterWithSenderMap(globalMap,message);
			}else {
				//执行注册到global的消息的处理方法
				CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
				//如果注册则执行
				if (globalMap)  execRegisterWithSenderMap(globalMap ,message);
			}
		}
	}
	//message for type
	CCDictionary* msgMap= (CCDictionary*)m_messages->objectForKey(message->getType());
	if (msgMap) {
		//parse for sender
		//如果sender不为空，则还要触发一次全局消息。
		sender=message->getSender();
		if (sender) {
			//执行注册到sender的消息的处理方法
			CCDictionary* senderMap=(CCDictionary *)msgMap->objectForKey(sender->m_uID);
			//如果注册则执行
			if (senderMap)  execRegisterWithSenderMap(senderMap,message);
			//执行注册到global的消息的处理方法
			CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
			//如果注册则执行
			if (globalMap)  execRegisterWithSenderMap(globalMap,message);
		}else {
			//执行注册到global的消息的处理方法
			CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
			//如果注册则执行
			if (globalMap)  execRegisterWithSenderMap(globalMap,message);
		}
	}
}

//适应message中没有receiver的情况
void SimpleMessageManager::dispatchMessage(Message* message ,CCObject*  receiver)
{
	//CCAssert(message.type!=0,)
	//如果message的type不为0，则需要执行一个type为global的所有消息
	if (message->getType()!=GlobalMessageType) {
		//message for global
		CCDictionary* msgMap=(CCDictionary*)m_messages->objectForKey(m_globalObject->m_uID);
		if (msgMap) {
			//parse for sender
			//如果sender不为空，则还要触发一次全局消息。
			CCObject* sender=message->getSender();
			if (sender) {
				//执行注册到sender的消息的处理方法
				CCDictionary* senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
				//如果注册则执行
				if (senderMap)  execRegisterWithSenderMap(senderMap,message,receiver);
				//执行注册到global的消息的处理方法
				CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
				//如果注册则执行
				if (globalMap)  execRegisterWithSenderMap(globalMap ,message ,receiver);
			}else {
				//执行注册到global的消息的处理方法
				CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
				//如果注册则执行
				if (globalMap)  execRegisterWithSenderMap(globalMap ,message ,receiver);
			}
		}
	}
	//message for type
	CCDictionary* msgMap=(CCDictionary*)m_messages->objectForKey(message->getType());
	if (msgMap) {
		//parse for sender
		//如果sender不为空，则还要触发一次全局消息。
		CCObject* sender=message->getSender();
		if (sender) {
			//执行注册到sender的消息的处理方法
			CCDictionary* senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
			//如果注册则执行
			if (senderMap)  execRegisterWithSenderMap(senderMap ,message ,receiver);
			//执行注册到global的消息的处理方法
			CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
			//如果注册则执行
			if (globalMap)  execRegisterWithSenderMap(globalMap ,message ,receiver);
		}else {
			//执行注册到global的消息的处理方法
			CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
			//如果注册则执行
			if (globalMap)  execRegisterWithSenderMap(globalMap ,message ,receiver);
		}
	}
}


void SimpleMessageManager::execAllRegisterWithSenderMap(CCDictionary* senderMap,Message* message)
{
	CCAssert(senderMap!=NULL,"SimpleMessageManager:execAllRegisterWithSenderMap:senderMap can't be null!");
	//send to all
	CCDictElement* pElement = NULL;
	CCDICT_FOREACH(senderMap,pElement){
		MessageHandler* handler=(MessageHandler*) pElement->getObject();
		handler->execute(message);
	}
}

void SimpleMessageManager::execRegisterWithSenderMap(CCDictionary* senderMap,Message* message)
{
	CCAssert(senderMap!=NULL,"SimpleMessageManager:execRegisterWithSenderMap:senderMap can't be null!");
	CCObject* receiver=message->getReceiver();
	if (receiver) {
		//message for receiver
		MessageHandler* handler=(MessageHandler*)senderMap->objectForKey(receiver->m_uID);
		if(handler) handler->execute(message);
	}else {
		//send to all receiver
		execAllRegisterWithSenderMap(senderMap ,message);
	}
}

void SimpleMessageManager::execRegisterWithSenderMap(CCDictionary* senderMap,Message* message,CCObject*  receiver)
{
	CCAssert(senderMap!=NULL,"SimpleMessageManager:execRegisterWithSenderMap:senderMap can't be null!");
	if (receiver) {
		//message for receiver
		MessageHandler* handler=(MessageHandler*)senderMap->objectForKey(receiver->m_uID);
		if(handler) handler->execute(message);
	}else {
		//send to all receiver
		execAllRegisterWithSenderMap(senderMap ,message);
	}
}

NS_CC_YHGE_END
