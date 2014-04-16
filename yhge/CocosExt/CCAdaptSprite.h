#ifndef YHGE_COCOSEXT_CCADAPTSPRITE_H_
#define YHGE_COCOSEXT_CCADAPTSPRITE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

/**
 * 自适应大小的sprite
 */
class CCAdaptSprite : public CCSprite
{
public:
    
    CCAdaptSprite();
    
    static CCAdaptSprite* create();
    
    static CCAdaptSprite* create(const char *pszFileName);
    
    static CCAdaptSprite* create(const char *pszFileName, const CCRect& rect);
    
    static CCAdaptSprite* createWithTexture(CCTexture2D *pTexture);
    
    static CCAdaptSprite* createWithTexture(CCTexture2D *pTexture, const CCRect& rect);
    
    static CCAdaptSprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);

    static CCAdaptSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    
    virtual void setTextureRect(const CCRect& rect);
    
    virtual void setTextureRect(const CCRect& rect, bool rotated, const CCSize& untrimmedSize);
        
public:
    
    enum FillType
    {
        kNormal,//keep texture original size
        kScale,//resize texture
        kClip,//clip texture
    };
    
    inline void setPreferredSize(const CCSize& preferredSize)
    {
        m_preferredSize = preferredSize;
        m_havePreferredSize=true;
        
        //如果已经设置texture，则调整texture
        if(m_pobTexture){
            adjustTextureRect();
        }
    }
    
    inline const CCSize& getPreferredSize()
    {
        return m_preferredSize;
    }
    
    inline void setUntrimmedSize(const CCSize& untrimmedSize)
    {
        m_untrimmedSize = untrimmedSize;
    }
    
    inline const CCSize& getUntrimmedSize()
    {
        return m_untrimmedSize;
    }
    
    inline void setFillType(int fillType)
    {
        m_fillType = fillType;
    }
    
    inline int getFillType()
    {
        return m_fillType;
    }
    
protected:
    
    void adjustTextureRect();
    
    void adjustTextureByScale();
    
    void adjustTextureByClip();
    
protected:
    
    CCSize m_preferredSize;
    
    bool m_havePreferredSize;
    
    CCSize m_untrimmedSize;
    
    int m_fillType;
    
    CCRect m_orignalRect;
};


NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_CCADAPTSPRITE_H_
