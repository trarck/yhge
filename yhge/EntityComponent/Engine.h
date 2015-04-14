#ifndef YHGE_ENTITYCOMPONENT_ENGINE_H_
#define YHGE_ENTITYCOMPONENT_ENGINE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/Time/Scheduler.h>
#include "Managers/UpdateManager.h"

NS_CC_YHGE_BEGIN

class Engine:public Ref
{
public:
    
    Engine();
    ~Engine();
    
    static Engine* getInstance();
    
    static void destroyInstance();
    
    virtual bool init();

    virtual void setup();

    virtual void cleanup();

    virtual void update(float delta);
    
public:

    
    inline yhge::Scheduler* getScheduler()
    {
        return _scheduler;
    }
    
    inline UpdateManager* getUpdateManager()
    {
        return _updateManager;
    }
    
//protected:
//    
//    inline void setScheduler(yhge::Scheduler* scheduler)
//    {
//        CC_SAFE_RETAIN(scheduler);
//        CC_SAFE_RELEASE(_scheduler);
//        _scheduler = scheduler;
//    }
    
protected:
    
    yhge::Scheduler* _scheduler;
    
    UpdateManager* _updateManager;
    
};


NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_ENGINE_H_
