#include "AnimationGroup.h"

NS_CC_YHGE_BEGIN

static const int kMaxDeltaFrame=60;

AnimationGroup::AnimationGroup()
:_duration(0.0f)
,_elapsed(0.0f)
,_frameIndex(0)
//,_nextFrameIndex(0)
,_skipAble(true)
,_animations(NULL)
,_maxDelta(60.0f)
{
    
}

AnimationGroup::~AnimationGroup()
{
    CC_SAFE_RELEASE_NULL(_animations);
}

bool AnimationGroup::init(float duration)
{
    CCAssert(duration>0, "AnimationGroup::init must great then 0");
    
    _animations=new CCArray();
    
    _duration=duration;
    
    _maxDelta=kMaxDeltaFrame*duration;
    
    return true;
}

void AnimationGroup::update(float delta)
{
    if (_skipAble) {
        delta=delta>_maxDelta?_duration:delta;
        
        _elapsed+=delta;
        
        int nextFrameIndex=(int)floor(_elapsed/_duration);
        
        if (nextFrameIndex>_frameIndex) {
            
            int deltaFrame=nextFrameIndex-_frameIndex;
            
            Ref* obj=NULL;
            Animation* animation=NULL;
            CCARRAY_FOREACH_REVERSE(_animations, obj){
                animation=static_cast<Animation*>(obj);
                animation->update(delta, deltaFrame);
            }
            
            _frameIndex=nextFrameIndex;
        }
        
    }else{
        ++_frameIndex;
        
        Ref* obj=NULL;
        Animation* animation=NULL;
        CCARRAY_FOREACH_REVERSE(_animations, obj){
            animation=static_cast<Animation*>(obj);
            animation->update(delta, 1);
        }
    }
}

void AnimationGroup::add(Animation* animation)
{
    _animations->addObject(animation);
}

void AnimationGroup::remove(Animation* animation)
{
    _animations->removeObject(animation);
}

NS_CC_YHGE_END