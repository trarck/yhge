#include "EffectComponent.h"
#include <yhge/message.h>
#include <yhge/EntityComponent/Entity.h>
#include "ComponentMessageDefine.h"
#include "ComponentConsts.h"
#include "RendererComponent.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

static const int kEightDirectionAction=1001;

//const int EffectComponent::kRepeatForverLoop=-1;

EffectComponent::EffectComponent()
:Component("EffectComponent")
,m_effects(NULL)
,m_lastActions(NULL)
,m_rendererComponent(NULL)
{

}

EffectComponent::~EffectComponent()
{
	CC_SAFE_RELEASE_NULL(m_effects);
    CC_SAFE_RELEASE_NULL(m_lastActions);
}

bool EffectComponent::init()
{
    if (Component::init()) {
        m_effects=new CCDictionary();
        return true;
    }
    return false;
}

bool EffectComponent::init(const std::string& file)
{
	if(Component::init()){
        //TODO load effects from files
        return true;
    }
    return false;
}

bool EffectComponent::init(CCDictionary* data)
{
	if (Component::init()) {
        setEffects(data);
        return true;
    }
    return false;
}

void EffectComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<RendererComponent*>(m_owner->getComponent("RendererComponent"));
}

void EffectComponent::cleanup()
{
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool EffectComponent::registerMessages()
{
    Component::registerMessages();
    
//    this->getMessageManager()->registerReceiver(m_owner,MSG_CHANGE_ANIMATION, NULL ,message_selector(EffectComponent::onChangeEffect),this);
    
    return true;
}


void EffectComponent::cleanupMessages()
{
//    this->getMessageManager()->removeReceiver(m_owner,MSG_CHANGE_ANIMATION);
    Component::cleanupMessages();
}


/**
 * 按名称取得动画
 */
CCEffect* EffectComponent::effectForName(const std::string& name)
{
	return (CCEffect*) m_effects->objectForKey(name);
}

CCEffect* EffectComponent::effectForName(const std::string& name ,int index)
{
	return (CCEffect*)((CCArray*)(m_effects->objectForKey(name)))->objectAtIndex(index);
}

CCEffect* EffectComponent::effectForName(const std::string& name ,const std::string& key)
{
	return (CCEffect*)((CCDictionary*)(m_effects->objectForKey(name)))->objectForKey(key);
}

/**
 * 按名称取得动画列表
 */
CCArray* EffectComponent::effectListForName(const std::string& name)
{
	return (CCArray*)(m_effects->objectForKey(name));
}

/**
 * 按名称取得动画字典
 */
CCDictionary* EffectComponent::effectMapForName(const std::string& name)
{
	return (CCDictionary*)m_effects->objectForKey(name);
}

/**
 * 添加一个动画
 */
void EffectComponent::addEffect(CCEffect* effect,const std::string&  name)
{
	m_effects->setObject(effect ,name);
}

/**
 * 添加一个动画列表
 */
void EffectComponent::addEffectList(CCArray* effectList ,const std::string& name)
{
	m_effects->setObject(effectList ,name);
}

/**
 * 添加一个动画字典
 */
void EffectComponent::addEffectMap(CCDictionary* effectMap ,const std::string& name)
{
	m_effects->setObject(effectMap ,name);
}

/**
 * 移除一个动画
 */
void EffectComponent::removeEffectNamed(const std::string& name)
{
	m_effects->removeObjectForKey(name);
}

/**
 * 播放一个动画
 */
void EffectComponent::runEffect(CCEffect* effect)
{
//    if(effect && m_lastEffect!=effect){
//        CCAction* action=createActionFromEffect(effect);
//
//        //停止上一个actions
////        if (m_lastActions)
////        {
////            m_rendererComponent->stopAction(m_lastAction);
////        }
//        
//        //如果性能比较低，可以直接调用renderer component的相关函数
//        //通知render run action
//        m_rendererComponent->runAction(action);
//        
////        setLastAction(action);
//    }
}

void EffectComponent::onChangeEffect(Message *message)
{
//    CCDictionary* data=message->getDictionary();
//    
//    CCString* effectName=(CCString*)data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_NAME);
//    int direction=((CCInteger*) data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_DIRECTION))->getValue();
//    CCLOG("direction:%d name:%s",direction,effectName->getCString());
//    
//    CCEffect* effect= effectForName(effectName->getCString(),direction);
//    
//    if(effect){
//        runEffect(effect);
//    }else {
//        CCLOG("unknow effect name %s action is null",effectName->getCString());
//    }
}

void EffectComponent::onEffectComplete()
{
    //消除上次action
//    setLastAction(NULL);
    //发送动画播放完成
    getMessageManager()->dispatchMessage(MSG_ANIMATION_COMPLETE, this, m_owner);
}

/**
 * 从动画里创建action
 */
CCAction* EffectComponent::createActionFromEffect(CCEffect* effect)
{
//    CCAction* action=NULL;
//    int loops=effect->getLoops();
//    
//    if (loops==kRepeatForverLoop) {
//        CCAnimate *animate= CCAnimate::create(effect);
//        action=CCRepeatForever::create(CCSequence::create(animate,NULL));
//    }else{
//        action= CCSequence::createWithTwoActions(
//                                                 CCAnimate::create(effect),
//                                                 CCCallFunc::create(this, callfunc_selector(EffectComponent::onEffectComplete)));
//    }
//    action->setTag(kEightDirectionAction);
//    return action;
    
    return NULL;
}

NS_CC_YHGE_END