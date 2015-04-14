#ifndef YHGE_ANIMATION_ANIMATIONSPRITE_H_
#define YHGE_ANIMATION_ANIMATIONSPRITE_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"
#include "AnimationInterface.h"
#include "Frame.h"
#include "Animation.h"

NS_CC_YHGE_BEGIN

class AnimationSprite:public CCSprite,public IAnimationSprite
{  
public:

    AnimationSprite();

    ~AnimationSprite();

    virtual void setAnimationFrame(Frame* frame);

    void updateCurrentAnimationFrame();

public:

    void setAnimation(Animation* animation)
    {
        CC_SAFE_RETAIN(animation);

        if (_animation)
        {
            _animation->setAnimationSprite(NULL);
        }

        CC_SAFE_RELEASE(_animation);

        _animation = animation;

        if (animation)
        {
            animation->setAnimationSprite(this);
            updateCurrentAnimationFrame();
        }
    }

    Animation* getAnimation()
    {
        return _animation;
    }

protected:

    Animation* _animation;

};

NS_CC_YHGE_END

#endif //YHGE_ANIMATION_ANIMATIONSPRITE_H_