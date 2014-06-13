#include "Engine.h"

NS_CC_YHGE_BEGIN

static Engine* s_engineInstance=NULL;

Engine::Engine()
:m_scheduler(NULL)
,m_updateManager(NULL)
{
   
    
}

Engine::~Engine()
{
    CC_SAFE_RELEASE_NULL(m_scheduler);
    CC_SAFE_RELEASE_NULL(m_updateManager);
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
    m_scheduler=new yhge::Scheduler();
    m_scheduler->init();
    
    m_updateManager=new UpdateManager();
    m_updateManager->init();
    
    //add update manager to scheduler
    m_scheduler->registerUpdate(m_updateManager, schedule_selector(UpdateManager::update), 0);
    
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
