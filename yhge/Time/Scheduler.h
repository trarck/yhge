#ifndef YHGE_TIME_SCHEDULER_H_
#define YHGE_TIME_SCHEDULER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/DataStructure/LinkedList.h>

NS_CC_YHGE_BEGIN

class SchedulerTask
{
public:
    SchedulerTask()
    :_target(NULL)
    ,_handle(NULL)
    ,_priority(0)
    ,_markedForDeletion(false)
    {
        
    }
    
    SchedulerTask(Ref* target,SEL_SCHEDULE handle,int priority)
    :_target(target)
    ,_handle(handle)
    ,_priority(priority)
    ,_markedForDeletion(false)
    {
        CC_SAFE_RETAIN(target);
    }
    
    ~SchedulerTask()
    {
        CC_SAFE_RELEASE_NULL(_target);
    }
    
    void update(float delta)
    {
        (_target->*_handle)(delta);
    }
    
public:
    
    inline void setTarget( Ref* target)
    {
        CC_SAFE_RETAIN(target);
        CC_SAFE_RELEASE(_target);
        _target = target;
    }
    
    inline  Ref* getTarget()
    {
        return _target;
    }
    
    inline void setHandle( SEL_SCHEDULE handle)
    {
        _handle = handle;
    }
    
    inline  SEL_SCHEDULE getHandle()
    {
        return _handle;
    }
    
    inline void setPriority( int priority)
    {
        _priority = priority;
    }
    
    inline  int getPriority()
    {
        return _priority;
    }
    
    inline void setMarkedForDeletion(bool markedForDeletion)
    {
        _markedForDeletion = markedForDeletion;
    }
    
    inline bool isMarkedForDeletion()
    {
        return _markedForDeletion;
    }
    
protected:
    Ref* _target;
    SEL_SCHEDULE _handle;
    int _priority;
    bool _markedForDeletion;
};


/**
 * 任务调度器
 * 和游戏主循环同步调用，即每帧执行。
 * 这里只处理每帧都运行的，对于一定时间间隔的调用，则由其它类实现。
 * 为了性能，一个target只能注册一次，而不管它的方法是什么。如果遇到一个target的二个方法都需要注册，则把target拆成二个。
 */
class Scheduler : public Ref
{
public:

    typedef ds::LinkedList<SchedulerTask*> TaskList;
	typedef std::unordered_map<Ref*, int> PriorityMap;
    
    Scheduler();
    
    virtual ~Scheduler();
    
    virtual bool init(void);
    
    /**
     * 消除更新列表
     */
    void clear();
    
    /**
     * 每帧执行的tick
     */
    void update(float delta);
    
    /**
     * 添加一个更新器
     */
    void registerUpdate(Ref* target,SEL_SCHEDULE handle,int priority);
    
//    /**
//     * 移除一个更新器
//     */
//    void unregisterUpdate(Ref* target,int priority);
    
    /**
     * 移除一个更新器
     */
//    void unregisterUpdate(Ref* target,SEL_SCHEDULE handle,int priority);
    
    /**
     * 移除一个更新器
     */
//    void unregisterUpdate(Ref* target,SEL_SCHEDULE handle);

    /**
     * 移除一个更新器
     */
    void unregisterUpdate(Ref* target);
    
protected:
    
    void insertToList(TaskList& list,SchedulerTask* task);
    
//    void removeFromList(TaskList& list,Ref* target,SEL_SCHEDULE handle);
    
    void removeFromList(TaskList& list,Ref* target);
    
    void directRemoveFromList(TaskList& list,Ref* target);
    
    void markRemoveFromList(TaskList& list,Ref* target);
    
    void removeMarkedList(TaskList& list);
    
protected:
    
    TaskList _pUpdatesNegList;        // list of priority < 0
    TaskList _pUpdatesZeroList;          // list priority == 0
    TaskList _pUpdatesPosList;        // list priority > 0
    
    //标记只否则在某个更新内
    bool _updating;
    
	PriorityMap _registerMap;
    
};

NS_CC_YHGE_END

#endif // YHGE_TIME_SCHEDULER_H_
