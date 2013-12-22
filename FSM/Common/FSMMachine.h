#ifndef YHGE_FSM_COMMON_CCFSMMACHINE_H_
#define YHGE_FSM_COMMON_CCFSMMACHINE_H_

#include "cocos2d.h"
#include "YHGEMacros.h"
#include "Message/Message.h"
#include "FSMState.h"

NS_CC_YHGE_BEGIN

class FSMMachine:public CCObject
{
public:
	FSMMachine(void);
	~FSMMachine(void);
	
	virtual bool init();

    virtual void addState(FSMState* state ,const std::string& name);
    virtual void addState(FSMState* state ,unsigned int uId);
    
    virtual void removeStateWithName(const std::string& name);
    virtual void removeStateWithGuid(unsigned int uId);
    
    virtual FSMState* stateForName(const std::string& name);
    virtual FSMState* stateForGuid(unsigned int uId);

	virtual void changeState(FSMState* state);

    virtual void update();
    
	virtual void update(float delta);

    virtual void handleMessage(Message* message);
 
public:

	inline void setCurrentState(FSMState* pCurrentState)
	{
		CC_SAFE_RETAIN(pCurrentState);
		CC_SAFE_RELEASE(m_pCurrentState);
		m_pCurrentState = pCurrentState;
	}

	inline FSMState* getCurrentState()
	{
		return m_pCurrentState;
	}

	inline void setOwner(CCObject* pOwner)
	{
		CC_SAFE_RETAIN(pOwner);
		CC_SAFE_RELEASE(m_pOwner);
		m_pOwner = pOwner;
	}

	inline CCObject* getOwner()
	{
		return m_pOwner;
	}

	inline void setStates(CCDictionary* pStates)
	{
		CC_SAFE_RETAIN(pStates);
		CC_SAFE_RELEASE(m_pStates);
		m_pStates = pStates;
	}

	inline CCDictionary* getStates()
	{
		return m_pStates;
	}

protected:

	FSMState* m_pCurrentState;
	CCObject* m_pOwner;
	CCDictionary* m_pStates;

};

NS_CC_YHGE_END

#endif // YHGE_FSM_COMMON_CCFSMMACHINE_H_