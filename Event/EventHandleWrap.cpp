//
//  MessageHandler.m
//  Message
//
//  Created by trarck trarck on 11-12-27.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "EventHandleWrap.h"

NS_CC_YHGE_BEGIN

EventHandleWrap::~EventHandleWrap()
{
     CC_SAFE_RELEASE(m_pTarget);
    CC_SAFE_RELEASE(m_data);
}

NS_CC_YHGE_END