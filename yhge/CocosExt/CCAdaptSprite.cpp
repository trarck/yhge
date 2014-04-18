#include "CCAdaptSprite.h"

NS_CC_YHGE_BEGIN

CCAdaptSprite::CCAdaptSprite()
:m_fillType(kNormal)
,m_preferredSize(CCSizeZero)
,m_havePreferredSize(false)
,m_untrimmedSize(CCSizeZero)
,m_orignalRect(CCRectZero)
{
    
}


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
    m_orignalRect=rect;
    m_bRectRotated=rotated;
    setUntrimmedSize(untrimmedSize);
    
    if (!m_havePreferredSize) {
        CCSprite::setTextureRect(rect, rotated, untrimmedSize);
    }else{
        adjustTextureRect();
    }
}

void CCAdaptSprite::adjustTextureRect()
{
    switch (m_fillType) {
        case kScale:
            adjustTextureByScale();
            break;
        case kClip:
            adjustTextureByClip();
            break;
        case kNormal:
        default:
            //            CCSprite::setTextureRect(m_orignalRect, m_bRectRotated, m_untrimmedSize);
            break;
    }
}

void CCAdaptSprite::adjustTextureByScale()
{
    setContentSize(m_preferredSize);
    
    setTextureCoords(m_orignalRect);
    
    float scaleX=m_preferredSize.width/m_untrimmedSize.width;
    float scaleY=m_preferredSize.height/m_untrimmedSize.height;
    
    CCRect vertexRect=m_orignalRect;
    vertexRect.size.width*=scaleX;
    vertexRect.size.height*=scaleY;
    setVertexRect(vertexRect);
    
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
    
    m_obOffsetPosition.x = relativeOffset.x + (m_untrimmedSize.width - m_orignalRect.size.width) / 2;
    m_obOffsetPosition.y = relativeOffset.y + (m_untrimmedSize.height - m_orignalRect.size.height) / 2;
    
    m_obOffsetPosition.x*=scaleX;
    m_obOffsetPosition.y*=scaleY;
    
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

void CCAdaptSprite::adjustTextureByClip()
{
    
    setContentSize(m_preferredSize);
    
    CCRect textureRect=m_orignalRect;
    textureRect.size.width=MIN(textureRect.size.width, m_preferredSize.width);
    textureRect.size.height=MIN(textureRect.size.height, m_preferredSize.height);
    setTextureCoords(textureRect);
    
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
    
    m_obOffsetPosition.x = relativeOffset.x + (m_untrimmedSize.width - m_orignalRect.size.width) / 2;
    
    m_obOffsetPosition.y = relativeOffset.y + (m_untrimmedSize.height - m_orignalRect.size.height) / 2;
    
    //设置要渲染的大小
    CCRect vertexRect=m_orignalRect;
    float vertexWidth=m_preferredSize.width-m_obOffsetPosition.x;
    float vertexHeight=m_preferredSize.height-m_obOffsetPosition.y;
    
    //保证在0和rect.size之间
    vertexWidth=MAX(0, MIN(vertexWidth, m_orignalRect.size.width));
    vertexHeight=MAX(0, MIN(vertexWidth, m_orignalRect.size.height));
    
    vertexRect.size.width=vertexWidth;
    vertexRect.size.height=vertexHeight;
    
    setVertexRect(vertexRect);
    
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
