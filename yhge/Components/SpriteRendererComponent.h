#ifndef YHGE_COMPONENTS_SpriteRendererComponent_H_
#define YHGE_COMPONENTS_SpriteRendererComponent_H_

#include "cocos2d.h"
#include "RendererComponent.h"

NS_CC_YHGE_BEGIN


class SpriteRendererComponent : public RendererComponent
{
public:
    
    SpriteRendererComponent();
    
    ~SpriteRendererComponent();
    
    virtual bool init();
    
    virtual bool registerMessages();
    
    virtual void cleanupMessages();
    
    void onRunAction(Message* message);
    
    void onStopAction(Message* message);

public:

    inline void setSpriteRenderer(CCSprite* spriteRenderer)
    {
        m_spriteRenderer = spriteRenderer;
        setRenderer(spriteRenderer);
    }
    
    inline CCSprite* getSpriteRenderer()
    {
        return m_spriteRenderer;
    }
    
protected:
    
    CCSprite* m_spriteRenderer;
    
};

NS_CC_YHGE_END

#endif //YHGE_COMPONENTS_SpriteRendererComponent_H_
