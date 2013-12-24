//
//  MessageManager.m
//  Message
//
//  Created by trarck on 11-11-27.
//

#include "AsyncMessageManager.h"

NS_CC_YHGE_BEGIN

const int kNullObjectId=0;

static AsyncMessageManager* s_sharedMessageManagerInstance=NULL;

AsyncMessageManager::AsyncMessageManager()
{

}

AsyncMessageManager::~AsyncMessageManager()
{

}

AsyncMessageManager* AsyncMessageManager::sharedAsyncMessageManager(void)
{
	if (!s_sharedMessageManagerInstance) {
		s_sharedMessageManagerInstance=new AsyncMessageManager();
		s_sharedMessageManagerInstance->init();
	}
	return s_sharedMessageManagerInstance;
}

bool AsyncMessageManager::init()
{
	return true;
}

/**
 * 发送消息。
 */
void AsyncMessageManager::dispatchMessage(Message* message,float delay)
{

}

NS_CC_YHGE_END
