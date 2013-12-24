//
//
//
//

#include "DelayMessageManager.h"
#include "Message/MessageManager.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

static DelayMessageManager* s_sharedDelayMessageManager=NULL;

DelayMessageManager::DelayMessageManager()
:m_pMessages(NULL)
,m_pMessageManager(NULL)
{
    
}

DelayMessageManager::~DelayMessageManager()
{
    CCLOG("DelayMessageManager destroy");
    CC_SAFE_RELEASE(m_pMessages);
    CC_SAFE_RELEASE(m_pMessageManager);
}

DelayMessageManager* DelayMessageManager::sharedDelayMessageManager()
{
    if(!s_sharedDelayMessageManager){
        s_sharedDelayMessageManager=new DelayMessageManager();
        s_sharedDelayMessageManager->init();
        s_sharedDelayMessageManager->start();
    }
    return s_sharedDelayMessageManager;
}

bool DelayMessageManager::init()
{
    m_pMessages=new CCArray();
    return true;
}



void DelayMessageManager::start()
{
    CCDirector* pDirector=CCDirector::sharedDirector();
    CCScheduler* pScheduler=pDirector->getScheduler();
    pScheduler->scheduleUpdateForTarget(this, 0, false);
}

void DelayMessageManager::stop()
{
    CCDirector* pDirector=CCDirector::sharedDirector();
    CCScheduler* pScheduler=pDirector->getScheduler();
    pScheduler->unscheduleUpdateForTarget(this);
}

void DelayMessageManager::update(float delta)
{
    CCObject* pObj=NULL;
    DelayMessage* pDelayMessage=NULL;
    
    //检查和发送消息分开，防止发送消息的时候会对m_pMessages进行操作
    CCArray* willExecs=new CCArray();
    
    CCARRAY_FOREACH(m_pMessages, pObj){
        pDelayMessage=static_cast<DelayMessage*>(pObj);
        pDelayMessage->m_fDelay-=delta;
        if (pDelayMessage->m_fDelay<=0) {
            //dispatch message
            willExecs->addObject(pDelayMessage);
        }
    }
    
    //先执行再移除
    CCARRAY_FOREACH(willExecs, pObj){
        pDelayMessage=static_cast<DelayMessage*>(pObj);
        //dispatch message
        MessageManager::defaultManager()->dispatchMessage(pDelayMessage->getMessage());
    }

    
    m_pMessages->removeObjectsInArray(willExecs);
    
    willExecs->release();
}

void DelayMessageManager::dispatchMessage(Message* message,float delay)
{
    DelayMessage* pDelayMessage=new DelayMessage(delay,message);
    m_pMessages->addObject(pDelayMessage);
    pDelayMessage->release();
}

NS_CC_YHGE_END