#include "CCAdaptSprite.h"

NS_CC_YHGE_BEGIN

CCAdaptSprite::CCAdaptSprite()
:_fillType(kNormal)
,_preferredSize(CCSizeZero)
,_havePreferredSize(false)
,_untrimmedSize(CCSizeZero)
,_orignalRect(CCRectZero)
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
    _orignalRect=rect;
    _bRectRotated=rotated;
    setUntrimmedSize(untrimmedSize);
    
    if (!_havePreferredSize) {
        CCSprite::setTextureRect(rect, rotated, untrimmedSize);
    }else{
        adjustTextureRect();
    }
}

void CCAdaptSprite::adjustTextureRect()
{
    switch (_fillType) {
        case kScale:
            adjustTextureByScale();
            break;
        case kClip:
            adjustTextureByClip();
            break;
        case kNormal:
        default:
            //            CCSprite::setTextureRect(_orignalRect, _bRectRotated, _untrimmedSize);
            break;
    }
}

void CCAdaptSprite::adjustTextureByScale()
{
    setContentSize(_preferredSize);
    
    setTextureCoords(_orignalRect);
    
    float scaleX=_preferredSize.width/_untrimmedSize.width;
    float scaleY=_preferredSize.height/_untrimmedSize.height;
    
    CCRect vertexRect=_orignalRect;
    vertexRect.size.width*=scaleX;
    vertexRect.size.height*=scaleY;
    setVertexRect(vertexRect);
    
    CCPoint relativeOffset = _obUnflippedOffsetPositionFromCenter;
    
    // issue #732
    if (_bFlipX)
    {
        relativeOffset.x = -relativeOffset.x;
    }
    if (_bFlipY)
    {
        relativeOffset.y = -relativeOffset.y;
    }
    
    _obOffsetPosition.x = relativeOffset.x + (_untrimmedSize.width - _orignalRect.size.width) / 2;
    _obOffsetPosition.y = relativeOffset.y + (_untrimmedSize.height - _orignalRect.size.height) / 2;
    
    _obOffsetPosition.x*=scaleX;
    _obOffsetPosition.y*=scaleY;
    
    // rendering using batch node
    if (_pobBatchNode)
    {
        // update dirty_, don't update recursiveDirty_
        setDirty(true);
    }
    else
    {
        // self rendering
        
        // Atlas: Vertex
        float x1 = 0 + _obOffsetPosition.x;
        float y1 = 0 + _obOffsetPosition.y;
        float x2 = x1 + _obRect.size.width;
        float y2 = y1 + _obRect.size.height;
        
        // Don't update Z.
        _sQuad.bl.vertices = vertex3(x1, y1, 0);
        _sQuad.br.vertices = vertex3(x2, y1, 0);
        _sQuad.tl.vertices = vertex3(x1, y2, 0);
        _sQuad.tr.vertices = vertex3(x2, y2, 0);
    }
}

void CCAdaptSprite::adjustTextureByClip()
{
    
    setContentSize(_preferredSize);
    
    CCRect textureRect=_orignalRect;
    textureRect.size.width=MIN(textureRect.size.width, _preferredSize.width);
    textureRect.size.height=MIN(textureRect.size.height, _preferredSize.height);
    setTextureCoords(textureRect);
    
    CCPoint relativeOffset = _obUnflippedOffsetPositionFromCenter;
    
    // issue #732
    if (_bFlipX)
    {
        relativeOffset.x = -relativeOffset.x;
    }
    if (_bFlipY)
    {
        relativeOffset.y = -relativeOffset.y;
    }
    
    _obOffsetPosition.x = relativeOffset.x + (_untrimmedSize.width - _orignalRect.size.width) / 2;
    
    _obOffsetPosition.y = relativeOffset.y + (_untrimmedSize.height - _orignalRect.size.height) / 2;
    
    //设置要渲染的大小
    CCRect vertexRect=_orignalRect;
    float vertexWidth=_preferredSize.width-_obOffsetPosition.x;
    float vertexHeight=_preferredSize.height-_obOffsetPosition.y;
    
    //保证在0和rect.size之间
    vertexWidth=MAX(0, MIN(vertexWidth, _orignalRect.size.width));
    vertexHeight=MAX(0, MIN(vertexWidth, _orignalRect.size.height));
    
    vertexRect.size.width=vertexWidth;
    vertexRect.size.height=vertexHeight;
    
    setVertexRect(vertexRect);
    
    // rendering using batch node
    if (_pobBatchNode)
    {
        // update dirty_, don't update recursiveDirty_
        setDirty(true);
    }
    else
    {
        // self rendering
        
        // Atlas: Vertex
        float x1 = 0 + _obOffsetPosition.x;
        float y1 = 0 + _obOffsetPosition.y;
        float x2 = x1 + _obRect.size.width;
        float y2 = y1 + _obRect.size.height;
        
        // Don't update Z.
        _sQuad.bl.vertices = vertex3(x1, y1, 0);
        _sQuad.br.vertices = vertex3(x2, y1, 0);
        _sQuad.tl.vertices = vertex3(x1, y2, 0);
        _sQuad.tr.vertices = vertex3(x2, y2, 0);
    }
}

NS_CC_YHGE_END
