#include "FSMState.h"

NS_CC_YHGE_BEGIN

void FSMState::enter()
{
	CCLOG("FSMState enter");
}

void FSMState::exit()
{
	CCLOG("FSMState exit");
}

void FSMState::update()
{
	CCLOG("FSMState update");
}

void FSMState::onMessage(Message* message)
{
	CCLOG("FSMState onMessage");
}

NS_CC_YHGE_END