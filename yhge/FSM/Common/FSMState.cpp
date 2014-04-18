#include "FSMState.h"

NS_CC_YHGE_BEGIN

bool FSMState::init()
{
    return true;
}

bool FSMState::init(FSMMachine* fsmMachine)
{
    m_fSMMachine=fsmMachine;
    return true;
}

void FSMState::enter()
{
//	CCLOG("FSMState enter");
}

void FSMState::exit()
{
//	CCLOG("FSMState exit");
}

void FSMState::update()
{
//	CCLOG("FSMState update");
}

void FSMState::update(float delta)
{
//	CCLOG("FSMState update");
}

void FSMState::onMessage(Message* message)
{
//	CCLOG("FSMState onMessage");
}

NS_CC_YHGE_END