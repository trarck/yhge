#include "ISOPositionComponent.h"
#include <yhge/message.h>
#include "ComponentMessageDefine.h"
#include "Entity.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

ISOPositionComponent::ISOPositionComponent()
:m_renderer(NULL)
{
    CCLOG("ISOPositionComponent create");
    m_name="ISOPositionComponent";
}

ISOPositionComponent::~ISOPositionComponent()
{
    CCLOG("ISOPositionComponent destroy");
    CC_SAFE_RELEASE_NULL(m_renderer);
}

bool ISOPositionComponent::init()
{
    CCLOG("ISOPositionComponent init");
    return true;
}

bool ISOPositionComponent::registerMessages()
{
    CCLOG("ISOPositionComponent::registerMessages");
    
    if(Component::registerMessages()){

        this->getMessageManager()->registerReceiver(m_owner,MSG_RUN_ACTION, NULL ,message_selector(ISOPositionComponent::onRunAction),this);
        this->getMessageManager()->registerReceiver(m_owner,MSG_STOP_ACTION, NULL ,message_selector(ISOPositionComponent::onStopAction),this);
        this->getMessageManager()->registerReceiver(m_owner,MSG_STOP_ACTION_BY_TAG, NULL ,message_selector(ISOPositionComponent::onStopActionByTag),this);
        
        return true;
    }
    return false;
}

void ISOPositionComponent::cleanupMessages()
{
	CCLOG("ISOPositionComponent::cleanupMessages");

    this->getMessageManager()->removeReceiver(m_owner,MSG_RUN_ACTION);
    this->getMessageManager()->removeReceiver(m_owner,MSG_STOP_ACTION);
    this->getMessageManager()->removeReceiver(m_owner,MSG_STOP_ACTION_BY_TAG);
    
    Component::cleanupMessages();
}

void ISOPositionComponent::setRenderer(CCNode* renderer)
{
    CC_SAFE_RETAIN(renderer);
    CC_SAFE_RELEASE(m_renderer);
    m_renderer = renderer;
}

CCNode* ISOPositionComponent::getRenderer()
{
    return m_renderer;
}

/**
 * 执行action
 */
void ISOPositionComponent::runAction(CCAction* action)
{
    //如果有标记,则消除源来的动画
    if (action->getTag()) {
        m_renderer->stopActionByTag(action->getTag());
    }
    m_renderer->runAction(action);
}

/**
 * 停止action
 */
void ISOPositionComponent::stopAction(CCAction* action)
{
    m_renderer->stopAction(action);
}

/**
 * 停止action by tag
 */
void ISOPositionComponent::stopActionByTag(int tag)
{
    m_renderer->stopActionByTag(tag);
}

/**
 * 响应执行action
 */
void ISOPositionComponent::onRunAction(Message* message)
{
    CCAction* action=static_cast<CCAction*>(message->getData());
    
    //如果有标记,则消除源来的动画
    if (action->getTag()) {
        m_renderer->stopActionByTag(action->getTag());
    }
    m_renderer->runAction(action);
}

/**
 * 响应停止action
 */
void ISOPositionComponent::onStopAction(Message* message)
{
    CCAction* action=static_cast<CCAction*>(message->getData());
    m_renderer->stopAction(action);
}

/**
 * 响应停止action by tag
 */
void ISOPositionComponent::onStopActionByTag(Message* message)
{
    CCInteger* tagValue=static_cast<CCInteger*>(message->getData());
    m_renderer->stopActionByTag(tagValue->getValue());
}

NS_CC_YHGE_END

