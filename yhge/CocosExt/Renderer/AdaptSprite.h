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
        _preferredSize = preferredSize;
        _havePreferredSize=true;
        
        //如果已经设置texture，则调整texture
        if(_pobTexture){
            adjustTextureRect();
        }
    }
    
    inline const CCSize& getPreferredSize()
    {
        return _preferredSize;
    }
    
    inline void setUntrimmedSize(const CCSize& untrimmedSize)
    {
        _untrimmedSize = untrimmedSize;
    }
    
    inline const CCSize& getUntrimmedSize()
    {
        return _untrimmedSize;
    }
    
    inline void setFillType(int fillType)
    {
        _fillType = fillType;
    }
    
    inline int getFillType()
    {
        return _fillType;
    }
    
protected:
    
    void adjustTextureRect();
    
    void adjustTextureByScale();
    
    void adjustTextureByClip();
    
protected:
    
    CCSize _preferredSize;
    
    bool _havePreferredSize;
    
    CCSize _untrimmedSize;
    
    int _fillType;
    
    CCRect _orignalRect;
};


NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_CCADAPTSPRITE_H_
