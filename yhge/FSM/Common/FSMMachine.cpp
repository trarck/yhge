
#include "FSMMachine.h"

NS_CC_YHGE_BEGIN

FSMMachine::FSMMachine(void)
:_pCurrentState(NULL)
,_lastState(NULL)
,_pStates(NULL)
,_pOwner(NULL)

{
    CCLOG("FSMMachine create");
}


FSMMachine::~FSMMachine(void)
{
    CCLOG("FSMMachine destroy");
//	CC_SAFE_RELEASE_NULL(_pCurrentState);
//    CC_SAFE_RELEASE_NULL(_lastState);
	CC_SAFE_RELEASE_NULL(_pStates);
}

bool FSMMachine::init()
{
	_pStates=new CCDictionary();
	return true;
}

bool FSMMachine::init(Ref* owner)
{
    setOwner(owner);
    
    return init();
}

void FSMMachine::addState(FSMState* state ,const std::string& key)
{
	_pStates->setObject(state,key);
}

void FSMMachine::addState(FSMState* state ,unsigned int key)
{
	_pStates->setObject(state,key);
}

void FSMMachine::removeState(const std::string& key)
{
	_pStates->removeObjectForKey(key);
}

void FSMMachine::removeState(unsigned int key)
{
	_pStates->removeObjectForKey(key);
}

FSMState* FSMMachine::getState(const std::string& key)
{
	return static_cast<FSMState*>(_pStates->objectForKey(key));
}

FSMState* FSMMachine::getState(unsigned int key)
{
	return static_cast<FSMState*>(_pStates->objectForKey(key));
}

void FSMMachine::changeState(FSMState* state)
{
    if (_pCurrentState!=state) {
        
        setLastState(_pCurrentState);
        
        if(_pCurrentState) _pCurrentState->exit();
        
        setCurrentState(state);
        
        if(state) state->enter();
    }
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
    changeState(_lastState);
}

void FSMMachine::update()
{
	_pCurrentState->update();
}

void FSMMachine::update(float delta)
{
	_pCurrentState->update(delta);
}

void FSMMachine::handleMessage(Message* message)
{
	_pCurrentState->onMessage(message);
}

NS_CC_YHGE_END
