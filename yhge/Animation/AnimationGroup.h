#ifndef YHGE_ANIMATION_ANIMATIONGROUP_H_
#define YHGE_ANIMATION_ANIMATIONGROUP_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"
#include "Animation.h"

NS_CC_YHGE_BEGIN

class AnimationGroup:public CCObject
{
    
    AnimationGroup();
    
    ~AnimationGroup();
    
    bool init(float duration);
    
    void update(float delta);
    
    void add(Animation* animation);
    
    void remove(Animation* animation);
    
    
public:
    
    inline void setElapsed(float elapsed)
    {
        m_elapsed = elapsed;
    }
    
    inline float getElapsed()
    {
        return m_elapsed;
    }
    
    inline void setDuration(float duration)
    {
        m_duration = duration;
    }
    
    inline float getDuration()
    {
        return m_duration;
    }
    
    inline void setFrameIndex(int frameIndex)
    {
        m_frameIndex = frameIndex;
    }
    
    inline int getFrameIndex()
    {
        return m_frameIndex;
    }
    
//    inline void setNextFrameIndex(int nextFrameIndex)
//    {
//        m_nextFrameIndex = nextFrameIndex;
//    }
//    
//    inline int getNextFrameIndex()
//    {
//        return m_nextFrameIndex;
//    }
    
    inline void setSkipAble(bool skipAble)
    {
        m_skipAble = skipAble;
    }
    
    inline bool isSkipAble()
    {
        return m_skipAble;
    }
    
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
    
    inline void setMaxDelta(float maxDelta)
    {
        m_maxDelta = maxDelta;
    }
    
    inline float getMaxDelta()
    {
        return m_maxDelta;
    }
    
protected:
    
    float m_elapsed;
    float m_duration;
    int m_frameIndex;
//    int m_nextFrameIndex;
    bool m_skipAble;
    
    CCArray* m_animations;
    
    //最大跳帧值
    float m_maxDelta;
};

NS_CC_YHGE_END

#endif //YHGE_ANIMATION_ANIMATIONGROUP_H_