#include "AnimationComponent.h"
#include <yhge/message.h>
#include <yhge/EntityComponent/Entity.h>
#include "ComponentMessageDefine.h"
#include "ComponentConsts.h"
#include "RendererComponent.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

static const int kEightDirectionAction=1001;

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
    m_rendererComponent=static_cast<RendererComponent*>(m_owner->getComponent("RendererComponent"));
}

void AnimationComponent::cleanup()
{
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
            m_rendererComponent->stopAction(m_lastAction);
        }
        
        //如果性能比较低，可以直接调用renderer component的相关函数
        //通知render run action
        m_rendererComponent->runAction(action);
        
        setLastAction(action);
        setLastAnimation(animation);
    }
}

void AnimationComponent::onChangeAnimation(Message *message)
{
    CCDictionary* data=message->getDictionary();
    int direction=0;
    
    CCString* animationName=(CCString*)data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_NAME);
    
    CCInteger* directionValue=((CCInteger*) data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_DIRECTION));
    if (directionValue) {
        direction=directionValue->getValue();
    }
    
    bool needCompleteAction=false;
    
    CCBool* needCompleteAcionValue=static_cast<CCBool*>(data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_NEEDCOMPLETEACTION));
    if(needCompleteAcionValue){
        needCompleteAction=needCompleteAcionValue->getValue();
    }
    
    CCLOG("direction:%d name:%s",direction,animationName->getCString());
    
    CCAnimation* animation= animationForName(animationName->getCString(),direction);
    
    if(animation){
        runAnimation(animation,needCompleteAction);
    }else {
        CCLOG("unknow animation name %s action is null",animationName->getCString());
    }
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
    action->setTag(kEightDirectionAction);
    return action;
}

/**
 * 从文件中取得8方向动画
 * 关键帧在一张图片里。根据名子来确定方向
 */
CCArray* AnimationComponent::eightDirectionActionListWithFile(const char* file ,int frameCount ,CCSize frameSize ,float delay,int loops)
{
	CCTexture2D *texture=CCTextureCache::sharedTextureCache()->addImage(file);
	
	CCArray* animations=CCArray::createWithCapacity(8);

	//move action
	for (int i=0; i<8; i++) {
		CCArray* animFrames=new CCArray();
		animFrames->initWithCapacity(frameCount);
		for (int j=0; j<frameCount; j++) {
			CCSpriteFrame *frame=CCSpriteFrame::createWithTexture(texture ,CCRectMake(j*frameSize.width, i*frameSize.height, frameSize.width, frameSize.height));
			animFrames->addObject(frame);
		}
        
		CCAnimation *animation=CCAnimation::createWithSpriteFrames(animFrames,delay);
        animation->setLoops(loops);
        
        animFrames->release();
        
        animations->addObject(animation);
		
	}
	return animations;
}

/**
 * 从目录中取得8方向动画
 * 关键帧是一张张图片。根据名子来确定方向
 */
CCArray* AnimationComponent::eightDirectionActionListWithDir(const char* dir ,int frameCount ,CCSize frameSize ,float delay,const char* pathFormat,int loops)
{
	CCArray* animations=CCArray::createWithCapacity(8);
	
	//move action
	char str[255] = {0};
	for (int i=0; i<8; i++) {
		CCAnimation* animation = CCAnimation::create();
		for (int j=0; j<frameCount; j++) {
			sprintf(str,pathFormat,dir,i,j);//"%s/%02d%03d.png"
			animation->addSpriteFrameWithFileName(str);
		}
		animation->setDelayPerUnit(delay);
		animation->setRestoreOriginalFrame(true);
        animation->setLoops(loops);
		//animation.delay=delay;
        animations->addObject(animation);
	}
	return animations;
}

/**
 * 从目录中取得8方向动画
 * 关键帧是一张张图片。根据名子来确定方向
 */
CCArray* AnimationComponent::eightDirectionActionListWithDirResource(const char* resource ,int frameCount ,CCSize frameSize ,float delay,int loops)
{
    CCArray* animations=CCArray::createWithCapacity(8);
	
	//move actiongit
	char str[255] = {0};
	for (int i=0; i<8; i++) {
		CCAnimation* animation = CCAnimation::create();
		for (int j=0; j<frameCount; j++) {
			sprintf(str,resource,i,j);//"xxx/xx/%02d%03d.png"
			animation->addSpriteFrameWithFileName(str);
		}
		animation->setDelayPerUnit(delay);
		animation->setRestoreOriginalFrame(true);
        animation->setLoops(loops);
		//animation.delay=delay;
        animations->addObject(animation);
	}
	return animations;
}

NS_CC_YHGE_END