//
//  FSMachine.m
//  GameFsm
//
//  Created by trarck trarck on 11-11-24.
//

#include "CCFSMMachine.h"

NS_CC_BEGIN

CCFSMMachine::CCFSMMachine():
m_currentState(NULL),m_owner(NULL)
{
	CCLOG("CCFSMMachine create");
}

CCFSMMachine::~CCFSMMachine()
{
	CCLOG("CCFSMMachine destroy");
	CC_SAFE_RELEASE(m_currentState);
}

void CCFSMMachine::setOwner(CCIEntity* owner)
{
	m_owner=owner;
}

CCIEntity* CCFSMMachine::getOwner()
{
	return m_owner;
}

CCIFSMState* CCFSMMachine::getCurrentState()
{
	return m_currentState;
}

void CCFSMMachine::setCurrentState(CCIFSMState* state)
{
	CC_SAFE_RETAIN(state);
	CC_SAFE_RELEASE(m_currentState);
	m_currentState=state;
}


void CCFSMMachine::initWithOwner(CCIEntity* owner)
{
	m_owner=owner;
}
	


void CCFSMMachine::changeState(CCIFSMState* state)
{
	m_currentState->exit(m_owner);
	setCurrentState(state);
	m_currentState->enter(m_owner);
}

void CCFSMMachine::update()
{
	m_currentState->update(m_owner);
}

void CCFSMMachine::handleMessage(Message* message)
{
	m_currentState->onMessage(message ,m_owner);
}

NS_CC_END
