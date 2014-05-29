#ifndef YHGE_ANIMATION_FRAME_H_
#define YHGE_ANIMATION_FRAME_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"

NS_CC_YHGE_BEGIN

class Frame:public CCObject
{
    
public:
    
    Frame();
    
    ~Frame();
    
    bool init();
    
    bool init(CCSpriteFrame* spriteFrame);
    
public:
    
    /*inline void setSize(const CCSize & size)
    {
        m_size = size;
    }
    
    inline const CCSize & getSize()
    {
        return m_size;
    }
    
    inline void setOffset(const CCPoint & offset)
    {
        m_offset = offset;
    }
    
    inline const CCPoint & getOffset()
    {
        return m_offset;
    }
    
    inline void setRect(const CCRect& rect)
    {
        m_rect = rect;
    }
    
    inline const CCRect& getRect()
    {
        return m_rect;
    }
    
    inline void setTexture(CCTexture2D* texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(m_texture);
        m_texture = texture;
    }
    
    inline CCTexture2D* getTexture()
    {
        return m_texture;
    }*/
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
    ////需要显示的大小
    //CCSize m_size;
    //
    ////显示的偏移量
    //CCPoint m_offset;
    //
    ////在texture中的位置
    //CCRect m_rect;
    //
    //CCTexture2D* m_texture;

    CCSpriteFrame* m_spriteFrame;

    bool m_haveTransform;
    CCAffineTransform m_transform;

    ccColor3B m_color;
    GLubyte m_opacity;
};


NS_CC_YHGE_END

#endif //YHGE_ANIMATION_FRAME_H_