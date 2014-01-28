#include "ISOTile.h"
#include "ISOTileset.h"

NS_CC_YHGE_BEGIN

ISOTile::ISOTile()
:m_nId(0)
,m_pTexture(NULL)
,m_pAnimation(NULL)
,m_tTextureRect(CCRectZero)
,m_pProperties(NULL)
,m_pTileset(NULL)
{
    
}

ISOTile::~ISOTile()
{
    CCLOG("ISOTile destroy");
    CC_SAFE_RELEASE(m_pProperties);
    CC_SAFE_RELEASE(m_pTexture);
    CC_SAFE_RELEASE_NULL(m_pAnimation);
}

bool ISOTile::init()
{
    m_pProperties=new CCDictionary();
    return true;
}

bool ISOTile::init(int id,ISOTileset* tileset)
{
    if(init()){
        m_nId=id;
        setTileset(tileset);
        return true;
    }
    return false;
}

bool ISOTile::init(int id,ISOTileset* tileset,CCTexture2D* texture)
{
    if(init(id,tileset)){
        setTexture(texture);
        m_tTextureRect.size=texture->getContentSizeInPixels();
        return true;
    }
    return false;
}

bool ISOTile::init(int id,ISOTileset* tileset,CCTexture2D* texture,CCRect& textureRect)
{
    if(init(id,tileset,texture)){
        m_tTextureRect=textureRect;
        return true;
    }
    return false;
}

void ISOTile::setId(int nId)
{
    m_nId = nId;
}

int ISOTile::getId()
{
    return m_nId;
}

int ISOTile::getGId()
{
    return m_nId+m_pTileset->getFirstGid();
}

void ISOTile::setTileset(ISOTileset* pTileset)
{
    m_pTileset = pTileset;
}

ISOTileset* ISOTile::getTileset()
{
    return m_pTileset;
}

void ISOTile::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* ISOTile::getProperties()
{
    return m_pProperties;
}

NS_CC_YHGE_END
