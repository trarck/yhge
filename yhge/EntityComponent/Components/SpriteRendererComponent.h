#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_SpriteRendererComponent_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_SpriteRendererComponent_H_

#include "cocos2d.h"
#include "RendererComponent.h"

NS_CC_YHGE_BEGIN


class SpriteRendererComponent : public RendererComponent
{
public:
    
    SpriteRendererComponent();
    
    ~SpriteRendererComponent();
    
    virtual bool init();
//    
//    /**
//     * 执行animation
//     */
//    virtual void runAnimate(CCAction* animate);
//    
//    /**
//     * 停止animation
//     */
//    virtual void stopAnimate(CCAction* animate);
//    
//    /**
//     * 停止animation
//     */
//    virtual void stopAnimateByTag(int tag);

public:

    inline void setSpriteRenderer(CCSprite* spriteRenderer)
    {
        _spriteRenderer = spriteRenderer;
        setRenderer(spriteRenderer);
    }
    
    inline CCSprite* getSpriteRenderer()
    {
        return _spriteRenderer;
    }
    
protected:
    
    CCSprite* _spriteRenderer;
    
};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_SpriteRendererComponent_H_
