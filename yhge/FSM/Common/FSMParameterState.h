//
//
//  具体在游戏里实现.由于CCEntity在不同游戏里实现不一样，所以要在游戏里实现此类。
//  状态对象不能有自己的变更，如果状态需要私有变量，可以放在实体中，实体通过参数传递。
//  状态可以在多个实体之间共用，状态可以使用单例模式。
//  状态也可以不共享，通常不这么用可以使用DelegateState。

#ifndef YHGE_FSM_COMMON_CCFSMSTATEDELEGATE_H_
#define YHGE_FSM_COMMON_CCFSMSTATEDELEGATE_H_

#include "cocos2d.h"
#include "FSMState.h"

NS_CC_YHGE_BEGIN

class FSMParameterState:public FSMState
{
public:
	virtual void enter(Ref* entity)=0;
	virtual void exit(Ref* entity)=0;
	virtual void update(Ref* entity)=0;
	virtual void update(float delta,Ref* entity)=0;
};

NS_CC_YHGE_END

#endif //YHGE_FSM_COMMON_CCFSMSTATEDELEGATE_H_