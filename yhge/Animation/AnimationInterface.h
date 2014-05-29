#ifndef YHGE_ANIMATION_ANIMATIONINTERFACE_H_
#define YHGE_ANIMATION_ANIMATIONINTERFACE_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"
#include "Frame.h"

NS_CC_YHGE_BEGIN

class IAnimationSprite
{
public:
    virtual void setAnimationFrame(Frame* frame)=0;
};

NS_CC_YHGE_END

#endif //YHGE_ANIMATION_ANIMATIONINTERFACE_H_