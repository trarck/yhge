#include "RendererComponent.h"
#include <yhge/message.h>
#include "ComponentMessageDefine.h"
#include <yhge/EntityComponent/Entity.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

RendererComponent::RendererComponent()
:Component("RendererComponent")
,m_renderer(NULL)
{

}

RendererComponent::~RendererComponent()
{
    CC_SAFE_RELEASE_NULL(m_renderer);
}

bool RendererComponent::registerMessages()
{
    if(Component::registerMessages()){

        MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(m_owner,MSG_RUN_ACTION, NULL ,message_selector(RendererComponent::onRunAction),this);
        messageManager->registerReceiver(m_owner,MSG_STOP_ACTION, NULL ,message_selector(RendererComponent::onStopAction),this);
        messageManager->registerReceiver(m_owner,MSG_STOP_ACTION_BY_TAG, NULL ,message_selector(RendererComponent::onStopActionByTag),this);
        messageManager->registerReceiver(m_owner,MSG_RUN_ANIMATE, NULL ,message_selector(RendererComponent::onRunAnimate),this);
        messageManager->registerReceiver(m_owner,MSG_STOP_ANIMATE, NULL ,message_selector(RendererComponent::onStopAnimate),this);
        messageManager->registerReceiver(m_owner,MSG_STOP_ANIMATE_BY_TAG, NULL ,message_selector(RendererComponent::onStopAnimateByTag),this);
        
        return true;
    }
    return false;
}

void RendererComponent::cleanupMessages()
{
    MessageManager* messageManager=this->getMessageManager();
    messageManager->removeReceiver(m_owner,MSG_RUN_ACTION);
    messageManager->removeReceiver(m_owner,MSG_STOP_ACTION);
    messageManager->removeReceiver(m_owner,MSG_STOP_ACTION_BY_TAG);
    messageManager->removeReceiver(m_owner,MSG_RUN_ANIMATE);
    messageManager->removeReceiver(m_owner,MSG_STOP_ANIMATE);
    messageManager->removeReceiver(m_owner,MSG_STOP_ANIMATE_BY_TAG);
    
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
    if (tagValue) {
        m_renderer->stopActionByTag(tagValue->getValue());
    }
}


//==============对animation的特殊支持==============//
/**
 * 执行action
 */
void RendererComponent::runAnimate(CCAction* animate)
{
    //default as action
    runAction(animate);
}

/**
 * 停止action
 */
void RendererComponent::stopAnimate(CCAction* animate)
{
    //default as action
    stopAction(animate);
}

/**
 * 停止action by tag
 */
void RendererComponent::stopAnimateByTag(int tag)
{
    //default as action
    stopActionByTag(tag);
}

/**
 * 响应执行action
 */
void RendererComponent::onRunAnimate(Message* message)
{
    //do nothing
    CCAction* action=static_cast<CCAction*>(message->getData());
    runAnimate(action);
}

/**
 * 响应停止action
 */
void RendererComponent::onStopAnimate(Message* message)
{
    //do nothing
    CCAction* action=static_cast<CCAction*>(message->getData());
    stopAnimate(action);
}

/**
 * 响应停止action by tag
 */
void RendererComponent::onStopAnimateByTag(Message* message)
{
    //do nothing
    CCInteger* tagValue=static_cast<CCInteger*>(message->getData());
    if (tagValue) {
        stopAnimateByTag(tagValue->getValue());
    }
}

NS_CC_YHGE_END

