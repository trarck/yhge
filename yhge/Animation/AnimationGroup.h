#ifndef YHGE_ANIMATION_ANIMATIONGROUP_H_
#define YHGE_ANIMATION_ANIMATIONGROUP_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"
#include "Animation.h"

NS_CC_YHGE_BEGIN

class AnimationGroup:public Ref
{
public:
    AnimationGroup();
    
    ~AnimationGroup();
    
    bool init(float duration);
    
    void update(float delta);
    
    void add(Animation* animation);
    
    void remove(Animation* animation);
    
    
public:
    
    inline void setElapsed(float elapsed)
    {
        _elapsed = elapsed;
    }
    
    inline float getElapsed()
    {
        return _elapsed;
    }
    
    inline void setDuration(float duration)
    {
        _duration = duration;
    }
    
    inline float getDuration()
    {
        return _duration;
    }
    
    inline void setFrameIndex(int frameIndex)
    {
        _frameIndex = frameIndex;
    }
    
    inline int getFrameIndex()
    {
        return _frameIndex;
    }
    
//    inline void setNextFrameIndex(int nextFrameIndex)
//    {
//        _nextFrameIndex = nextFrameIndex;
//    }
//    
//    inline int getNextFrameIndex()
//    {
//        return _nextFrameIndex;
//    }
    
    inline void setSkipAble(bool skipAble)
    {
        _skipAble = skipAble;
    }
    
    inline bool isSkipAble()
    {
        return _skipAble;
    }
    
    inline void setAnimations(CCArray* animations)
    {
        CC_SAFE_RETAIN(animations);
        CC_SAFE_RELEASE(_animations);
        _animations = animations;
    }
    
    inline CCArray* getAnimations()
    {
        return _animations;
    }
    
    inline void setMaxDelta(float maxDelta)
    {
        _maxDelta = maxDelta;
    }
    
    inline float getMaxDelta()
    {
        return _maxDelta;
    }
    
protected:
    
    float _elapsed;
    float _duration;
    int _frameIndex;
//    int _nextFrameIndex;
    bool _skipAble;
    
    CCArray* _animations;
    
    //最大跳帧值
    float _maxDelta;
};

NS_CC_YHGE_END

#endif //YHGE_ANIMATION_ANIMATIONGROUP_H_