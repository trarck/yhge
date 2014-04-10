#include "AnimationComponent.h"
#include <yhge/Base/Log.h>
#include <yhge/message.h>
#include <yhge/EntityComponent/Entity.h>
#include "ComponentMessageDefine.h"
#include "ComponentConsts.h"
#include "SpriteRendererComponent.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

//const int AnimationComponent::kRepeatForverLoop=-1;

AnimationComponent::AnimationComponent()
:Component("AnimationComponent")
,m_animations(NULL)
,m_lastAnimation(NULL)
,m_lastAction(NULL)
,m_rendererComponent(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
	CC_SAFE_RELEASE_NULL(m_animations);
    CC_SAFE_RELEASE_NULL(m_lastAction);
}

bool AnimationComponent::init()
{
    if (Component::init()) {
        m_animations=new CCDictionary();
        return true;
    }
    return false;
}

bool AnimationComponent::init(const std::string& file)
{
	if(Component::init()){
        //TODO load animations from files
        return true;
    }
    return false;
}

bool AnimationComponent::init(CCDictionary* data)
{
	if (Component::init()) {
        setAnimations(data);
        return true;
    }
    return false;
}

void AnimationComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<SpriteRendererComponent*>(m_owner->getComponent("RendererComponent"));
}

void AnimationComponent::cleanup()
{
    if (m_lastAction)
    {
        m_rendererComponent->getSpriteRenderer()->stopAction(m_lastAction);
    }
    
    m_rendererComponent=NULL;

    Component::cleanup();
}

bool AnimationComponent::registerMessages()
{
    Component::registerMessages();
    
    this->getMessageManager()->registerReceiver(m_owner,MSG_CHANGE_ANIMATION, NULL ,message_selector(AnimationComponent::onChangeAnimation),this);
    
    return true;
}


void AnimationComponent::cleanupMessages()
{
    this->getMessageManager()->removeReceiver(m_owner,MSG_CHANGE_ANIMATION);
    Component::cleanupMessages();
}


/**
 * 按名称取得动画
 */
CCAnimation* AnimationComponent::animationForName(const std::string& name)
{
	return (CCAnimation*) m_animations->objectForKey(name);
}

CCAnimation* AnimationComponent::animationForName(const std::string& name ,int index)
{
	return (CCAnimation*)((CCArray*)(m_animations->objectForKey(name)))->objectAtIndex(index);
}

CCAnimation* AnimationComponent::animationForName(const std::string& name ,const std::string& key)
{
	return (CCAnimation*)((CCDictionary*)(m_animations->objectForKey(name)))->objectForKey(key);
}

/**
 * 按名称取得动画列表
 */
CCArray* AnimationComponent::animationListForName(const std::string& name)
{
	return (CCArray*)(m_animations->objectForKey(name));
}

/**
 * 按名称取得动画字典
 */
CCDictionary* AnimationComponent::animationMapForName(const std::string& name)
{
	return (CCDictionary*)m_animations->objectForKey(name);
}

/**
 * 添加一个动画
 */
void AnimationComponent::addAnimation(CCAnimation* animation,const std::string&  name)
{
	m_animations->setObject(animation ,name);
}

/**
 * 添加一个动画列表
 */
void AnimationComponent::addAnimationList(CCArray* animationList ,const std::string& name)
{
	m_animations->setObject(animationList ,name);
}

/**
 * 添加一个动画字典
 */
void AnimationComponent::addAnimationMap(CCDictionary* animationMap ,const std::string& name)
{
	m_animations->setObject(animationMap ,name);
}

/**
 * 移除一个动画
 */
void AnimationComponent::removeAnimationNamed(const std::string& name)
{
	m_animations->removeObjectForKey(name);
}

/**
 * 播放一个动画
 */
void AnimationComponent::runAnimation(CCAnimation* animation,bool needCompleteAction)
{
    if(animation && m_lastAnimation!=animation){
        CCAction* action=createActionFromAnimation(animation,needCompleteAction);

        //停止上一个action
        if (m_lastAction)
        {
            m_rendererComponent->getSpriteRenderer()->stopAction(m_lastAction);
        }
        
        //如果性能比较低，可以直接调用renderer component的相关函数
        //通知render run action
        //由于runAction要到下一帧才设置成具体的元素,如果此时取得的元素大小是之前的，不是动画的大小。
        m_rendererComponent->getSpriteRenderer()->runAction(action);
        
        setLastAction(action);
        setLastAnimation(animation);
    }
}

void AnimationComponent::displayAnimationFrame(CCAnimation* animation,int frameIndex)
{
    CCAnimationFrame* frame = (CCAnimationFrame*)animation->getFrames()->objectAtIndex(frameIndex);
    
    CCAssert(frame, "AnimationComponent#displayAnimationFrame. Invalid frame");
    
    m_rendererComponent->getSpriteRenderer()->setDisplayFrame(frame->getSpriteFrame());
}

void AnimationComponent::onChangeAnimation(Message *message)
{
    YHINFO("AnimationComponent::onChangeAnimation do nothing.you must implement by child");
//    CCDictionary* data=message->getDictionary();
//    int direction=0;
//    
//    CCString* animationName=(CCString*)data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_NAME);
//    
//    CCInteger* directionValue=((CCInteger*) data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_DIRECTION));
//    if (directionValue) {
//        direction=directionValue->getValue();
//    }
//    
//    bool needCompleteAction=false;
//    
//    CCBool* needCompleteAcionValue=static_cast<CCBool*>(data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_NEEDCOMPLETEACTION));
//    if(needCompleteAcionValue){
//        needCompleteAction=needCompleteAcionValue->getValue();
//    }
//    
//    YHDEBUG("direction:%d name:%s",direction,animationName->getCString());
//    
//    CCAnimation* animation= animationForName(animationName->getCString(),direction);
//    
//    if(animation){
//        runAnimation(animation,needCompleteAction);
//    }else {
//        YHERROR("unknow animation name %s action is null",animationName->getCString());
//    }
}

void AnimationComponent::onAnimationComplete()
{
    //消除上次action
    setLastAction(NULL);
    //发送动画播放完成
    getMessageManager()->dispatchMessage(MSG_ANIMATION_COMPLETE, this, m_owner);
}

/**
 * 从动画里创建action
 */
CCAction* AnimationComponent::createActionFromAnimation(CCAnimation* animation,bool needCompleteAction)
{
    CCAction* action=NULL;
    int loops=animation->getLoops();
    
    if (loops==kRepeatForverLoop) {
        //不能修改animation的任何属性，由于它是一个指针。
        CCAnimate *animate= CCAnimate::create(animation);
        action=CCRepeatForever::create(CCSequence::create(animate,NULL));
    }else{
        if (needCompleteAction) {
            action= CCSequence::createWithTwoActions(
                                                     CCAnimate::create(animation),
                                                     CCCallFunc::create(this, callfunc_selector(AnimationComponent::onAnimationComplete)));
        }else{
            action=CCAnimate::create(animation);
        }
    }

    return action;
}

CCSize AnimationComponent::getAnimationContentSize(CCAnimation* animation)
{
    if (animation) {
        
        CCArray* frames=animation->getFrames();
        if (frames && frames->count()) {
            CCAnimationFrame* animationFrame=static_cast<CCAnimationFrame*>(frames->objectAtIndex(0));
            CCSpriteFrame* spriteFrame=animationFrame->getSpriteFrame();
            return spriteFrame->getOriginalSize();
        }
    }
    
    return CCSizeZero;
}

NS_CC_YHGE_END