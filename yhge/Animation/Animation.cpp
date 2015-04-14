#include "Animation.h"

NS_CC_YHGE_BEGIN

static const AnimationDataFlag kDefaultFlag={false,false,false};

Animation::Animation()
:_enable(true)
,_currentFrameIndex(0)
,_frameCount(0)
//,_totalDuration(0.0f)
,_duration(0.0f)
,_elapsed(0.0f)
,_frames(NULL)
,_animationSprite(NULL)
,_animationDataFlag(kDefaultFlag)
{
    
}

Animation::~Animation()
{
    CC_SAFE_RELEASE_NULL(_frames);
}

bool Animation::init()
{
    _frames=new CCArray();
    
    return true;
}

bool Animation::init(float duration)
{
    _frames=new CCArray();
    
    _duration=duration;
    
    return true;
}

void Animation::play()
{
    _enable=true;
}

void Animation::stop()
{
    _enable=false;
}

void Animation::nextFrame()
{
    _currentFrameIndex=(_currentFrameIndex+1)%_frameCount;
    stop();
}

void Animation::prevFrame()
{
    _currentFrameIndex=_currentFrameIndex==0?_frameCount-1:_currentFrameIndex-1;
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
    _frames->addObject(frame);
    ++_frameCount;
}

void Animation::insertFrame(Frame* frame,int index)
{
    _frames->insertObject(frame, index);
}

void Animation::removeFrame(Frame* frame)
{
    int index=_frames->indexOfObject(frame);
    if (index!=CC_INVALID_INDEX) {
        removeFrameByIndex(index);
    }
}

void Animation::removeFrameByIndex(int index)
{
    if (index>=0 && index<_frames->count()) {
        _frames->removeObjectAtIndex(index);
        --_frameCount;
    }
}

Frame* Animation::getFrame(int index)
{
    return index>=0 && index<_frames->count()?static_cast<Frame*>(_frames->objectAtIndex(index)):NULL;
}

Frame* Animation::getCurrentFrame()
{
    return _frames->count()?static_cast<Frame*>(_frames->objectAtIndex(_currentFrameIndex)):NULL;
}

void Animation::update(float delta)
{
    if (_enable) {
        _elapsed+=delta;
        int frameIndex=(int)floor(_elapsed/_duration)%_frameCount;

        if (_currentFrameIndex!=frameIndex) {
            _currentFrameIndex=frameIndex;
            if (_animationSprite)
            {
                _animationSprite->setAnimationFrame(getCurrentFrame());
            }
        }
    }
}

void Animation::update(float delta,int deltaFrame)
{
    if (delta>0) {
        _currentFrameIndex=(_currentFrameIndex+deltaFrame)%_frameCount;
        if (_animationSprite)
        {
            _animationSprite->setAnimationFrame(getCurrentFrame());
        }
    }
}

NS_CC_YHGE_END