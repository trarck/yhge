#ifndef YHGE_ANIMATION_ANIMATIONMANAGER_H_
#define YHGE_ANIMATION_ANIMATIONMANAGER_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"
#include "Animation.h"
#include "AnimationGroup.h"

NS_CC_YHGE_BEGIN

class AnimationManager:public CCObject
{
public:
    AnimationManager();
    
    ~AnimationManager();
    
    bool init();

    static AnimationManager* getInstance();
    
    static void destroyInstance();
    
    void update(float delta);
    
    void add(Animation* animation);
    
    void remove(Animation* animation);
    
    void addAnimationGroup(AnimationGroup* animationGroup,int key);
    
    void removeAnimationGroup(int key);
    
    AnimationGroup* getAnimationGroupByKey(int key);
    
    AnimationGroup* getAnimationGroupByDuration(float duration);
    
    void addToAnimationGroup(Animation* animation);
    
    void removeFromAnimationGroup(Animation* animation);
    
public:
    
    inline void setAnimations(CCArray* animations)
    {
        CC_SAFE_RETAIN(animations);
        CC_SAFE_RELEASE(m_animations);
        m_animations = animations;
    }
    
    inline CCArray* getAnimations()
    {
        return m_animations;
    }

    inline void setAnimationGroups(CCDictionary* animationGroups)
    {
        CC_SAFE_RETAIN(animationGroups);
        CC_SAFE_RELEASE(m_animationGroups);
        m_animationGroups = animationGroups;
    }
    
    inline CCDictionary* getAnimationGroups()
    {
        return m_animationGroups;
    }
    
protected:
    
    CCArray* m_animations;
    
    CCDictionary* m_animationGroups;
    
};

NS_CC_YHGE_END

#endif //YHGE_ANIMATION_ANIMATIONMANAGER_H_