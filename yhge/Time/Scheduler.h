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
    :m_target(NULL)
    ,m_handle(NULL)
    {
        
    }
    
    SchedulerTask(CCObject* target,SEL_SCHEDULE handle,int priority)
    :m_target(target)
    ,m_handle(handle)
    ,m_priority(priority)
    {
        CC_SAFE_RETAIN(target);
    }
    
    ~SchedulerTask()
    {
        CC_SAFE_RELEASE_NULL(m_target);
    }
    
    void tick(float delta)
    {
        (m_target->*m_handle)(delta);
    }
    
public:
    
    inline void setTarget( CCObject* target)
    {
        CC_SAFE_RETAIN(target);
        CC_SAFE_RELEASE(m_target);
        m_target = target;
    }
    
    inline  CCObject* getTarget()
    {
        return m_target;
    }
    
    inline void setHandle( SEL_SCHEDULE handle)
    {
        m_handle = handle;
    }
    
    inline  SEL_SCHEDULE getHandle()
    {
        return m_handle;
    }
    
    inline void setPriority( int priority)
    {
        m_priority = priority;
    }
    
    inline  int getPriority()
    {
        return m_priority;
    }
    
protected:
    CCObject* m_target;
    SEL_SCHEDULE m_handle;
    int m_priority;
};


/**
 * 任务调度器
 * 和游戏主循环同步调用，即每帧执行。
 * 这里只处理每帧都运行的，对于一定时间间隔的调用，则由其它类实现。
 * 为了性能，一个target只能注册一次，而不管它的方法是什么。如果遇到一个target的二个方法都需要注册，则把target拆成二个。
 */
class Scheduler : public CCObject
{
public:

    typedef ds::LinkedList<SchedulerTask*> TaskList;
    
    Scheduler();
    
    virtual ~Scheduler();
    
    virtual bool init(void);
    
    //用于添加到cocos的scheduler里的接口。
    virtual void update(float delta)
    {
        tick(delta);
    }
    
    /**
     * 消除更新列表
     */
    void clear();
    
    /**
     * 每帧执行的tick
     */
    void tick(float delta);
    
    /**
     * 添加一个更新器
     */
    void registerUpdate(CCObject* target,SEL_SCHEDULE handle,int priority);
    
//    /**
//     * 移除一个更新器
//     */
//    void unregisterUpdate(CCObject* target,int priority);
    
    /**
     * 移除一个更新器
     */
//    void unregisterUpdate(CCObject* target,SEL_SCHEDULE handle,int priority);
    
    /**
     * 移除一个更新器
     */
//    void unregisterUpdate(CCObject* target,SEL_SCHEDULE handle);

    /**
     * 移除一个更新器
     */
    void unregisterUpdate(CCObject* target);
    
protected:
    
    void insertToList(TaskList& list,SchedulerTask* task);
    
//    void removeFromList(TaskList& list,CCObject* target,SEL_SCHEDULE handle);
    
    void removeFromList(TaskList& list,CCObject* target);
    
protected:
    
    TaskList m_pUpdatesNegList;        // list of priority < 0
    TaskList m_pUpdatesZeroList;          // list priority == 0
    TaskList m_pUpdatesPosList;        // list priority > 0
    
    //标记只否则在某个更新内
    bool m_updating;
    
    std::map<int, int> m_registerMap;
    
};

NS_CC_YHGE_END

#endif // YHGE_TIME_SCHEDULER_H_
