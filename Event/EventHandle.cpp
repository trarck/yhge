//
//  MessageHandler.m
//  Message
//
//  Created by trarck trarck on 11-12-27.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "EventHandle.h"

NS_CC_YHGE_BEGIN

EventHandle::~EventHandle()
{
	CCLOG("EventHandle destroy begin ");
    CC_SAFE_RELEASE(m_pTarget);
    CCLOG("EventHandle destroy end ");
}

//void EventHandle::execute(Event *event)
//{
//	if(m_handle){
//		(m_pTarget->*m_handle)(event);
//	}
//}


NS_CC_YHGE_END