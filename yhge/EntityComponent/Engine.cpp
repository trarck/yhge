#include "Engine.h"

NS_CC_YHGE_BEGIN

static Engine* s_engineInstance=NULL;

Engine::Engine()
{
   
    
}

Engine::~Engine()
{
    
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
    yhge::Scheduler* scheduler=new yhge::Scheduler();
    scheduler->init();
    setScheduler(scheduler);
    scheduler->release();
    
    return true;
}

void Engine::setup()
{
    //add game scheduler to main loop
    if(m_scheduler)
        CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(m_scheduler,0,false);
}

void Engine::cleanup()
{
    if(m_scheduler)
        CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(m_scheduler);
}

//void Engine::update(float delta)
//{
//    m_scheduler->tick(delta);
//}

NS_CC_YHGE_END
