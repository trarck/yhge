//
//  FSMachine.h
//  GameFsm
//
//  Created by trarck trarck on 11-11-24.
//

#ifndef __CCFSMMachine_H__
#define __CCFSMMachine_H__

#include "cocos2d.h"
#include "CCFSMState.h"
#include "CCIEntity.h"

NS_CC_BEGIN

class CCFSMMachine:public CCObject
{
public:
	CCFSMMachine(void);
	~CCFSMMachine(void);
	void initWithOwner(CCEntity* owner);

	//ovveride
	virtual void setOwner(CCEntity* owner);
    virtual CCEntity* getOwner();
    virtual CCFSMState* getCurrentState();
    virtual void setCurrentState(CCFSMState* state);

    //由于State是单例，可以直接取得，无须另外保存

    virtual void update();
    virtual void handleMessage(Message* message);
    virtual void changeState(CCFSMState* state);//可有可无
private:
	CCFSMState* m_currentState;
	CCEntity* m_owner;
};

NS_CC_END

#endif //__CCFSMMachine_H__
