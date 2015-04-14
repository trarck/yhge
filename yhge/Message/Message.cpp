//
//  Message.m
//  Message

//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "Message.h"

NS_CC_YHGE_BEGIN


Message::~Message(void)
{
    //CCLOG("Message destroy begin");
    CC_SAFE_RELEASE_NULL(_sender);
    CC_SAFE_RELEASE_NULL(_receiver);
//    CC_SAFE_RELEASE(_dData);
    CC_SAFE_RELEASE_NULL(_data);
	CC_SAFE_RELEASE_NULL(_extData);
    //CCLOG("Message destroy end");
}

NS_CC_YHGE_END