#ifndef YHGE_ANIMATION_AVATARSPRITE_H_
#define YHGE_ANIMATION_AVATARSPRITE_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"
#include "AnimationInterface.h"
#include "Frame.h"
#include "Animation.h"
#include "DisplayProperty.h"

NS_CC_YHGE_BEGIN

/**
 * 组件的生命周期
 * 通常纸娃娃系统的单个生命周期一直到动画结束
 * 如果遇到某个组件不显示，则设置为visible.就算后面几帧不显示，也不能删除，因为循环播放到前几帧又要显示了。
 * 另外一个组件的zorder是一直占用的，不会出现某一帧是一个zorder，另一帧又是个zorder。另外编辑器也没这个功能。解决办法使用二个组件。
 */
class AvatarSprite:public CCSpriteBatchNode,public IAnimationSprite
{  
public:

    AvatarSprite();

    ~AvatarSprite();

    virtual bool init();
    
    virtual void setAnimationFrame(Frame* frame);

    void updateCurrentAnimationFrame();
    
protected:
    
    void updateDisplayElement(CCSprite* element,DisplayProperty* property);
    
public:

    void setAnimation(Animation* animation)
    {
        CC_SAFE_RETAIN(animation);

        if (m_animation)
        {
            m_animation->setAnimationSprite(NULL);
        }

        CC_SAFE_RELEASE(m_animation);

        m_animation = animation;

        if (animation)
        {
            animation->setAnimationSprite(this);
            updateCurrentAnimationFrame();
        }
    }

    Animation* getAnimation()
    {
        return m_animation;
    }

protected:

    Animation* m_animation;
    
    CCArray* m_elements;

};

NS_CC_YHGE_END

#endif //YHGE_ANIMATION_AVATARSPRITE_H_