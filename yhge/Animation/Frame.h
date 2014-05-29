#ifndef YHGE_ANIMATION_FRAME_H_
#define YHGE_ANIMATION_FRAME_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"

NS_CC_YHGE_BEGIN

class Frame:public CCObject
{
    
public:
    
    Frame()
    :m_size(CCSizeZero)
    ,m_offset(CCPointZero)
    ,m_rect(CCRectZero)
    ,m_texture(NULL)
    {
        
    }
    
    ~Frame()
    {
        CC_SAFE_RELEASE_NULL(m_texture);
    }
    
    bool init();
    
    bool init(CCTexture2D* texture,const CCRect& rect);
    
    bool init(CCTexture2D* texture,const CCRect& rect,const CCSize & size,const CCPoint & offset);
    
public:
    
    inline void setSize(const CCSize & size)
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
    }
    
protected:
    //需要显示的大小
    CCSize m_size;
    
    //显示的偏移量
    CCPoint m_offset;
    
    //在texture中的位置
    CCRect m_rect;
    
    CCTexture2D* m_texture;
};


NS_CC_YHGE_END

#endif //YHGE_ANIMATION_FRAME_H_