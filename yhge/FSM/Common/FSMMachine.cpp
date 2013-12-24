
#include "FSMMachine.h"

NS_CC_YHGE_BEGIN

FSMMachine::FSMMachine(void)
:m_pCurrentState(NULL)
,m_pStates(NULL)

{
    CCLOG("FSMMachine create");
}


FSMMachine::~FSMMachine(void)
{
    CCLOG("FSMMachine destroy");
	CC_SAFE_RELEASE(m_pCurrentState);
	CC_SAFE_RELEASE(m_pStates);
}

bool FSMMachine::init()
{
	m_pStates=new CCDictionary();
	return true;
}

void FSMMachine::addState(FSMState* state ,const std::string& name)
{
	m_pStates->setObject(state,name);
}

void FSMMachine::addState(FSMState* state ,unsigned int uId)
{
	m_pStates->setObject(state,uId);
}

void FSMMachine::removeStateWithName(const std::string& name)
{
	m_pStates->removeObjectForKey(name);
}

void FSMMachine::removeStateWithGuid(unsigned int uId)
{
	m_pStates->removeObjectForKey(uId);
}

FSMState* FSMMachine::stateForName(const std::string& name)
{
	return static_cast<FSMState*>(m_pStates->objectForKey(name));
}

FSMState* FSMMachine::stateForGuid(unsigned int uId)
{
	return static_cast<FSMState*>(m_pStates->objectForKey(uId));
}

void FSMMachine::changeState(FSMState* state)
{
	m_pCurrentState->exit();
	setCurrentState(state);
	m_pCurrentState->enter();
}

void FSMMachine::update()
{
	m_pCurrentState->update();
}

void FSMMachine::update(float delta)
{
	m_pCurrentState->update(delta);
}

void FSMMachine::handleMessage(Message* message)
{
	m_pCurrentState->onMessage(message);
}

NS_CC_YHGE_END
