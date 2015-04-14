#ifndef YHGE_ANIMATION_DISPLAYPROPERTY_H_
#define YHGE_ANIMATION_DISPLAYPROPERTY_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"

NS_CC_YHGE_BEGIN

class DisplayProperty:public Ref
{
    
public:
    
    DisplayProperty();
    
    ~DisplayProperty();
    
    bool init();
    
    bool init(CCSpriteFrame* spriteFrame);
    
public:
   
    inline bool haveCharacter()
    {
        return _haveCharacter;
    }
    
    inline void setHaveCharacter(bool value)
    {
        _haveCharacter=value;
    }
    
    inline void setSpriteFrame(CCSpriteFrame* spriteFrame)
    {
        CC_SAFE_RETAIN(spriteFrame);
        CC_SAFE_RELEASE(_spriteFrame);
        _spriteFrame = spriteFrame;
        
        _haveCharacter=true;
    }

    inline CCSpriteFrame* getSpriteFrame()
    {
        return _spriteFrame;
    }

    inline bool haveTransform()
    {
        return _haveTransform;
    }
    
    inline void setHaveTransform(bool value)
    {
        _haveTransform=value;
    }

    inline void setTransform(const CCAffineTransform& transform)
    {
        _transform = transform;
        
        _haveTransform=true;
    }

    inline const CCAffineTransform& getTransform()
    {
        return _transform;
    }
    
    inline bool haveColor()
    {
        return _haveColor;
    }
    
    inline void setHaveColor(bool value)
    {
        _haveColor=value;
    }

    inline void setColor(const ccColor3B& color)
    {
        _color = color;
        _haveColor=true;
    }

    inline const ccColor3B& getColor()
    {
        return _color;
    }
    
    inline bool haveOpacity()
    {
        return _haveOpacity;
    }
    
    inline void setHaveOpacity(bool value)
    {
        _haveOpacity=value;
    }

    inline void setOpacity(unsigned char opacity)
    {
        _opacity = opacity;
        _haveOpacity=true;
    }

    inline unsigned char getOpacity()
    {
        return _opacity;
    }
    
    inline void setHaveZOrder(bool haveZOrder)
    {
        _haveZOrder = haveZOrder;
    }
    
    inline bool haveZOrder()
    {
        return _haveZOrder;
    }
    
    inline void setZOrder( int zOrder)
    {
        _zOrder = zOrder;
        _haveZOrder=true;
    }
    
    inline  int getZOrder()
    {
        return _zOrder;
    }

protected:

    bool _haveCharacter;
    
    CCSpriteFrame* _spriteFrame;

    bool _haveTransform;
    
    CCAffineTransform _transform;

    bool _haveColor;
    
    ccColor3B _color;
    
    bool _haveOpacity;
    
    unsigned char _opacity;
    
    bool _haveZOrder;
    
    int _zOrder;
};

NS_CC_YHGE_END

#endif //YHGE_ANIMATION_DISPLAYPROPERTY_H_