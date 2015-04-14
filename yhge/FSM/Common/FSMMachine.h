#ifndef YHGE_FSM_COMMON_CCFSMMACHINE_H_
#define YHGE_FSM_COMMON_CCFSMMACHINE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/Message/Message.h>
#include "FSMState.h"

NS_CC_YHGE_BEGIN

class FSMMachine:public Ref
{
public:
	FSMMachine(void);
	~FSMMachine(void);
	
	virtual bool init();
    
    virtual bool init(Ref* owner);

    virtual void addState(FSMState* state ,const std::string& key);
    virtual void addState(FSMState* state ,unsigned int key);
    
    virtual void removeState(const std::string& key);
    virtual void removeState(unsigned int key);
    
    virtual FSMState* getState(const std::string& key);
    virtual FSMState* getState(unsigned int key);

	virtual void changeState(FSMState* state);
    
    virtual void changeState(unsigned int key);
    
    virtual void changeState(const std::string& key);
    
    virtual void changeToLastState();

    virtual void update();
    
	virtual void update(float delta);

    virtual void handleMessage(Message* message);
 
public:

	inline void setCurrentState(FSMState* pCurrentState)
	{
//		CC_SAFE_RETAIN(pCurrentState);
//		CC_SAFE_RELEASE(_pCurrentState);
		_pCurrentState = pCurrentState;
	}

	inline FSMState* getCurrentState()
	{
		return _pCurrentState;
	}
    
    inline void setLastState(FSMState* lastState)
    {
//        CC_SAFE_RETAIN(lastState);
//        CC_SAFE_RELEASE(_lastState);
        _lastState = lastState;
    }
    
    inline FSMState* getLastState()
    {
        return _lastState;
    }

	inline void setOwner(Ref* pOwner)
	{
//		CC_SAFE_RETAIN(pOwner);
//		CC_SAFE_RELEASE(_pOwner);
		_pOwner = pOwner;
	}

	inline Ref* getOwner()
	{
		return _pOwner;
	}

	inline void setStates(CCDictionary* pStates)
	{
		CC_SAFE_RETAIN(pStates);
		CC_SAFE_RELEASE(_pStates);
		_pStates = pStates;
	}

	inline CCDictionary* getStates()
	{
		return _pStates;
	}

protected:

    //由于state通常都是在状态表里的，这里就弱引用
	FSMState* _pCurrentState;
    
    //由于state通常都是在状态表里的，这里就弱引用
    FSMState* _lastState;
    
    //弱引用
	Ref* _pOwner;
	CCDictionary* _pStates;

};

NS_CC_YHGE_END

#endif // YHGE_FSM_COMMON_CCFSMMACHINE_H_