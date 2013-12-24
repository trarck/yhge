//
//  State.m
//  GameFsm
//
//  Created by trarck trarck on 11-11-24.
//

#include "CCIEntity.h"
#include "CCFSMState.h"

NS_CC_BEGIN

CCFSMState::CCFSMState()
{
    CCLOG("CCFSMState create");
}

CCFSMState::~CCFSMState()
{
    CCLOG("CCFSMState destroy");
}

CCFSMState* CCFSMState::create()
{
	CCFSMState* pState=new CCFSMState();
    pState->autorelease();
    
	return pState;
}

void CCFSMState::enter(CCIEntity* entity)
{
	CCLOG("CCFSMState enter");
}

void CCFSMState::exit(CCIEntity* entity)
{
	CCLOG("CCFSMState exit");
}

void CCFSMState::update(CCIEntity* entity)
{
	CCLOG("CCFSMState update");
}

void CCFSMState::onMessage(Message* ,CCIEntity* entity)
{
	CCLOG("CCFSMState onMessage");
}

NS_CC_END
