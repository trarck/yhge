#include "Animation.h"

NS_CC_YHGE_BEGIN

Animation::Animation()
:m_enable(true)
,m_currentFrameIndex(0)
,m_frameCount(0)
//,m_totalDuration(0.0f)
,m_duration(0.0f)
,m_elapsed(0.0f)
,m_frames(NULL)
{
    
}

Animation::~Animation()
{
    CC_SAFE_RELEASE_NULL(m_frames);
}

bool Animation::init()
{
    m_frames=new CCArray();
    
    return true;
}

bool Animation::init(float duration)
{
    m_frames=new CCArray();
    
    m_duration=duration;
    
    return true;
}

void Animation::play()
{
    m_enable=true;
}

void Animation::stop()
{
    m_enable=false;
}

void Animation::nextFrame()
{
    m_currentFrameIndex=(m_currentFrameIndex+1)%m_frameCount;
    stop();
}

void Animation::prevFrame()
{
    m_currentFrameIndex=m_currentFrameIndex==0?m_frameCount-1:m_currentFrameIndex-1;
    stop();
}

void Animation::gotoAndPlay(int index)
{
    setCurrentFrameIndex(index);
    play();
}

void Animation::gotoAndStop(int index)
{
    setCurrentFrameIndex(index);
    stop();
}

void Animation::appendFrame(Frame* frame)
{
    m_frames->addObject(frame);
    ++m_frameCount;
}

void Animation::insertFrame(Frame* frame,int index)
{
    m_frames->insertObject(frame, index);
}

void Animation::removeFrame(Frame* frame)
{
    int index=m_frames->indexOfObject(frame);
    if (index!=CC_INVALID_INDEX) {
        removeFrameByIndex(index);
    }
}

void Animation::removeFrameByIndex(int index)
{
    if (index>=0 && index<m_frames->count()) {
        m_frames->removeObjectAtIndex(index);
        --m_frameCount;
    }
}

Frame* Animation::getFrame(int index)
{
    return index>=0 && index<m_frames->count()?static_cast<Frame*>(m_frames->objectAtIndex(index)):NULL;
}

Frame* Animation::getCurrentFrame()
{
    return static_cast<Frame*>(m_frames->objectAtIndex(m_currentFrameIndex));
}

void Animation::update(float delta)
{
    if (m_enable) {
        m_elapsed+=delta;
        m_currentFrameIndex=(int)floor(m_elapsed/m_duration)%m_frameCount;
    }
}

void Animation::update(float delta,int deltaFrame)
{
    m_currentFrameIndex=(m_currentFrameIndex+deltaFrame)%m_frameCount;
}

NS_CC_YHGE_END