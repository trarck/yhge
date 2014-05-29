#include "AnimationManager.h"


NS_CC_YHGE_BEGIN

AnimationManager::AnimationManager()
:m_animations(NULL)
,m_animationGroups(NULL)
{
    
}

AnimationManager::~AnimationManager()
{
    CC_SAFE_RELEASE_NULL(m_animations);
    CC_SAFE_RELEASE_NULL(m_animationGroups);
}

bool AnimationManager::init()
{
    m_animations=new CCArray();
    m_animationGroups=new CCDictionary();
    
    
    return true;
}

void AnimationManager::add(Animation* animation)
{
    m_animations->addObject(animation);
}

void AnimationManager::remove(Animation* animation)
{
    m_animations->removeObject(animation);
}

void AnimationManager::addAnimationGroup(AnimationGroup* animationGroup,int key)
{
    m_animationGroups->setObject(animationGroup, key);
}

void AnimationManager::removeAnimationGroup(int key)
{
    m_animationGroups->removeObjectForKey(key);
}

AnimationGroup* AnimationManager::getAnimationGroupByKey(int key)
{
    return static_cast<AnimationGroup*>(m_animationGroups->objectForKey(key));
}

AnimationGroup* AnimationManager::getAnimationGroupByDuration(float duration)
{
    CCDictElement* elem=NULL;
    AnimationGroup* animationGroup=NULL;
    CCDICT_FOREACH(m_animationGroups, elem){
        
        animationGroup=static_cast<AnimationGroup*>(elem->getObject());
        
        if (animationGroup->getDuration()==duration) {
            return animationGroup;
        }
    }
    
    return NULL;
}


void AnimationManager::addToAnimationGroup(Animation* animation)
{
    CCAssert(animation!=NULL, "AnimationManager::addToAnimationGroup cant be null");
    AnimationGroup* animationGroup=getAnimationGroupByDuration(animation->getDuration());
    if (animationGroup) {
        animationGroup->add(animation);
    }
}

void AnimationManager::removeFromAnimationGroup(Animation* animation)
{
    CCAssert(animation!=NULL, "AnimationManager::removeFromAnimationGroup cant be null");
    AnimationGroup* animationGroup=getAnimationGroupByDuration(animation->getDuration());
    if (animationGroup) {
        animationGroup->remove(animation);
    }
}

NS_CC_YHGE_END