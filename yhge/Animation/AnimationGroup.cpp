#include "AnimationGroup.h"

NS_CC_YHGE_BEGIN

static const int kMaxDeltaFrame=60;

AnimationGroup::AnimationGroup()
:m_duration(0.0f)
,m_elapsed(0.0f)
,m_frameIndex(0)
//,m_nextFrameIndex(0)
,m_skipAble(true)
,m_animations(NULL)
,m_maxDelta(60.0f)
{
    
}

AnimationGroup::~AnimationGroup()
{
    CC_SAFE_RELEASE_NULL(m_animations);
}

bool AnimationGroup::init(float duration)
{
    CCAssert(duration>0, "AnimationGroup::init must great then 0");
    
    m_animations=new CCArray();
    
    m_duration=duration;
    
    m_maxDelta=kMaxDeltaFrame*duration;
    
    return true;
}

void AnimationGroup::update(float delta)
{
    if (m_skipAble) {
        delta=delta>m_maxDelta?m_duration:delta;
        
        m_elapsed+=delta;
        
        int nextFrameIndex=(int)floor(m_elapsed/m_duration);
        
        if (nextFrameIndex>m_frameIndex) {
            
            int deltaFrame=nextFrameIndex-m_frameIndex;
            
            CCObject* obj=NULL;
            Animation* animation=NULL;
            CCARRAY_FOREACH_REVERSE(m_animations, obj){
                animation=static_cast<Animation*>(obj);
                animation->update(delta, deltaFrame);
            }
            
            m_frameIndex=nextFrameIndex;
        }
        
    }else{
        ++m_frameIndex;
        
        CCObject* obj=NULL;
        Animation* animation=NULL;
        CCARRAY_FOREACH_REVERSE(m_animations, obj){
            animation=static_cast<Animation*>(obj);
            animation->update(delta, 1);
        }
    }
}

void AnimationGroup::add(Animation* animation)
{
    m_animations->addObject(animation);
}

void AnimationGroup::remove(Animation* animation)
{
    m_animations->removeObject(animation);
}

NS_CC_YHGE_END