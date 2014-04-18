//
//  State.h
//  做为 state的基类，具体功能由实现决定	
//  enter exit update是基础可以保障设计的灵活
//  update 是个定时事件，代替实体的update，进行处理，也可以改变状态。
//  
//  扩展:为输入创建方法，主要是处理状态转换。这与update方法不冲突。
//      监听事件，主要是处理状态转换。可以和上面扩展同时存在
//  content的相关:
//      参数传递，状态实例可由多个content使用，状态可用单例引用。不能保存变量。
//		委托,每个状态包含对content的引用，每个状态实例只可用于一个content。
//
//
//
//
//
//
//
//  比如当一个npc处于空闲状态时，
//  如果收到警戒输入(直接调用或事件),则进入戒备状态，调用enter方法。
//  定时执行update方法，搜索指定范围的怪物，如果找到则进入攻击状态，否则继续寻找。
//  如果收到警戒解除(直接调用或事件)，则会调用exit方法，进入空闲状态。
//  Created by trarck trarck on 11-11-23.
//

#ifndef YHGE_FSM_COMMON_CCFSMSTATE_H_
#define YHGE_FSM_COMMON_CCFSMSTATE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/Message/Message.h>

NS_CC_YHGE_BEGIN

class FSMMachine;

class FSMState:public CCObject 
{
public:
    virtual bool init();
    
    virtual bool init(FSMMachine* fsmMachine);
    
	virtual void enter();
    virtual void exit();
    virtual void update();
	virtual void update(float delta);
    virtual void onMessage(Message* message);
    
public:
    
    inline void setFSMMachine(FSMMachine* fSMMachine)
    {
        m_fSMMachine = fSMMachine;
    }
    
    inline FSMMachine* getFSMMachine()
    {
        return m_fSMMachine;
    }
    
protected:
    //如果state使用单例，则不要设置该值
    FSMMachine* m_fSMMachine;
};

NS_CC_YHGE_END

#endif // YHGE_FSM_COMMON_CCFSMSTATE_H_