#ifndef YHGE_ANIMATION_AVATARSPRITE_H_
#define YHGE_ANIMATION_AVATARSPRITE_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"
#include "AnimationInterface.h"
#include "Frame.h"
#include "Animation.h"
#include "DisplayProperty.h"

NS_CC_YHGE_BEGIN

class AvatarComponent:public CCSprite
{
public:

    static AvatarComponent* create();
  
    static AvatarComponent* create(const char *pszFileName);

    static AvatarComponent* create(const char *pszFileName, const CCRect& rect);

    static AvatarComponent* createWithTexture(CCTexture2D *pTexture);
    
    static AvatarComponent* createWithTexture(CCTexture2D *pTexture, const CCRect& rect);
    
    static AvatarComponent* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
    
    static AvatarComponent* createWithSpriteFrameName(const char *pszSpriteFrameName);

    void setTransform(const CCAffineTransform& transform);
};

/**
 * 显示组件
 * 通常分为二种类型
 * 1.每帧之间的显示组件，差另很大。也就是说，当前帧用到几个组件，下一帧又用到另外几个组件，很少有相同的组件。
     由于要切换显示内容，渲染效率不高。
   2.每帧之间的显示组件，基本相同，每帧只是进行状态变换。这样要求同一帧内的组件的id为能重复，就算资源相同，只是显示属性不同。
     由于不需要切换显示内容，只是设置属性，渲染效率高。
     如果组件之间的遮挡关系也是固定的，可以进一步提升效率。如果要实现当前帧A在B上，下一帧B在A上。则可以同时使用另一个和A一样的A'，注意ID要不同。当前帧A'不显示，显示A.下一帧A不显示，显示A'.
     后面在显示A,不显示A'.如果是用flash做ide,可以支持这个功能。
   3.类似flash的显示列表。
 */

/**
 * 组件的生命周期
 * 通常纸娃娃系统的组件生命周期一直到动画结束
 * 如果遇到某个组件不显示，则设置为disvisible.就算后面几帧不显示，也不能删除，因为循环播放到前几帧又要显示了。
 * 另外一个组件的zorder是一直占用的，不会出现某一帧是一个zorder，另一帧又是个zorder。另外编辑器也没这个功能。解决办法使用二个组件。
 */
class AvatarSprite:public CCSpriteBatchNode,public IAnimationSprite
{  
public:

    AvatarSprite();

    ~AvatarSprite();

    virtual bool init();
    
    bool initWithTexture(CCTexture2D *tex, unsigned int capacity);

    bool initWithFile(const char* fileImage, unsigned int capacity);
    
    virtual void setAnimationFrame(Frame* frame);

    void updateCurrentAnimationFrame();
    
    void setupComponets(CCArray* characters);
    
    void clearComponents();
    
protected:
    
    void updateDisplayElement(AvatarComponent* component,DisplayProperty* property);
    
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
    
    CCArray* m_components;

};

NS_CC_YHGE_END

#endif //YHGE_ANIMATION_AVATARSPRITE_H_