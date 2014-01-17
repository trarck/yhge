#include "RendererComponent.h"
#include <yhge/message.h>
#include "ComponentMessageDefine.h"
#include <yhge/EntityComponent/Entity.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

RendererComponent::RendererComponent()
:m_renderer(NULL)
{
    CCLOG("RendererComponent create");
    m_name="RendererComponent";
}

RendererComponent::~RendererComponent()
{
    CCLOG("RendererComponent destroy");
    CC_SAFE_RELEASE_NULL(m_renderer);
}

bool RendererComponent::init()
{
    CCLOG("RendererComponent init");
    return true;
}

bool RendererComponent::registerMessages()
{
    CCLOG("RendererComponent::registerMessages");
    
    if(Component::registerMessages()){

        this->getMessageManager()->registerReceiver(m_owner,MSG_RUN_ACTION, NULL ,message_selector(RendererComponent::onRunAction),this);
        this->getMessageManager()->registerReceiver(m_owner,MSG_STOP_ACTION, NULL ,message_selector(RendererComponent::onStopAction),this);
        this->getMessageManager()->registerReceiver(m_owner,MSG_STOP_ACTION_BY_TAG, NULL ,message_selector(RendererComponent::onStopActionByTag),this);
        
        return true;
    }
    return false;
}

void RendererComponent::cleanupMessages()
{
	CCLOG("RendererComponent::cleanupMessages");

    this->getMessageManager()->removeReceiver(m_owner,MSG_RUN_ACTION);
    this->getMessageManager()->removeReceiver(m_owner,MSG_STOP_ACTION);
    this->getMessageManager()->removeReceiver(m_owner,MSG_STOP_ACTION_BY_TAG);
    
    Component::cleanupMessages();
}

void RendererComponent::setRenderer(CCNode* renderer)
{
    CC_SAFE_RETAIN(renderer);
    CC_SAFE_RELEASE(m_renderer);
    m_renderer = renderer;
}

CCNode* RendererComponent::getRenderer()
{
    return m_renderer;
}

/**
 * 执行action
 */
void RendererComponent::runAction(CCAction* action)
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
void RendererComponent::stopAction(CCAction* action)
{
    m_renderer->stopAction(action);
}

/**
 * 停止action by tag
 */
void RendererComponent::stopActionByTag(int tag)
{
    m_renderer->stopActionByTag(tag);
}

/**
 * 响应执行action
 */
void RendererComponent::onRunAction(Message* message)
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
void RendererComponent::onStopAction(Message* message)
{
    CCAction* action=static_cast<CCAction*>(message->getData());
    m_renderer->stopAction(action);
}

/**
 * 响应停止action by tag
 */
void RendererComponent::onStopActionByTag(Message* message)
{
    CCInteger* tagValue=static_cast<CCInteger*>(message->getData());
    m_renderer->stopActionByTag(tagValue->getValue());
}

NS_CC_YHGE_END
