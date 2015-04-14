#include "Engine.h"

NS_CC_YHGE_BEGIN

static Engine* s_engineInstance=NULL;

Engine::Engine()
:_scheduler(NULL)
,_updateManager(NULL)
{
   
    
}

Engine::~Engine()
{
    CC_SAFE_RELEASE_NULL(_scheduler);
    CC_SAFE_RELEASE_NULL(_updateManager);
}

Engine* Engine::getInstance()
{
    if (!s_engineInstance) {
        s_engineInstance=new Engine();
        s_engineInstance->init();
    }
    return s_engineInstance;
}


void Engine::destroyInstance()
{
    if (s_engineInstance) {
        s_engineInstance->release();
        s_engineInstance=NULL;
    }
}

bool Engine::init()
{
    _scheduler=new yhge::Scheduler();
    _scheduler->init();
    
    _updateManager=new UpdateManager();
    _updateManager->init();
    
    //add update manager to scheduler
    _scheduler->registerUpdate(_updateManager, schedule_selector(UpdateManager::update), 0);
    
    return true;
}

void Engine::setup()
{
    //add game scheduler to main loop
    if(_scheduler)
        CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(_scheduler,0,false);
}

void Engine::cleanup()
{
    if(_scheduler)
        CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(_scheduler);
}

void Engine::update(float delta)
{
//    _scheduler->update(delta);
    //do noting
}

NS_CC_YHGE_END
