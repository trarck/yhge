#ifndef __FSMMachine_H__
#define __FSMMachine_H__

#include "FSMMachine.h"

NS_CC_BEGIN

class FSMMachine:public CCObject
{
public:
	FSMMachine(void);
	~FSMMachine(void);
	
	// virtual CCFSMState* getCurrentState();
	//     virtual void setCurrentState(CCFSMState* state);
    
    virtual void addState(CCFSMState* state ,CCObject* key);
    virtual void addState(CCFSMState* state ,const std::string& name);
    virtual void addState(CCFSMState* state ,unsigned int guid);
    
    virtual void removeStateWithKey(CCObject* key);
    virtual void removeStateWithName(const std::string& name);
    virtual void removeStateWithGuid(unsigned int guid);
    
    virtual CCFSMState* stateForKey(CCObject* key);
    virtual CCFSMState* stateForName(const std::string& name);
    virtual CCFSMState* stateForGuid(unsigned int guid);
    
    virtual void update();
    
    virtual void handleMessage(Message* message);
    
    virtual void changeState(CCFSMState* state);
};

NS_CC_END

#endif //__FSMMachine_H__