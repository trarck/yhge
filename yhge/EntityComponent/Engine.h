#ifndef YHGE_ENTITYCOMPONENT_ENGINE_H_
#define YHGE_ENTITYCOMPONENT_ENGINE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/Time/Scheduler.h>
#include "Managers/UpdateManager.h"

NS_CC_YHGE_BEGIN

class Engine:public CCObject
{
public:
    
    Engine();
    ~Engine();
    
    static Engine* getInstance();
    
    static void destroyInstance();
    
    virtual bool init();

    virtual void setup();

    virtual void cleanup();

    //virtual void update(float delta);
    
public:

    
    inline yhge::Scheduler* getScheduler()
    {
        return m_scheduler;
    }
    
    inline UpdateManager* getUpdateManager()
    {
        return m_updateManager;
    }
    
//protected:
//    
//    inline void setScheduler(yhge::Scheduler* scheduler)
//    {
//        CC_SAFE_RETAIN(scheduler);
//        CC_SAFE_RELEASE(m_scheduler);
//        m_scheduler = scheduler;
//    }
    
protected:
    
    yhge::Scheduler* m_scheduler;
    
    UpdateManager* m_updateManager;
    
};


NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_ENGINE_H_
