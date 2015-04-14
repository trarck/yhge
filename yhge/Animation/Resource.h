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
        m_id = id;
    }
    
    inline int getId()
    {
        return m_id;
    }
    
    inline void setType(int type)
    {
        m_type = type;
    }
    
    inline int getType()
    {
        return m_type;
    }
    
    inline void setSpriteFrame(CCSpriteFrame* spriteFrame)
    {
        CC_SAFE_RETAIN(spriteFrame);
        CC_SAFE_RELEASE(m_spriteFrame);
        m_spriteFrame = spriteFrame;
    }
    
    inline CCSpriteFrame* getSpriteFrame()
    {
        return m_spriteFrame;
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
   
    //唯一标识符
    int m_id;
    
    //类型。一种是使用图块，一种是直接使用图片
    int m_type;
    
    //类型为图块的定义
    CCSpriteFrame* m_spriteFrame;
    
    //类型为图片的定义
    CCTexture2D* m_texture;
    
};


NS_CC_YHGE_END

#endif //YHGE_ANIMATION_RESOURCE_H_