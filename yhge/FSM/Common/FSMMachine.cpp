
#include "FSMMachine.h"

NS_CC_YHGE_BEGIN

FSMMachine::FSMMachine(void)
:m_pCurrentState(NULL)
,m_lastState(NULL)
,m_pStates(NULL)
,m_pOwner(NULL)

{
    CCLOG("FSMMachine create");
}


FSMMachine::~FSMMachine(void)
{
    CCLOG("FSMMachine destroy");
//	CC_SAFE_RELEASE_NULL(m_pCurrentState);
//    CC_SAFE_RELEASE_NULL(m_lastState);
	CC_SAFE_RELEASE_NULL(m_pStates);
}

bool FSMMachine::init()
{
	m_pStates=new CCDictionary();
	return true;
}

bool FSMMachine::init(CCObject* owner)
{
    setOwner(owner);
    
    return init();
}

void FSMMachine::addState(FSMState* state ,const std::string& key)
{
	m_pStates->setObject(state,key);
}

void FSMMachine::addState(FSMState* state ,unsigned int key)
{
	m_pStates->setObject(state,key);
}

void FSMMachine::removeState(const std::string& key)
{
	m_pStates->removeObjectForKey(key);
}

void FSMMachine::removeState(unsigned int key)
{
	m_pStates->removeObjectForKey(key);
}

FSMState* FSMMachine::getState(const std::string& key)
{
	return static_cast<FSMState*>(m_pStates->objectForKey(key));
}

FSMState* FSMMachine::getState(unsigned int key)
{
	return static_cast<FSMState*>(m_pStates->objectForKey(key));
}

void FSMMachine::changeState(FSMState* state)
{
	if(m_pCurrentState) m_pCurrentState->exit();
	
    setLastState(m_pCurrentState);
    setCurrentState(state);
    
	if(state) state->enter();

}

void FSMMachine::changeState(unsigned int key)
{
    changeState(getState(key));
}

void FSMMachine::changeState(const std::string& key)
{
    changeState(getState(key));
}

void FSMMachine::changeToLastState()
{
    changeState(m_lastState);
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
