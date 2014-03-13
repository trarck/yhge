#include "ActionComponent.h"
#include <yhge/message.h>
#include <yhge/EntityComponent/Entity.h>
#include "ComponentMessageDefine.h"
#include "ComponentConsts.h"
#include "RendererComponent.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

static const int kEightDirectionAction=1001;

//const int ActionComponent::kRepeatForverLoop=-1;

ActionComponent::ActionComponent()
:Component("ActionComponent")
,m_actions(NULL)
,m_lastActions(NULL)
,m_rendererComponent(NULL)
{

}

ActionComponent::~ActionComponent()
{
	CC_SAFE_RELEASE_NULL(m_actions);
    CC_SAFE_RELEASE_NULL(m_lastActions);
}

bool ActionComponent::init()
{
    if (Component::init()) {
        m_actions=new CCDictionary();
        return true;
    }
    return false;
}

bool ActionComponent::init(const std::string& file)
{
	if(Component::init()){
        //TODO load actions from files
        return true;
    }
    return false;
}

bool ActionComponent::init(CCDictionary* data)
{
	if (Component::init()) {
        setEffects(data);
        return true;
    }
    return false;
}

void ActionComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<RendererComponent*>(m_owner->getComponent("RendererComponent"));
}

void ActionComponent::cleanup()
{
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool ActionComponent::registerMessages()
{
    Component::registerMessages();
    
    this->getMessageManager()->registerReceiver(m_owner,MSG_CHANGE_ANIMATION, NULL ,message_selector(ActionComponent::onChangeAction),this);
    
    return true;
}


void ActionComponent::cleanupMessages()
{
    this->getMessageManager()->removeReceiver(m_owner,MSG_CHANGE_ANIMATION);
    Component::cleanupMessages();
}


/**
 * 按名称取得动画
 */
CCAction* ActionComponent::actionForName(const std::string& name)
{
	return (CCAction*) m_actions->objectForKey(name);
}

CCAction* ActionComponent::actionForName(const std::string& name ,int index)
{
	return (CCAction*)((CCArray*)(m_actions->objectForKey(name)))->objectAtIndex(index);
}

CCAction* ActionComponent::actionForName(const std::string& name ,const std::string& key)
{
	return (CCAction*)((CCDictionary*)(m_actions->objectForKey(name)))->objectForKey(key);
}

/**
 * 按名称取得动画列表
 */
CCArray* ActionComponent::actionListForName(const std::string& name)
{
	return (CCArray*)(m_actions->objectForKey(name));
}

/**
 * 按名称取得动画字典
 */
CCDictionary* ActionComponent::actionMapForName(const std::string& name)
{
	return (CCDictionary*)m_actions->objectForKey(name);
}

/**
 * 添加一个动画
 */
void ActionComponent::addAction(CCAction* action,const std::string&  name)
{
	m_actions->setObject(action ,name);
}

/**
 * 添加一个动画列表
 */
void ActionComponent::addActionList(CCArray* actionList ,const std::string& name)
{
	m_actions->setObject(actionList ,name);
}

/**
 * 添加一个动画字典
 */
void ActionComponent::addActionMap(CCDictionary* actionMap ,const std::string& name)
{
	m_actions->setObject(actionMap ,name);
}

/**
 * 移除一个动画
 */
void ActionComponent::removeActionNamed(const std::string& name)
{
	m_actions->removeObjectForKey(name);
}

/**
 * 播放一个动画
 */
void ActionComponent::runAction(CCAction* action)
{
    if(action){
//        CCAction* action=createActionFromAction(action);
        
        //如果性能比较低，可以直接调用renderer component的相关函数
        //通知render run action
        m_rendererComponent->runAction(action);
        
//        setLastAction(action);
//        setLastAction(action);
    }
}

void ActionComponent::onChangeAction(Message *message)
{
    CCDictionary* data=message->getDictionary();
    
    CCString* actionName=(CCString*)data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_NAME);
    int direction=((CCInteger*) data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_DIRECTION))->getValue();
    CCLOG("direction:%d name:%s",direction,actionName->getCString());
    
    CCAction* action= actionForName(actionName->getCString(),direction);
    
    if(action){
        runAction(action);
    }else {
        CCLOG("unknow action name %s action is null",actionName->getCString());
    }
}

void ActionComponent::onActionComplete()
{
    //消除上次action
//    setLastAction(NULL);
    //发送动画播放完成
    getMessageManager()->dispatchMessage(MSG_ANIMATION_COMPLETE, this, m_owner);
}

/**
 * 从动画里创建action
 */
CCAction* ActionComponent::createActionFromDefine(CCAction* action)
{
//    CCAction* action=NULL;
//    int loops=action->getLoops();
//    
//    if (loops==kRepeatForverLoop) {
//        CCAnimate *animate= CCAnimate::create(action);
//        action=CCRepeatForever::create(CCSequence::create(animate,NULL));
//    }else{
//        action= CCSequence::createWithTwoActions(
//                                                 CCAnimate::create(action),
//                                                 CCCallFunc::create(this, callfunc_selector(ActionComponent::onActionComplete)));
//    }
//    action->setTag(kEightDirectionAction);
//    return action;
    
    return NULL;
}

NS_CC_YHGE_END