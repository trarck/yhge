//
//  MessageManager.m
//  Message
//
//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "NormalMessageManager.h"

NS_CC_YHGE_BEGIN

static NormalMessageManager* s_sharedNormalMessageManagerInstance=NULL;

NormalMessageManager* NormalMessageManager::sharedNormalMessageManager(void)
{
	if (!s_sharedNormalMessageManagerInstance) {
		s_sharedNormalMessageManagerInstance=new NormalMessageManager();
		s_sharedNormalMessageManagerInstance->init();
	}
	return s_sharedNormalMessageManagerInstance;
}

void NormalMessageManager::dispatchMessage(Message* message)
{
	//NSAssert(message.type!=0,)
		//message for type
	CCDictionary* msgMap= (CCDictionary*)m_messages->objectForKey(message->getType());
	if (msgMap) {
		dispatchMessageMap(msgMap,message);
	}
}

NS_CC_YHGE_END
