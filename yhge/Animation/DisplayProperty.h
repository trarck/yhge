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
   
    inline bool haveCharacter()
    {
        return m_haveCharacter;
    }
    
    inline void setHaveCharacter(bool value)
    {
        m_haveCharacter=value;
    }
    
    inline void setSpriteFrame(CCSpriteFrame* spriteFrame)
    {
        CC_SAFE_RETAIN(spriteFrame);
        CC_SAFE_RELEASE(m_spriteFrame);
        m_spriteFrame = spriteFrame;
        
        m_haveCharacter=true;
    }

    inline CCSpriteFrame* getSpriteFrame()
    {
        return m_spriteFrame;
    }

    inline bool haveTransform()
    {
        return m_haveTransform;
    }
    
    inline void setHaveTransform(bool value)
    {
        m_haveTransform=value;
    }

    inline void setTransform(const CCAffineTransform& transform)
    {
        m_transform = transform;
        
        m_haveTransform=true;
    }

    inline const CCAffineTransform& getTransform()
    {
        return m_transform;
    }
    
    inline bool haveColor()
    {
        return m_haveColor;
    }
    
    inline void setHaveColor(bool value)
    {
        m_haveColor=value;
    }

    inline void setColor(const ccColor3B& color)
    {
        m_color = color;
        m_haveColor=true;
    }

    inline const ccColor3B& getColor()
    {
        return m_color;
    }
    
    inline bool haveOpacity()
    {
        return m_haveOpacity;
    }
    
    inline void setHaveOpacity(bool value)
    {
        m_haveOpacity=value;
    }

    inline void setOpacity(unsigned char opacity)
    {
        m_opacity = opacity;
        m_haveOpacity=true;
    }

    inline unsigned char getOpacity()
    {
        return m_opacity;
    }
    
    inline void setHaveZOrder(bool haveZOrder)
    {
        m_haveZOrder = haveZOrder;
    }
    
    inline bool haveZOrder()
    {
        return m_haveZOrder;
    }
    
    inline void setZOrder( int zOrder)
    {
        m_zOrder = zOrder;
        m_haveZOrder=true;
    }
    
    inline  int getZOrder()
    {
        return m_zOrder;
    }

protected:

    bool m_haveCharacter;
    
    CCSpriteFrame* m_spriteFrame;

    bool m_haveTransform;
    
    CCAffineTransform m_transform;

    bool m_haveColor;
    
    ccColor3B m_color;
    
    bool m_haveOpacity;
    
    unsigned char m_opacity;
    
    bool m_haveZOrder;
    
    int m_zOrder;
};

NS_CC_YHGE_END

#endif //YHGE_ANIMATION_DISPLAYPROPERTY_H_