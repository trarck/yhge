#ifndef YHGE_FSM_COMMON_CCFSMMACHINE_H_
#define YHGE_FSM_COMMON_CCFSMMACHINE_H_

#include "cocos2d.h"
#include "YHGEMacros.h"
#include "Message/Message.h"
#include "FSMStateInterface.h"

NS_CC_YHGE_BEGIN

class FSMMachineInterface
{
public:
	virtual bool init();

    virtual void addState(FSMStateInterface* state ,const std::string& name)=0;
    virtual void addState(FSMStateInterface* state ,unsigned int guid)=0;

	virtual void removeStateWithName(const std::string& name)=0;
    virtual void removeStateWithGuid(unsigned int guid)=0;

    virtual FSMStateInterface* stateForName(const std::string& name)=0;
    virtual FSMStateInterface* stateForGuid(unsigned int guid)=0;
    
	virtual void changeState(FSMStateInterface* state)=0;

    virtual void update()=0;
    
	virtual void update(float delta)=0;

    virtual void handleMessage(Message* message)=0;
    
    
};

NS_CC_YHGE_END

#endif // YHGE_FSM_COMMON_CCFSMMACHINE_H_