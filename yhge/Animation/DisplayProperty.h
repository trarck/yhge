#ifndef YHGE_ANIMATION_DISPLAYPROPERTY_H_
#define YHGE_ANIMATION_DISPLAYPROPERTY_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"

NS_CC_YHGE_BEGIN

class DisplayProperty:public CCObject
{
    
public:
    
    DisplayProperty();
    
    ~DisplayProperty();
    
    bool init();
    
    bool init(CCSpriteFrame* spriteFrame);
    
public:
   
    void setSpriteFrame(CCSpriteFrame* spriteFrame)
    {
        CC_SAFE_RETAIN(spriteFrame);
        CC_SAFE_RELEASE(m_spriteFrame);
        m_spriteFrame = spriteFrame;
    }

    CCSpriteFrame* getSpriteFrame()
    {
        return m_spriteFrame;
    }

    bool haveTransform()
    {
        return m_haveTransform;
    }

    void setTransform(const CCAffineTransform& transform)
    {
        m_transform = transform;
    }

    const CCAffineTransform& getTransform()
    {
        return m_transform;
    }

    void setColor(const ccColor3B& color)
    {
        m_color = color;
    }

    const ccColor3B& getColor()
    {
        return m_color;
    }

    void setOpacity(GLubyte opacity)
    {
        m_opacity = opacity;
    }

    GLubyte getOpacity()
    {
        return m_opacity;
    }

protected:

    CCSpriteFrame* m_spriteFrame;

    bool m_haveTransform;
    CCAffineTransform m_transform;

    ccColor3B m_color;
    GLubyte m_opacity;
};

NS_CC_YHGE_END

#endif //YHGE_ANIMATION_DISPLAYPROPERTY_H_