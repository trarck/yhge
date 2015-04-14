#include "RendererComponent.h"
#include <yhge/message.h>
#include "ComponentMessageDefine.h"
#include <yhge/EntityComponent/Entity.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

RendererComponent::RendererComponent()
:Component("RendererComponent")
,_renderer(NULL)
{

}

RendererComponent::~RendererComponent()
{
    CC_SAFE_RELEASE_NULL(_renderer);
}

bool RendererComponent::init()
{
    if (Component::init()) {
        
        _renderer=new CCNode();
        
        return true;
    }
    
    return false;
}

void RendererComponent::cleanup(void)
{
    if (_renderer) {
        _renderer->stopAllActions();
    }
    Component::cleanup();
}

bool RendererComponent::registerMessages()
{
    if(Component::registerMessages()){

        MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(_owner,MSG_RUN_ACTION, NULL ,MESSAGE_SELECTOR(RendererComponent::onRunAction),this);
        messageManager->registerReceiver(_owner,MSG_STOP_ACTION, NULL ,MESSAGE_SELECTOR(RendererComponent::onStopAction),this);
        messageManager->registerReceiver(_owner,MSG_STOP_ACTION_BY_TAG, NULL ,MESSAGE_SELECTOR(RendererComponent::onStopActionByTag),this);
//        messageManager->registerReceiver(_owner,MSG_RUN_ANIMATE, NULL ,MESSAGE_SELECTOR(RendererComponent::onRunAnimate),this);
//        messageManager->registerReceiver(_owner,MSG_STOP_ANIMATE, NULL ,MESSAGE_SELECTOR(RendererComponent::onStopAnimate),this);
//        messageManager->registerReceiver(_owner,MSG_STOP_ANIMATE_BY_TAG, NULL ,MESSAGE_SELECTOR(RendererComponent::onStopAnimateByTag),this);
        
        return true;
    }
    return false;
}

void RendererComponent::cleanupMessages()
{
    MessageManager* messageManager=this->getMessageManager();
    messageManager->removeReceiver(_owner,MSG_RUN_ACTION);
    messageManager->removeReceiver(_owner,MSG_STOP_ACTION);
    messageManager->removeReceiver(_owner,MSG_STOP_ACTION_BY_TAG);
//    messageManager->removeReceiver(_owner,MSG_RUN_ANIMATE);
//    messageManager->removeReceiver(_owner,MSG_STOP_ANIMATE);
//    messageManager->removeReceiver(_owner,MSG_STOP_ANIMATE_BY_TAG);
    
    Component::cleanupMessages();
}

void RendererComponent::setRenderer(CCNode* renderer)
{
    CC_SAFE_RETAIN(renderer);
    CC_SAFE_RELEASE(_renderer);
    _renderer = renderer;
}

CCNode* RendererComponent::getRenderer()
{
    return _renderer;
}

/**
 * 执行action
 */
void RendererComponent::runAction(CCAction* action)
{
    //如果有标记,则消除源来的动画
    if (action->getTag()) {
        _renderer->stopActionByTag(action->getTag());
    }
    _renderer->runAction(action);
}

/**
 * 停止action
 */
void RendererComponent::stopAction(CCAction* action)
{
    _renderer->stopAction(action);
}

/**
 * 停止action by tag
 */
void RendererComponent::stopActionByTag(int tag)
{
    _renderer->stopActionByTag(tag);
}

/**
 * 响应执行action
 */
void RendererComponent::onRunAction(Message* message)
{
    CCAction* action=static_cast<CCAction*>(message->getData());
    
    //如果有标记,则消除源来的动画
    if (action->getTag()) {
        _renderer->stopActionByTag(action->getTag());
    }
    _renderer->runAction(action);
}

/**
 * 响应停止action
 */
void RendererComponent::onStopAction(Message* message)
{
    CCAction* action=static_cast<CCAction*>(message->getData());
    _renderer->stopAction(action);
}

/**
 * 响应停止action by tag
 */
void RendererComponent::onStopActionByTag(Message* message)
{
    CCInteger* tagValue=static_cast<CCInteger*>(message->getData());
    if (tagValue) {
        _renderer->stopActionByTag(tagValue->getValue());
    }
}


////==============对animation的特殊支持==============//
///**
// * 执行action
// */
//void RendererComponent::runAnimate(CCAction* animate)
//{
//    //default as action
//    runAction(animate);
//}
//
///**
// * 停止action
// */
//void RendererComponent::stopAnimate(CCAction* animate)
//{
//    //default as action
//    stopAction(animate);
//}
//
///**
// * 停止action by tag
// */
//void RendererComponent::stopAnimateByTag(int tag)
//{
//    //default as action
//    stopActionByTag(tag);
//}
//
///**
// * 响应执行action
// */
//void RendererComponent::onRunAnimate(Message* message)
//{
//    //do nothing
//    CCAction* action=static_cast<CCAction*>(message->getData());
//    runAnimate(action);
//}
//
///**
// * 响应停止action
// */
//void RendererComponent::onStopAnimate(Message* message)
//{
//    //do nothing
//    CCAction* action=static_cast<CCAction*>(message->getData());
//    stopAnimate(action);
//}
//
///**
// * 响应停止action by tag
// */
//void RendererComponent::onStopAnimateByTag(Message* message)
//{
//    //do nothing
//    CCInteger* tagValue=static_cast<CCInteger*>(message->getData());
//    if (tagValue) {
//        stopAnimateByTag(tagValue->getValue());
//    }
//}

NS_CC_YHGE_END

