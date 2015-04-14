#ifndef YHGE_ANIMATION_RESOURCE_H_
#define YHGE_ANIMATION_RESOURCE_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"

NS_CC_YHGE_BEGIN

class Resource:public Ref
{
    
public:
    
    Resource();
    
    ~Resource();
    
    virtual bool init();
    
    CCSize getSize();
public:
    
    enum {
        kNoneTexture,
        kPackTexture,
        kFileTexture
    };
    
    inline void setId(int id)
    {
        _id = id;
    }
    
    inline int getId()
    {
        return _id;
    }
    
    inline void setType(int type)
    {
        _type = type;
    }
    
    inline int getType()
    {
        return _type;
    }
    
    inline void setSpriteFrame(CCSpriteFrame* spriteFrame)
    {
        CC_SAFE_RETAIN(spriteFrame);
        CC_SAFE_RELEASE(_spriteFrame);
        _spriteFrame = spriteFrame;
    }
    
    inline CCSpriteFrame* getSpriteFrame()
    {
        return _spriteFrame;
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
    }
    
protected:
   
    //唯一标识符
    int _id;
    
    //类型。一种是使用图块，一种是直接使用图片
    int _type;
    
    //类型为图块的定义
    CCSpriteFrame* _spriteFrame;
    
    //类型为图片的定义
    CCTexture2D* _texture;
    
};


NS_CC_YHGE_END

#endif //YHGE_ANIMATION_RESOURCE_H_