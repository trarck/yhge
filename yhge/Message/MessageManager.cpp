//
//  MessageManager.m
//  Message
//
//  Created by trarck on 11-11-27.
//

#include "MessageManager.h"

NS_CC_YHGE_BEGIN

#if CC_ENABLE_SCRIPT_BINDING
	#define MESSAGE_GETOBJECT_ID(obj) obj->_ID
#else
	#define MESSAGE_GETOBJECT_ID(obj) (intptr_t)(obj)
#endif

const int kNullObjectId=0;

class MessageEmptyObject:public Ref
{
public:
	MessageEmptyObject()
	{
	}

	~MessageEmptyObject()
	{

	}

private:

};

static MessageManager* s_sharedMessageManagerInstance=NULL;

MessageManager::MessageManager()
:_globalObject(NULL)
,_nullObject(NULL)
{
	//CCLOG("MessageManager create");
}

MessageManager::~MessageManager()
{
	//CCLOG("MessageManager destroy begin");
	CC_SAFE_RELEASE_NULL(_globalObject);
		
	CC_SAFE_RELEASE_NULL(_nullObject);
	//CC_SAFE_RELEASE(_regiesterMap);
	//CCLOG("MessageManager destroy end");
}

MessageManager* MessageManager::getInstance(void)
{
	if (!s_sharedMessageManagerInstance) {
		s_sharedMessageManagerInstance=new MessageManager();
		s_sharedMessageManagerInstance->init();
	}
	return s_sharedMessageManagerInstance;
}

void MessageManager::destroyInstance()
{
	CC_SAFE_RELEASE_NULL(s_sharedMessageManagerInstance);
}

bool MessageManager::init()
{
	_globalObject=new MessageEmptyObject();
	_nullObject=new MessageEmptyObject();
	return true;
}

bool MessageManager::registerReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle ,Ref*  handleObject)
{
	CCASSERT(receiver!=NULL,"MessageManage:registerReceiver:receiver can't be null");
	CCASSERT(handle!=NULL,"MessageManage:registerReceiver:handle");
	CCASSERT(handleObject!=NULL,"MessageManage:registerReceiver:handleObject");

	//type等于0，则所有消息都会发送
	if(sender==NULL){
		sender=_nullObject;
	}


#ifdef MESSAGE_REGIEST_REPEAT
	MessageHandler *handler=new MessageHandler();
	handler->initWithTarget(handleObject,handle);
	_messages[type][receiver][sender].pushBack(handler);
	handler->release();
	
	return true;
	
#else
	//检查是否已经注册过
    bool isRegisted=false;
	MessageHandler* handler=NULL;

	for(HandleList::iterator iter=_messages[type][receiver][sender].begin();iter!=_messages[type][receiver][sender].end();++iter){
		handler=*iter;
		if (handler->getHandle()==handle && handler->getTarget()==handleObject) {
			CCASSERT(0,"Handle has register");
            isRegisted=true;
            break;
		}
	}

    if(!isRegisted){
       
        //register for handler
        MessageHandler *handler=new MessageHandler();
        handler->initWithTarget(handleObject,handle);
        _messages[type][receiver][sender].pushBack(handler);
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

	CCASSERT(receiver!=NULL,"MessageManage:registerReceiver:receiver can't be null");
	CCASSERT(handler!=NULL,"MessageManage:registerReceiver:handler");

	//type等于0，则所有消息都会发送
	if(sender==NULL){
		sender=_nullObject;
	}


#ifdef MESSAGE_REGIEST_REPEAT
	_messages[type][receiver][sender].pushBack(handler);
	
	return true;
#else
	//检查是否已经注册过
    bool isRegisted=false;
	MessageHandler* handlerItem=NULL;

	for(HandleList::iterator iter=_messages[type][receiver][sender].begin();iter!=_messages[type][receiver][sender].end();++iter){
		handlerItem=*iter;
		if (handler->getTarget()==handlerItem->getTarget() && handler->getHandle()==handlerItem->getHandle()) {
			CCASSERT(0,"Handle has register");
            isRegisted=true;
            break;
		}
	}

    if(!isRegisted){
        _messages[type][receiver][sender].pushBack(handler);
    }
	return !isRegisted;
#endif
}

/**
 * 检查是否已经注册某个消息。
 */
bool MessageManager::isRegisterReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle ,Ref*  handleObject)
{
	CCASSERT(receiver!=NULL,"MessageManage:registerReceiver:receiver can't be null");
	CCASSERT(handle!=NULL,"MessageManage:registerReceiver:handle");
	CCASSERT(handleObject!=NULL,"MessageManage:registerReceiver:handleObject");

	MessageMap::iterator msgIter=_messages.find(type);

	if(msgIter == _messages.end()){
		return false;
	}

	ReceiverMap::iterator receiverIter=_messages[type].find(receiver);

	if(receiverIter == _messages[type].end()){
		return false;
	}

	SenderMap::iterator senderIter=_messages[type][receiver].find(sender);

	if(senderIter == _messages[type][receiver].end()){
		return false;
	}

	if(senderIter->second.empty()){
		return false;
	}

	bool isRegisted=false;
	MessageHandler* handler=NULL;

	for(HandleList::iterator iter=senderIter->second.begin();iter!=senderIter->second.end();++iter){
		handler=*iter;
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
    CCASSERT(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	CCASSERT(handle!=NULL,"MessageManager:removeReceiver:handle can't be null!");
    CCASSERT(handleObject!=NULL,"MessageManager:removeReceiver:handleObject can't be null!");
    

	MessageMap::iterator msgIter=_messages.find(type);

    if(msgIter!=_messages.end()){
		ReceiverMap::iterator receiverIter=msgIter->second.find(receiver);

        if(receiverIter!=msgIter->second.end()){
            if(sender){
                //移除注册到sender的记录
				SenderMap::iterator senderIter=receiverIter->second.find(sender);

				if(senderIter!=receiverIter->second.end()){
                    removeHandleList(senderIter->second, handle,handleObject);
					//删除没有数据的记录
					if(senderIter->second.empty()){
						receiverIter->second.erase(senderIter);
					}
                }
            }else{
                //移除所有receiver记录
                removeReceiverMap(receiverIter->second, handle,handleObject);
            }

			//删除没有数据的记录
			if(receiverIter->second.empty()){
				msgIter->second.erase(receiverIter);
			}
        }
    }
}

/**
 * 取消接收者的处理方法，该方法注册到发送者的某个消息。
 */
void MessageManager::removeReceiver(Ref* receiver,unsigned int type ,Ref* sender,SEL_MessageHandler handle)
{
    CCASSERT(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	CCASSERT(handle!=NULL,"MessageManager:removeReceiver:handle can't be null!");

	MessageMap::iterator msgIter=_messages.find(type);

    if(msgIter!=_messages.end()){
		ReceiverMap::iterator receiverIter=msgIter->second.find(receiver);

        if(receiverIter!=msgIter->second.end()){
            if(sender){
                //移除注册到sender的记录
				SenderMap::iterator senderIter=receiverIter->second.find(sender);

				if(senderIter!=receiverIter->second.end()){
                    removeHandleList(senderIter->second, handle);
					//删除没有数据的记录
					if(senderIter->second.empty()){
						receiverIter->second.erase(senderIter);
					}
                }
            }else{
                //移除所有receiver记录
                removeReceiverMap(receiverIter->second, handle);
            }

			//删除没有数据的记录
			if(receiverIter->second.empty()){
				msgIter->second.erase(receiverIter);
			}
        }
    }
}

/**
 * 取消接收者注册到某个发送者的某个消息的所有处理方法。
 */
void MessageManager::removeReceiver(Ref* receiver,unsigned int type ,Ref* sender)
{
    CCASSERT(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	MessageMap::iterator msgIter=_messages.find(type);

    if(msgIter!=_messages.end()){
		ReceiverMap::iterator receiverIter=msgIter->second.find(receiver);

        if(receiverIter!=msgIter->second.end()){
            if(sender){
                //移除注册到sender的记录
				SenderMap::iterator senderIter=receiverIter->second.find(sender);

				if(senderIter!=receiverIter->second.end()){
                    removeHandleList(senderIter->second);
					//删除没有数据的记录
					receiverIter->second.erase(senderIter);
				}       
            }else{
                //移除所有receiver记录
                removeReceiverMap(receiverIter->second);
            }

			//删除没有数据的记录
			if(receiverIter->second.empty()){
				msgIter->second.erase(receiverIter);
			}
        }
    }
}

/**
 * 取消接收者注册到某个消息的所有处理方法。
 */
void MessageManager::removeReceiver(Ref* receiver,unsigned int type)
{
    CCASSERT(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");

	MessageMap::iterator msgIter=_messages.find(type);

    if(msgIter!=_messages.end()){
        ReceiverMap::iterator receiverIter=msgIter->second.find(receiver);

        if(receiverIter!=msgIter->second.end()){
            //移除所有receiver记录
            removeReceiverMap(receiverIter->second);
			//删除没有数据的记录
			msgIter->second.erase(receiverIter);
        }
    }
}

/**
 * 取消接收者的所有注册信息。
 */
void MessageManager::removeReceiver(Ref* receiver)
{
    CCASSERT(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
    

	for(MessageMap::iterator msgIter=_messages.begin();msgIter!=_messages.end();++msgIter){
		ReceiverMap::iterator receiverIter=msgIter->second.find(receiver);
		if(receiverIter!=msgIter->second.end()){
			//移除所有receiver记录
            removeReceiverMap(receiverIter->second);
			//删除没有数据的记录
			msgIter->second.erase(receiverIter);
		}
	}
}

void MessageManager::removeReceiver(Ref* receiver,unsigned int type ,SEL_MessageHandler handle)
{
    CCASSERT(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	CCASSERT(handle!=NULL,"MessageManager:removeReceiver:handle can't be null!");

    MessageMap::iterator msgIter=_messages.find(type);

    if(msgIter!=_messages.end()){
        ReceiverMap::iterator receiverIter=msgIter->second.find(receiver);
		if(receiverIter!=msgIter->second.end()){
            //移除所有receiver记录
            removeReceiverMap(receiverIter->second,handle);
			//删除没有数据的记录
			if(receiverIter->second.empty()){
				msgIter->second.erase(receiverIter);
			}
        }
    }
}

void MessageManager::removeReceiver(Ref* receiver,Ref* sender,SEL_MessageHandler handle)
{
    CCASSERT(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	CCASSERT(sender!=NULL,"MessageManager:removeReceiver:sender can't be null!");
	CCASSERT(handle!=NULL,"MessageManager:removeReceiver:handle can't be null!");

	for(MessageMap::iterator msgIter=_messages.begin();msgIter!=_messages.end();++msgIter){
		ReceiverMap::iterator receiverIter=msgIter->second.find(receiver);
		if(receiverIter!=msgIter->second.end()){
			SenderMap::iterator senderIter=receiverIter->second.find(sender);
			if(senderIter!=receiverIter->second.end()){
				//移除所有receiver记录
                removeHandleList(senderIter->second,handle);
				//删除没有数据的记录
				if(senderIter->second.empty()){
					receiverIter->second.erase(senderIter);
				}
			}

			//删除没有数据的记录
			if(receiverIter->second.empty()){
				msgIter->second.erase(receiverIter);
			}

		}
	}
}

void MessageManager::removeReceiver(Ref* receiver,Ref* sender)
{
    CCASSERT(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
    CCASSERT(sender!=NULL,"MessageManager:removeReceiver:sender can't be null!");

	for(MessageMap::iterator msgIter=_messages.begin();msgIter!=_messages.end();++msgIter){
		ReceiverMap::iterator receiverIter=msgIter->second.find(receiver);
		if(receiverIter!=msgIter->second.end()){
			SenderMap::iterator senderIter=receiverIter->second.find(sender);
			if(senderIter!=receiverIter->second.end()){
				//移除所有receiver记录
                removeHandleList(senderIter->second);
				//删除没有数据的记录
				if(senderIter->second.empty()){
					receiverIter->second.erase(senderIter);
				}
			}

			//删除没有数据的记录
			if(receiverIter->second.empty()){
				msgIter->second.erase(receiverIter);
			}

		}
	}
}

void MessageManager::removeReceiver(Ref* receiver,SEL_MessageHandler handle)
{
    CCASSERT(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	CCASSERT(handle!=NULL,"MessageManager:removeReceiver:handle can't be null!");

	for(MessageMap::iterator msgIter=_messages.begin();msgIter!=_messages.end();++msgIter){
		ReceiverMap::iterator receiverIter=msgIter->second.find(receiver);
		if(receiverIter!=msgIter->second.end()){
			//移除所有receiver记录
			removeReceiverMap(receiverIter->second,handle);

			//删除没有数据的记录
			if(receiverIter->second.empty()){
				msgIter->second.erase(receiverIter);
			}

		}
	}
}

/**
 * 取消注册到接收者的处理对象的所有处理方法，该方法注册到发送者的某个消息。
 */
void MessageManager::removeReceiverAllHanldes(Ref* receiver,unsigned int type ,Ref* sender,Ref*  handleObject)
{
    CCASSERT(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
    CCASSERT(handleObject!=NULL,"MessageManager:removeReceiver:handleObject can't be null!");

    MessageMap::iterator msgIter=_messages.find(type);

    if(msgIter!=_messages.end()){
        ReceiverMap::iterator receiverIter=msgIter->second.find(receiver);
		if(receiverIter!=msgIter->second.end()){
            if(sender){
                //移除注册到sender的记录
				SenderMap::iterator senderIter=receiverIter->second.find(sender);

				if(senderIter!=receiverIter->second.end()){
                    removeHandleListForTarget(senderIter->second, handleObject);
					//删除没有数据的记录
					if(senderIter->second.empty()){
						receiverIter->second.erase(senderIter);
					}
				}       
            }else{
                //移除所有receiver记录
                removeReceiverMapForTarget(receiverIter->second, handleObject);
            }

			//删除没有数据的记录
			if(receiverIter->second.empty()){
				msgIter->second.erase(receiverIter);
			}
        }
    }
}

/**
 * 取消接收者处理某个消息的所有方法。
 */
void MessageManager::removeReceiverAllHanldes(Ref* receiver,unsigned int type ,Ref*  handleObject)
{
    CCASSERT(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
    CCASSERT(handleObject!=NULL,"MessageManager:removeReceiver:handleObject can't be null!");

     MessageMap::iterator msgIter=_messages.find(type);

    if(msgIter!=_messages.end()){
        ReceiverMap::iterator receiverIter=msgIter->second.find(receiver);
		if(receiverIter!=msgIter->second.end()){
            //移除所有receiver记录
            removeReceiverMapForTarget(receiverIter->second,handleObject);
			//删除没有数据的记录
			if(receiverIter->second.empty()){
				msgIter->second.erase(receiverIter);
			}
        }
    }
}

/**
 * 取消接收者注册到发送者的任意消息的所有处理方法。
 */
void MessageManager::removeReceiverAllHanldes(Ref* receiver,Ref* sender,Ref*  handleObject)
{
    CCASSERT(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	CCASSERT(sender!=NULL,"MessageManager:removeReceiver:sender can't be null!");
	CCASSERT(handleObject!=NULL,"MessageManager:removeReceiver:handleObject can't be null!");

	for(MessageMap::iterator msgIter=_messages.begin();msgIter!=_messages.end();++msgIter){
		ReceiverMap::iterator receiverIter=msgIter->second.find(receiver);
		if(receiverIter!=msgIter->second.end()){
			SenderMap::iterator senderIter=receiverIter->second.find(sender);

			if(senderIter!=receiverIter->second.end()){
                //移除所有receiver记录
                removeHandleListForTarget(senderIter->second,handleObject);

				//删除没有数据的记录
				if(senderIter->second.empty()){
					receiverIter->second.erase(senderIter);
				}
            }

			//删除没有数据的记录
			if(receiverIter->second.empty()){
				msgIter->second.erase(receiverIter);
			}

		}
	}
}

/**
 * 取消接收者注册到任意发送者任意消息的所有处理方法。
 */
void MessageManager::removeReceiverAllHanldes(Ref* receiver,Ref*  handleObject)
{
    CCASSERT(receiver!=NULL,"MessageManager:removeReceiver:receiver can't be null!");
	CCASSERT(handleObject!=NULL,"MessageManager:removeReceiver:handleObject can't be null!");

	for(MessageMap::iterator msgIter=_messages.begin();msgIter!=_messages.end();++msgIter){
		ReceiverMap::iterator receiverIter=msgIter->second.find(receiver);
		if(receiverIter!=msgIter->second.end()){
			//移除所有receiver记录
            removeReceiverMapForTarget(receiverIter->second,handleObject);

			//删除没有数据的记录
			if(receiverIter->second.empty()){
				msgIter->second.erase(receiverIter);
			}

		}
	}
}

void MessageManager::removeReceiverMap(SenderMap& senderMap,SEL_MessageHandler handle,Ref* handleObject){

	for(SenderMap::iterator senderIter=senderMap.begin();senderIter!=senderMap.end();++senderIter){
		//移除所有receiver记录
        removeHandleList(senderIter->second,handle,handleObject);
		//删除没有数据的记录
		if(senderIter->second.empty()){
			senderMap.erase(senderIter);
		}
	}
}

void MessageManager::removeReceiverMap(SenderMap& senderMap,SEL_MessageHandler handle){

	for(SenderMap::iterator senderIter=senderMap.begin();senderIter!=senderMap.end();++senderIter){
		//移除所有receiver记录
        removeHandleList(senderIter->second,handle);
		//删除没有数据的记录
		if(senderIter->second.empty()){
			senderMap.erase(senderIter);
		}
	}
}

void MessageManager::removeReceiverMap(SenderMap& senderMap){
	senderMap.clear();
}

/**
 * 删除接收者的注册列表。
 */
void MessageManager::removeReceiverMapForTarget(SenderMap& senderMap,Ref* handleObject)
{

	for(SenderMap::iterator senderIter=senderMap.begin();senderIter!=senderMap.end();++senderIter){
		//移除所有receiver记录
        removeHandleListForTarget(senderIter->second,handleObject);
		//删除没有数据的记录
		if(senderIter->second.empty()){
			senderMap.erase(senderIter);
		}
	}
}

void MessageManager::removeHandleList(HandleList& handleList,SEL_MessageHandler handle,Ref* handleObject){

	if(!handleList.empty()){
		for(HandleList::iterator iter=handleList.begin();iter!=handleList.end();){
			MessageHandler* handler=*iter;
		    if (handler->getTarget()==handleObject && handler->getHandle()==handle) {
				 //这里可以优化，handleList的handle和handleObject是唯一的，一但在for循环中找到，就可以直接break，因为后面不会存在同样的元素。
                //这里的handle和handleObject都不为空。通过调用的asset得以保证
				iter=handleList.erase(iter);
			}else{
				++iter;
			}
		}
	}
}

void MessageManager::removeHandleList(HandleList& handleList,SEL_MessageHandler handle){
	if(!handleList.empty()){
		for(HandleList::iterator iter=handleList.begin();iter!=handleList.end();){
			MessageHandler* handler=*iter;
		    if (handler->getHandle()==handle) {
				iter=handleList.erase(iter);
			}else{
				++iter;
			}
		}
	}

}

void MessageManager::removeHandleList(HandleList& handleList){
    handleList.clear();
}

/**
 * 删除接收者的处理方法列表的处理方法为参数指定的函数。
 */
void MessageManager::removeHandleListForTarget(HandleList& handleList,Ref* handleObject)
{
	if(!handleList.empty()){
		for(HandleList::iterator iter=handleList.begin();iter!=handleList.end();){
			MessageHandler* handler=*iter;
		    if (handler->getTarget()==handleObject) {
				iter=handleList.erase(iter);
			}else{
				++iter;
			}
		}
	}
}


void MessageManager::dispatchMessage(Message* message)
{
	CCASSERT(message!=NULL,"MessageManager:dispatchMessage:message can't be null!");

	//CCASSERT(message.type!=0,)
	//如果message的type不为0，则需要执行一个type为global的所有消息
	if (message->getType()!=GlobalMessageType) {
		//message for global
		MessageMap::iterator globalMsgIter=_messages.find(GlobalMessageType);
		
		if (globalMsgIter!=_messages.end()) {
            dispatchMessageMap(globalMsgIter->second,message);
		}
	}
	
	//message for type
	MessageMap::iterator msgIter=_messages.find(message->getType());
	if (msgIter!=_messages.end()) {
		dispatchMessageMap(msgIter->second,message);
	}
}


//适应message中没有receiver的情况
void MessageManager::dispatchMessage(Message* message ,Ref*  receiver)
{
	CCASSERT(message!=NULL,"MessageManager:dispatchMessage:message can't be null!");
	CCASSERT(receiver!=NULL,"MessageManager:dispatchMessage:receiver can't be null!");
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

void MessageManager::dispatchMessageMap(ReceiverMap& receiverMap,Message* message)
{
    Ref* receiver=message->getReceiver();
    Ref* sender=message->getSender();

    if(receiver){
		ReceiverMap::iterator receiverIter=receiverMap.find(receiver);

        if(receiverIter!=receiverMap.end()){
            CCArray* handleList=NULL;
            if(sender){
                //执行注册到送送者为sender的消息的处理方法
				SenderMap::iterator senderIter=receiverIter->second.find(sender);
                if(senderIter!=receiverIter->second.end())
                    execHandleList(senderIter->second,message);
            }

            //执行注册到送送者为null的消息的处理方法
			SenderMap::iterator senderIter=receiverIter->second.find(_nullObject);
            if(senderIter!=receiverIter->second.end())
                execHandleList(senderIter->second,message);
        }
    }else{
        //发送到注册时的接收者为sender的所有接收者
        dispathMessageToAllReceiverWithSender(message,receiverMap,sender);
    }
}

void MessageManager::dispathMessageToAllReceiverWithSender(Message* message,ReceiverMap& receiverMap,Ref* sender)
{
	if(sender==NULL){
		sender=_nullObject;
	}

	for(ReceiverMap::iterator iter=receiverMap.begin();iter!=receiverMap.end();++iter){
		SenderMap::iterator senderIter=iter->second.find(sender);

         if(senderIter!=iter->second.end())
			 execHandleList(senderIter->second,message);

	}

}

void MessageManager::execHandleList(HandleList& handleList ,Message* message)
{

	//为了安全执行handler，需要一份handleList的复制。
	//在执行handle的时间，有可能会调用反注册函数。
	//如果反注册函数和当前handleList相关，则下面的执行会出错。
	HandleList copyList=handleList;

	for(HandleList::iterator iter=copyList.begin();iter!=copyList.end();++iter){
		MessageHandler* handler=*iter;
		//TODO 不执行删除的消息。在执行消息的时候，可能会调用到(直接或间接)反注册函数，把消息接收处理列表删除。
        //如果删除，这里的handler的retain就是1否则大于1.
        //所以这里可以加个判断，如果等于1，表示被删除，可以不执行。
        //给manager设置个开关，来决定执不执行删除了的消息。通常执行删除的消息也不会有什么逻辑问题，目前就不加这个开关。
		handler->execute(message);
	}

	copyList.clear();
}

NS_CC_YHGE_END
