//
//  具体在游戏里实现。由于owner在不同游戏里实现不一样，所以要在游戏里实现此类
//
//  状态使用代理模式。状态可以保存自己的变量，每个实体都有一个状态对象。
//  状态不能被多个实体共享。
//

#ifndef YHGE_FSM_COMMON_CCFSMSTATEDELEGATE_H_
#define YHGE_FSM_COMMON_CCFSMSTATEDELEGATE_H_

#include "cocos2d.h"
#include "FSMState.h"

NS_CC_YHGE_BEGIN

class FSMDelegateState:public FSMState
{
public:
    //状态的拥有者，状态机或实体对象
    virtual void setOwner(Ref* owner)=0;
    virtual Ref* getOwner()=0;
}

NS_CC_YHGE_END

#endif //YHGE_FSM_COMMON_CCFSMSTATEDELEGATE_H_
