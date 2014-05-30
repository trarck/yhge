#include "AnimationSprite.h"

NS_CC_YHGE_BEGIN

AnimationSprite::AnimationSprite()
:m_animation(NULL)
{

}

AnimationSprite::~AnimationSprite()
{
    CC_SAFE_RELEASE_NULL(m_animation);
}

void AnimationSprite::setAnimationFrame(Frame* frame)
{
    setDisplayFrame(frame->getSpriteFrame());

    AnimationDataFlag flag=m_animation->getAnimationDataFlag();

    if(flag.haveTransform){
        setAdditionalTransform(frame->getTransform());
    }

    if (flag.haveColor)
    {
        setColor(frame->getColor());
    }
    
    if(flag.haveOpacity){
        setOpacity(frame->getOpacity());
    }
}

void AnimationSprite::updateCurrentAnimationFrame()
{
    //set current frame
    if (m_animation)
    {
        Frame* frame=m_animation->getCurrentFrame();
        if (frame)
        {
            setAnimationFrame(frame);
        }
    }
}


NS_CC_YHGE_END