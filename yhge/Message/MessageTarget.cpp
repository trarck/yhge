#include "MessageManager.h"
#include "MessageTarget.h"

NS_CC_YHGE_BEGIN


void MessageTarget::registerMessage(unsigned int type,SEL_MessageHandler handle , Ref* pSender)
{
    MessageManager::defaultManager()->registerReceiver(this,type,pSender,handle);
}

void MessageTarget::unregisterMessage(unsigned int type ,SEL_MessageHandler handle ,Ref* pSender)
{
    MessageManager::defaultManager()->removeReceiver(this,type,pSender,handle);
}

void MessageTarget::sendMessage(unsigned int type ,Ref* pReceiver ,Ref* data)
{
    MessageManager::defaultManager()->dispatchMessage(type,this,pReceiver,data);
}

void MessageTarget::sendMessage(unsigned int type ,Ref* pReceiver)
{
    MessageManager::defaultManager()->dispatchMessage(type,this,pReceiver);
}

void MessageTarget::cleanupMessages()
{
    MessageManager::defaultManager()->removeReceiver(this);
}

NS_CC_YHGE_END
