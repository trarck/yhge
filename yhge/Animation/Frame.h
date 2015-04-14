#ifndef YHGE_ANIMATION_FRAME_H_
#define YHGE_ANIMATION_FRAME_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"
#include "DisplayProperty.h"

NS_CC_YHGE_BEGIN

class Frame:public Ref
{
    
public:
    
    Frame();
    
    ~Frame();
    
    virtual bool init();
    
//    virtual bool init(CCSpriteFrame* spriteFrame);
    
public:
    
    inline void setDisplayProperty(DisplayProperty* displayProperty)
    {
        CC_SAFE_RETAIN(displayProperty);
        CC_SAFE_RELEASE(_displayProperty);
        _displayProperty = displayProperty;
    }
    
    inline DisplayProperty* getDisplayProperty()
    {
        return _displayProperty;
    }
    
    /*inline void setSize(const CCSize & size)
    {
        _size = size;
    }
    
    inline const CCSize & getSize()
    {
        return _size;
    }
    
    inline void setOffset(const CCPoint & offset)
    {
        _offset = offset;
    }
    
    inline const CCPoint & getOffset()
    {
        return _offset;
    }
    
    inline void setRect(const CCRect& rect)
    {
        _rect = rect;
    }
    
    inline const CCRect& getRect()
    {
        return _rect;
    }
    
    inline void setTexture(CCTexture2D* texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(_texture);
        _texture = texture;
    }
    
    inline CCTexture2D* getTexture()
    {
        return _texture;
    }*/
//    void setSpriteFrame(CCSpriteFrame* spriteFrame)
//    {
//        CC_SAFE_RETAIN(spriteFrame);
//        CC_SAFE_RELEASE(_spriteFrame);
//        _spriteFrame = spriteFrame;
//    }
//
//    CCSpriteFrame* getSpriteFrame()
//    {
//        return _spriteFrame;
//    }
//
//    bool haveTransform()
//    {
//        return _haveTransform;
//    }
//
//    void setTransform(const CCAffineTransform& transform)
//    {
//        _transform = transform;
//    }
//
//    const CCAffineTransform& getTransform()
//    {
//        return _transform;
//    }
//
//    void setColor(const ccColor3B& color)
//    {
//        _color = color;
//    }
//
//    const ccColor3B& getColor()
//    {
//        return _color;
//    }
//
//    void setOpacity(GLubyte opacity)
//    {
//        _opacity = opacity;
//    }
//
//    GLubyte getOpacity()
//    {
//        return _opacity;
//    }

protected:
    ////需要显示的大小
    //CCSize _size;
    //
    ////显示的偏移量
    //CCPoint _offset;
    //
    ////在texture中的位置
    //CCRect _rect;
    //
    //CCTexture2D* _texture;

//    CCSpriteFrame* _spriteFrame;
//
//    bool _haveTransform;
//    CCAffineTransform _transform;
//
//    ccColor3B _color;
//    GLubyte _opacity;
    
    DisplayProperty* _displayProperty;
};


NS_CC_YHGE_END

#endif //YHGE_ANIMATION_FRAME_H_