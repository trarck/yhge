#include "CCAdaptSprite.h"

NS_CC_YHGE_BEGIN


CCAdaptSprite* CCAdaptSprite::createWithTexture(CCTexture2D *pTexture)
{
    CCAdaptSprite *pobSprite = new CCAdaptSprite();
    if (pobSprite && pobSprite->initWithTexture(pTexture))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCAdaptSprite* CCAdaptSprite::createWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
    CCAdaptSprite *pobSprite = new CCAdaptSprite();
    if (pobSprite && pobSprite->initWithTexture(pTexture, rect))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCAdaptSprite* CCAdaptSprite::create(const char *pszFileName)
{
    CCAdaptSprite *pobSprite = new CCAdaptSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCAdaptSprite* CCAdaptSprite::create(const char *pszFileName, const CCRect& rect)
{
    CCAdaptSprite *pobSprite = new CCAdaptSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName, rect))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCAdaptSprite* CCAdaptSprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    CCAdaptSprite *pobSprite = new CCAdaptSprite();
    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCAdaptSprite* CCAdaptSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
#endif
    
    return createWithSpriteFrame(pFrame);
}

CCAdaptSprite* CCAdaptSprite::create()
{
    CCAdaptSprite *pSprite = new CCAdaptSprite();
    if (pSprite && pSprite->init())
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void CCAdaptSprite::setTextureRect(const CCRect& rect)
{
    CCSprite::setTextureRect(rect, false, rect.size);
}

void CCAdaptSprite::setTextureRect(const CCRect& rect, bool rotated, const CCSize& untrimmedSize)
{
    m_bRectRotated = rotated;
    
    CCRect vertexRect=rect;
    vertexRect.size=untrimmedSize;
    
    setContentSize(untrimmedSize);
    setVertexRect(vertexRect);
    setTextureCoords(rect);
    
    CCPoint relativeOffset = m_obUnflippedOffsetPositionFromCenter;
    
    // issue #732
    if (m_bFlipX)
    {
        relativeOffset.x = -relativeOffset.x;
    }
    if (m_bFlipY)
    {
        relativeOffset.y = -relativeOffset.y;
    }
    
    m_obOffsetPosition.x = relativeOffset.x ;//+ (m_obContentSize.width - m_obRect.size.width) / 2;
    m_obOffsetPosition.y = relativeOffset.y ;//+ (m_obContentSize.height - m_obRect.size.height) / 2;
    
    // rendering using batch node
    if (m_pobBatchNode)
    {
        // update dirty_, don't update recursiveDirty_
        setDirty(true);
    }
    else
    {
        // self rendering
        
        // Atlas: Vertex
        float x1 = 0 + m_obOffsetPosition.x;
        float y1 = 0 + m_obOffsetPosition.y;
        float x2 = x1 + m_obRect.size.width;
        float y2 = y1 + m_obRect.size.height;
        
        // Don't update Z.
        m_sQuad.bl.vertices = vertex3(x1, y1, 0);
        m_sQuad.br.vertices = vertex3(x2, y1, 0);
        m_sQuad.tl.vertices = vertex3(x1, y2, 0);
        m_sQuad.tr.vertices = vertex3(x2, y2, 0);
    }
}

NS_CC_YHGE_END
