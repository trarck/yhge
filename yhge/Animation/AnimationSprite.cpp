#include "AnimationSprite.h"

NS_CC_YHGE_BEGIN

AnimationSprite::AnimationSprite()
:_animation(NULL)
{

}

AnimationSprite::~AnimationSprite()
{
    CC_SAFE_RELEASE_NULL(_animation);
}

void AnimationSprite::setAnimationFrame(Frame* frame)
{
    DisplayProperty* displayProperty=frame->getDisplayProperty();
    
    if (displayProperty->haveCharacter()) {
        setDisplayFrame(displayProperty->getSpriteFrame());
    }
    
    AnimationDataFlag flag=_animation->getAnimationDataFlag();

    if(flag.haveTransform && displayProperty->haveTransform()){
        setAdditionalTransform(displayProperty->getTransform());
    }

    if (flag.haveColor && displayProperty->haveColor())
    {
        setColor(displayProperty->getColor());
    }
    
    if(flag.haveOpacity && displayProperty->haveOpacity()){
        setOpacity(displayProperty->getOpacity());
    }
}

void AnimationSprite::updateCurrentAnimationFrame()
{
    //set current frame
    if (_animation)
    {
        Frame* frame=_animation->getCurrentFrame();
        if (frame)
        {
            setAnimationFrame(frame);
        }
    }
}


NS_CC_YHGE_END