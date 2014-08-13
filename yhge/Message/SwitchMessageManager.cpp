//
//  MessageManager.m
//  Message
//
//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "SimpleMessageManager.h"

NS_CC_YHGE_BEGIN

static SwitchMessageManager* s_sharedSimpleMessageManagerInstance=NULL;

SwitchMessageManager* SwitchMessageManager::sharedSwitchMessageManager(void)
{
	if (!s_sharedSwitchMessageManagerInstance) {
		s_sharedSwitchMessageManagerInstance=new SwitchMessageManager();
		s_sharedSwitchMessageManagerInstance->init();
	}
	return s_sharedSwitchMessageManagerInstance;
}


SwitchMessageManager::SimpleMessageManager()
:m_enableExecDeleteHandle(true)
{

}

void SwitchMessageManager::execHandleList(CCArray* handleList ,Message* message)
{
	CCAssert(handleList!=NULL,"MessageManager:execHandleList:handleList can't be null!");
	CCObject* pObject = NULL;
	//为了安全执行handler，需要一份handleList的复制。
	//在执行handle的时间，有可能会调用反注册函数。
	//如果反注册函数和当前handleList相关，则下面的执行会出错。
	CCArray* handleListCopy=new CCArray();
	handleListCopy->initWithArray(handleList);
    CCARRAY_FOREACH(handleListCopy,pObject){
        MessageHandler* handler=(MessageHandler*) pObject;
        //不执行删除的消息。在执行消息的时候，可能会调用到(直接或间接)反注册函数，把消息接收处理列表删除。
        //如果删除，这里的handler的retain就是1否则大于1.
        //所以这里可以加个判断，如果等于1，表示被删除，可以不执行。
        //给manager设置个开关，来决定执不执行删除了的消息。通常执行删除的消息也不会有什么逻辑问题，目前就不加这个开关。
		if(m_enableExecDeleteHandle || handler->retainCount()>1)
			handler->execute(message);
    }
	handleListCopy->release();
}

NS_CC_YHGE_END
