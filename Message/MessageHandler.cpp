//
//  MessageHandler.m
//  Message
//
//  Created by trarck trarck on 11-12-27.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "MessageHandler.h"

NS_CC_YHGE_BEGIN

MessageHandler::~MessageHandler()
{
	//CCLOG("MessageHandler destroy begin ");
    CC_SAFE_RELEASE(m_pTarget);
    //CCLOG("MessageHandler destroy end ");
}

NS_CC_YHGE_END