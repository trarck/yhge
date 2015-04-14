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
,_animations(NULL)
,_lastAnimation(NULL)
,_lastAction(NULL)
,_rendererComponent(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
	CC_SAFE_RELEASE_NULL(_animations);
    CC_SAFE_RELEASE_NULL(_lastAction);
}

bool AnimationComponent::init()
{
    if (Component::init()) {
        _animations=new CCDictionary();
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
    _rendererComponent=static_cast<SpriteRendererComponent*>(_owner->getComponent("RendererComponent"));
}

void AnimationComponent::cleanup()
{
    if (_lastAction)
    {
        _rendererComponent->getSpriteRenderer()->stopAction(_lastAction);
    }
    
    _rendererComponent=NULL;

    Component::cleanup();
}

bool AnimationComponent::registerMessages()
{
    Component::registerMessages();
    
    this->getMessageManager()->registerReceiver(_owner,MSG_CHANGE_ANIMATION, NULL ,message_selector(AnimationComponent::onChangeAnimation),this);
    
    return true;
}


void AnimationComponent::cleanupMessages()
{
    this->getMessageManager()->removeReceiver(_owner,MSG_CHANGE_ANIMATION);
    Component::cleanupMessages();
}


/**
 * 按名称取得动画
 */
CCAnimation* AnimationComponent::animationForName(const std::string& name)
{
	return (CCAnimation*) _animations->objectForKey(name);
}

CCAnimation* AnimationComponent::animationForName(const std::string& name ,int index)
{
	return (CCAnimation*)((CCArray*)(_animations->objectForKey(name)))->objectAtIndex(index);
}

CCAnimation* AnimationComponent::animationForName(const std::string& name ,const std::string& key)
{
	return (CCAnimation*)((CCDictionary*)(_animations->objectForKey(name)))->objectForKey(key);
}

/**
 * 按名称取得动画列表
 */
CCArray* AnimationComponent::animationListForName(const std::string& name)
{
	return (CCArray*)(_animations->objectForKey(name));
}

/**
 * 按名称取得动画字典
 */
CCDictionary* AnimationComponent::animationMapForName(const std::string& name)
{
	return (CCDictionary*)_animations->objectForKey(name);
}

/**
 * 添加一个动画
 */
void AnimationComponent::addAnimation(CCAnimation* animation,const std::string&  name)
{
	_animations->setObject(animation ,name);
}

/**
 * 添加一个动画列表
 */
void AnimationComponent::addAnimationList(CCArray* animationList ,const std::string& name)
{
	_animations->setObject(animationList ,name);
}

/**
 * 添加一个动画字典
 */
void AnimationComponent::addAnimationMap(CCDictionary* animationMap ,const std::string& name)
{
	_animations->setObject(animationMap ,name);
}

/**
 * 移除一个动画
 */
void AnimationComponent::removeAnimationNamed(const std::string& name)
{
	_animations->removeObjectForKey(name);
}

/**
 * 播放一个动画
 */
void AnimationComponent::runAnimation(CCAnimation* animation,bool needCompleteAction)
{
    if(animation && _lastAnimation!=animation){
        CCAction* action=createActionFromAnimation(animation,needCompleteAction);

        //停止上一个action
        if (_lastAction)
        {
            _rendererComponent->getSpriteRenderer()->stopAction(_lastAction);
        }
        
        //如果性能比较低，可以直接调用renderer component的相关函数
        //通知render run action
        //由于runAction要到下一帧才设置成具体的元素,如果此时取得的元素大小是之前的，不是动画的大小。
        _rendererComponent->getSpriteRenderer()->runAction(action);
        
        setLastAction(action);
        setLastAnimation(animation);
    }
}

void AnimationComponent::displayAnimationFrame(CCAnimation* animation,int frameIndex)
{
    CCAnimationFrame* frame = (CCAnimationFrame*)animation->getFrames()->objectAtIndex(frameIndex);
    
    CCAssert(frame, "AnimationComponent#displayAnimationFrame. Invalid frame");
    
    _rendererComponent->getSpriteRenderer()->setDisplayFrame(frame->getSpriteFrame());
}

void AnimationComponent::onChangeAnimation(Message *message)
{
    YHINFO("AnimationComponent::onChangeAnimation do nothing.you must implement by child");
    CCDictionary* data=message->getDictionary();
    
    CCString* animationName=(CCString*)data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_NAME);
    YHDEBUG("onChangeAnimation name:%s",animationName->getCString());
    
    CCAnimation* animation= NULL;
    
    CCInteger* indexValue=((CCInteger*) data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_INDEX));
    if (indexValue) {
        animation=animationForName(animationName->getCString(), indexValue->getValue());
    }else{
        CCString* keyValue=static_cast<CCString*>(data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_KEY));
        if (keyValue) {
            animation=animationForName(animationName->getCString(), keyValue->getCString());
        }else{
            animation=animationForName(animationName->getCString());
        }
    }
    
    bool needCompleteAction=false;
    
    CCBool* needCompleteAcionValue=static_cast<CCBool*>(data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_NEEDCOMPLETEACTION));
    if(needCompleteAcionValue){
        needCompleteAction=needCompleteAcionValue->getValue();
    }

    if(animation){
        runAnimation(animation,needCompleteAction);
    }else {
        YHERROR("unknow animation name %s action is null",animationName->getCString());
    }
}

void AnimationComponent::onAnimationComplete()
{
    //消除上次action
    setLastAction(NULL);
    //发送动画播放完成
    getMessageManager()->dispatchMessage(MSG_ANIMATION_COMPLETE, this, _owner);
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