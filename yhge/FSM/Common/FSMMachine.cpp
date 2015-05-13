
#include "FSMMachine.h"

NS_CC_YHGE_BEGIN

FSMMachine::FSMMachine(void)
:_currentState(NULL)
,_lastState(NULL)
,_owner(NULL)

{
    CCLOG("FSMMachine create");
}


FSMMachine::~FSMMachine(void)
{
    CCLOG("FSMMachine destroy");
//	CC_SAFE_RELEASE_NULL(_pCurrentState);
//    CC_SAFE_RELEASE_NULL(_lastState);
}

bool FSMMachine::init()
{
	return true;
}

bool FSMMachine::init(Ref* owner)
{
    setOwner(owner);
    
    return init();
}

void FSMMachine::addState(FSMState* state ,unsigned int key)
{
	_iStates.insert(key, state);
}

void FSMMachine::removeState(unsigned int key)
{
	_iStates.erase(key);
}

FSMState* FSMMachine::getState(unsigned int key)
{
	return _iStates.at(key);
}

void FSMMachine::changeState(FSMState* state)
{
    if (_currentState!=state) {
        
        setLastState(_currentState);
        
        if(_currentState) _currentState->exit();
        
        setCurrentState(state);
        
        if(state) state->enter();
    }
}

void FSMMachine::changeState(unsigned int key)
{
    changeState(getState(key));
}

void FSMMachine::changeToLastState()
{
    changeState(_lastState);
}

void FSMMachine::update()
{
	_currentState->update();
}

void FSMMachine::update(float delta)
{
	_currentState->update(delta);
}

void FSMMachine::handleMessage(Message* message)
{
	_currentState->onMessage(message);
}


//void FSMMachine::addState(FSMState* state, const std::string& key)
//{
//	_sStates.insert(key, state);
//}
//
//void FSMMachine::removeState(const std::string& key)
//{
//	_sStates.erase(key);
//}
//
//FSMState* FSMMachine::getState(const std::string& key)
//{
//	return _sStates.at(key);
//}
//
//void FSMMachine::changeState(const std::string& key)
//{
//	changeState(getState(key));
//}

NS_CC_YHGE_END
