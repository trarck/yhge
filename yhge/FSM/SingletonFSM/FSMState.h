//
//  State.h
//  GameFsm
//
//  Created by trarck trarck on 11-11-24.
//

#ifndef __CCFSMState_H__
#define __CCFSMState_H__

#include "cocos2d.h"
#include "CCIEntity.h"

NS_CC_BEGIN

class CCFSMState : public CCObject
{
public:
    CCFSMState();
    ~CCFSMState();
    static CCFSMState* create();
    
    virtual void enter(CCEntity* entity);
    virtual void exit(CCEntity* entity);
    virtual void update(CCEntity* entity);
    
    virtual void onMessage(Message* message,CCEntity* entity);
};

NS_CC_END

#endif //__CCFSMState_H__
