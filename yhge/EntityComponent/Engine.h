#ifndef YHGE_ENTITYCOMPONENT_ENGINE_H_
#define YHGE_ENTITYCOMPONENT_ENGINE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/Time/Scheduler.h>

NS_CC_YHGE_BEGIN

class Engine:public CCObject
{
public:
    
    Engine();
    ~Engine();
    
    static Engine* getInstance();
    static void destroyInstance();
    
    virtual bool init();
    
public:
    
    inline void setScheduler(yhge::Scheduler* scheduler)
    {
        CC_SAFE_RETAIN(scheduler);
        CC_SAFE_RELEASE(m_scheduler);
        m_scheduler = scheduler;
    }
    
    inline yhge::Scheduler* getScheduler()
    {
        return m_scheduler;
    }
    
protected:
    yhge::Scheduler* m_scheduler;
    
};


NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_ENGINE_H_
