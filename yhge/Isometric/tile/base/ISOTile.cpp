#include "ISOTile.h"
#include "ISOTileset.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTile::ISOTile()
:_nId(0)
,_pTexture(NULL)
,_pAnimation(NULL)
,_tTextureRect(CCRectZero)
,_properties(NULL)
,_pTileset(NULL)
{
    
}

ISOTile::~ISOTile()
{
    CCLOG("ISOTile destroy");
    CC_SAFE_RELEASE(_properties);
    CC_SAFE_RELEASE(_pTexture);
    CC_SAFE_RELEASE_NULL(_pAnimation);
}

bool ISOTile::init()
{
    _properties=new CCDictionary();
    return true;
}

bool ISOTile::init(int id,ISOTileset* tileset)
{
    if(init()){
        _nId=id;
        setTileset(tileset);
        return true;
    }
    return false;
}

bool ISOTile::init(int id,ISOTileset* tileset,CCTexture2D* texture)
{
    if(init(id,tileset)){
        setTexture(texture);
        _tTextureRect.size=texture->getContentSizeInPixels();
        return true;
    }
    return false;
}

bool ISOTile::init(int id,ISOTileset* tileset,CCTexture2D* texture,CCRect& textureRect)
{
    if(init(id,tileset,texture)){
        _tTextureRect=textureRect;
        return true;
    }
    return false;
}

void ISOTile::setId(int nId)
{
    _nId = nId;
}

int ISOTile::getId()
{
    return _nId;
}

int ISOTile::getGId()
{
    return _nId+_pTileset->getFirstGid();
}

void ISOTile::setTileset(ISOTileset* pTileset)
{
    _pTileset = pTileset;
}

ISOTileset* ISOTile::getTileset()
{
    return _pTileset;
}

void ISOTile::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(_properties);
    _properties = pProperties;
}

CCDictionary* ISOTile::getProperties()
{
    return _properties;
}

NS_CC_YHGE_ISOMETRIC_END
