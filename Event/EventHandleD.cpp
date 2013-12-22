//
//  MessageHandler.m
//  Message
//
//  Created by trarck trarck on 11-12-27.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "EventHandleD.h"

NS_CC_YHGE_BEGIN

EventHandleD::~EventHandleD()
{
	CCLOG("EventHandle destroy begin ");
    CC_SAFE_RELEASE(m_data);
    CCLOG("EventHandle destroy end ");
}

void EventHandleD::execute(Event *event)
{
	if(m_handle){
		(m_pTarget->*m_handleD)(event,m_data);
	}
}


NS_CC_YHGE_END