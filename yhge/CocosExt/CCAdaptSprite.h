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
    
    static CCAdaptSprite* create();
    
    static CCAdaptSprite* create(const char *pszFileName);
    
    static CCAdaptSprite* create(const char *pszFileName, const CCRect& rect);
    
    static CCAdaptSprite* createWithTexture(CCTexture2D *pTexture);
    
    static CCAdaptSprite* createWithTexture(CCTexture2D *pTexture, const CCRect& rect);
    
    static CCAdaptSprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);

    static CCAdaptSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    
    virtual void setTextureRect(const CCRect& rect);
    
    virtual void setTextureRect(const CCRect& rect, bool rotated, const CCSize& untrimmedSize);
    
};


NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_CCADAPTSPRITE_H_
