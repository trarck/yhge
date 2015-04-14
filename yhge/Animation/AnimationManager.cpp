#include "AnimationManager.h"

NS_CC_YHGE_BEGIN

static AnimationManager* sAnimationManagerInstance=NULL;

AnimationManager::AnimationManager()
:_animations(NULL)
,_animationGroups(NULL)
{
    
}

AnimationManager::~AnimationManager()
{
    CC_SAFE_RELEASE_NULL(_animations);
    CC_SAFE_RELEASE_NULL(_animationGroups);
}

bool AnimationManager::init()
{
    _animations=new CCArray();
    _animationGroups=new CCDictionary();
    
    
    return true;
}

AnimationManager* AnimationManager::getInstance()
{
    if (!sAnimationManagerInstance)
    {
        sAnimationManagerInstance=new AnimationManager();
        sAnimationManagerInstance->init();
    }

    return sAnimationManagerInstance;
}

void AnimationManager::destroyInstance()
{
    if (sAnimationManagerInstance)
    {
        sAnimationManagerInstance->release();
        sAnimationManagerInstance=NULL;
    }
}

void AnimationManager::update(float delta)
{
    Ref* pObj=NULL;

    CCARRAY_FOREACH_REVERSE(_animations, pObj){
        static_cast<Animation*>(pObj)->update(delta);
    }
    
    CCDictElement* element=NULL;
    
    CCDICT_FOREACH(_animationGroups, element){
        static_cast<AnimationGroup*>(element->getObject())->update(delta);
    }
}

void AnimationManager::add(Animation* animation)
{
    _animations->addObject(animation);
}

void AnimationManager::remove(Animation* animation)
{
    _animations->removeObject(animation);
}

void AnimationManager::addAnimationGroup(AnimationGroup* animationGroup,int key)
{
    _animationGroups->setObject(animationGroup, key);
}

void AnimationManager::removeAnimationGroup(int key)
{
    _animationGroups->removeObjectForKey(key);
}

AnimationGroup* AnimationManager::getAnimationGroupByKey(int key)
{
    return static_cast<AnimationGroup*>(_animationGroups->objectForKey(key));
}

AnimationGroup* AnimationManager::getAnimationGroupByDuration(float duration)
{
    CCDictElement* elem=NULL;
    AnimationGroup* animationGroup=NULL;
    CCDICT_FOREACH(_animationGroups, elem){
        
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